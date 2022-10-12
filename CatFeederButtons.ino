void ButtonISR()
{  
  // button posedge detected, press and release  
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    Serial.println("ISR");
    buttonPressPending = true;
  }
  last_interrupt_time = interrupt_time;  
}

void ButtonISRHandler()
{
  if (feedButtonPressPending)
  {
    feedButtonPressPending = false;
    Feed();
  }

  if (calibrateButtonPressPending)
  {
    calibrateButtonPressPending = false;
    FinishCalibratingScale();
  }
}