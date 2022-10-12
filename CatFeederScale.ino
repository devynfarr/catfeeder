#include "limits.h"

void StartScale()
{
  if (!scaleCalibrated)
  {
    Serial.println("scale not calibrated!");
    return;
  }
  scaleStarted = true;
  scale.power_up();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(SCALE_CALIBRATION_FACTOR);
  scale.tare();
}

void EndScale()
{
scale.power_down();
scaleStarted = false;
}

void BeginCalibrateScale()
{
  scaleCalibrated = false;
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();

  // capture the button interrupt
  feedIsrEnabled = false;
  calibrateIsrEnabled = true;
  Serial.println("Place exactly 100g on the scale and press button to cal.");
}

void FinishCalibratingScale()
{
  SCALE_CALIBRATION_FACTOR = scale.get_units(10) / 100;  // hard coded 100 requires a calibration weight of 100g
    
  Serial.print("Calibration Factor: ");
  Serial.println(SCALE_CALIBRATION_FACTOR, DEC);
  
  // restore button interrupt enables
  feedIsrEnabled = false;
  calibrateIsrEnabled = true;

  scaleCalibrated = true;

  // TODO store to nonvolatile memory
}

Grams MeasureFood()
{        
  if (!scaleStarted || !scaleCalibrated)
  {
    Serial.println("scale not started!");
    return INT_MAX;
  }
    return static_cast<int>(scale.get_units()); // intentionally truncate float to int with narrowing cast
}

void DisplayMeasuredFood(Grams measuredFood, Grams targetFood)
{
  Serial.print(measuredFood, DEC);
  Serial.print("g / ");
  Serial.print(targetFood, DEC);
  Serial.println("g");
}