MotorSpeed GetMotorSpeed(Percent targetSpeed)
{
  // map -100 0 100 % to calibrated motor control range
  // explicitly map stop since it depends on the exact resistor tuning of the servo
  if ( targetSpeed < 0)
  {
    return static_cast<MotorSpeed>(map(targetSpeed, -100, -1, CALIBRATED_SERVO_MAX_CCW, CALIBRATED_SERVO_STOP));
  }

    if ( targetSpeed == 0)
  {
    return static_cast<MotorSpeed>(CALIBRATED_SERVO_STOP);
  }

    if ( targetSpeed > 0)
  {
    return static_cast<MotorSpeed>(map(targetSpeed, 1, 100, CALIBRATED_SERVO_STOP, CALIBRATED_SERVO_MAX_CW));
  }
  
}