#include <Servo.h>
#include <RTClib.h>
#include <HX711.h>
#include <SerialCommands.h>
#include <math.h>

#define DEBUGGING

// region types
using MotorSpeed = int;
using Percent = int;
using Grams = int;
// endregion types

#define SERVO_CONTROL_PIN 9
Servo myservo;
int CALIBRATED_SERVO_STOP = 92;
int CALIBRATED_SERVO_MAX_CW = 180;
int CALIBRATED_SERVO_MAX_CCW = 0;

// region auger motion configuration parameters
using Milliseconds = int;
Milliseconds forwardDuration = 200;
Milliseconds reverseDuration = 100;
Milliseconds interFeedDuration = 100;
Percent forwardSpeed = 50;
Percent reverseSpeed = 50;
// region auger motion configuration parameters

// region loadcell
#define LOADCELL_DOUT_PIN 4
#define LOADCELL_SCK_PIN 2
int SCALE_CALIBRATION_FACTOR = 1;
int NUM_READINGS = 10;
bool scaleCalibrated = false;
bool scaleStarted = false;
HX711 scale;
// endregion loadcell

// region buttons
#define BUTTON_PIN 3
volatile int buttonPressPending = false;

// redirect button presses for multiple functions
bool feedIsrEnabled = true;
volatile bool feedButtonPressPending = false;

bool calibrateIsrEnabled = false;
volatile bool calibrateButtonPressPending = false;
// endregion buttons

// region serial commands
  char serial_command_buffer_[32];
  SerialCommands serial_commands_(&Serial, serial_command_buffer_, sizeof(serial_command_buffer_), "\r\n", " ");
// endregion serial commands

void setup() {  
  Serial.begin(9600);
  Serial.println("starting up");
  pinMode(BUTTON_PIN, INPUT_PULLUP);    
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ButtonISR, RISING);

  SetupSerialCommands();
  Serial.println("Started!");
}

void loop() {
  if (buttonPressPending)
  {
    buttonPressPending = false;

    feedButtonPressPending = feedIsrEnabled;
    calibrateButtonPressPending = calibrateIsrEnabled;

    Serial.println("");
      #ifdef DEBUGGING
        Serial.println("button press flag!");
      #endif
      ButtonISRHandler();
  }

  if (Serial.available())
  {
    // process serial commands
    Serial.println("reading serial...");
    serial_commands_.ReadSerial();
  }

  delay(100);
}

void Feed(Grams targetQty = 0)
{
  Grams fedQty = 0;

  if (targetQty > 0)
  {
    StartScale();
  }

  do{    

    Serial.println("Feeding...");


    myservo.attach(SERVO_CONTROL_PIN);  // attaches the servo on pin 9 to the servo object    
    myservo.write(GetMotorSpeed(forwardSpeed));
    delay(forwardDuration); 
    myservo.write(GetMotorSpeed(reverseSpeed));    
    delay(reverseDuration);
    myservo.write(CALIBRATED_SERVO_STOP);
    myservo.detach();

    if (targetQty > 0)
    {
        fedQty = MeasureFood();        
        DisplayMeasuredFood(fedQty, targetQty);        
    }  
  } while (fedQty < targetQty);

  Serial.println("Finished");  


  if (targetQty > 0)
  {    
    EndScale();
  }  
}
