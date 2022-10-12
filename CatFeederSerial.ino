#include <SerialCommands.h>

//This is the default handler, and gets called when no other command matches. 
void cmd_unrecognized(SerialCommands* sender, const char* cmd)
{
  sender->GetSerial()->print("Unrecognized command [");
  sender->GetSerial()->print(cmd);
  sender->GetSerial()->println("]");
  
  sender->PrintAllCommands();
}

// serial command to set calibrated motor stop
void cmd_motor_set_stop(SerialCommands* sender){
  // TODO accept some sort of argument with this command
  CALIBRATED_SERVO_STOP = 92;
}

// serial command to set calibrated motor max cw
void cmd_motor_set_max_cw(SerialCommands* sender){
  // TODO accept some sort of argument with this command
  CALIBRATED_SERVO_MAX_CW = 180;
}

// serial command to set calibrated motor max ccw
void cmd_motor_set_max_ccw(SerialCommands* sender){
  // TODO accept some sort of argument with this command
  CALIBRATED_SERVO_MAX_CCW = 0;
}

// serial command to set forwardDuration
void cmd_motor_set_forward_duration(SerialCommands* sender){}

// serial command to set forwardSpeed
void cmd_motor_set_forward_speed(SerialCommands* sender){}

// serial command to set reverseDuration
void cmd_motor_set_reverse_duration(SerialCommands* sender){}

// serial command to set reverseSpeed
void cmd_motor_set_reverse_speed(SerialCommands* sender){}

// serial command to set interFeedDuration
void cmd_motor_set_interfeed_duration(SerialCommands* sender){}

// serial command to feed once
void cmd_feed_once(SerialCommands* sender){
  Feed();
}

// serial command to feed qty
void cmd_feed_qty(SerialCommands* sender){
  // TODO accept some sort of argument with this command
  Feed(10);
}

// serial command to display measured qty
void cmd_measure(SerialCommands* sender){}

// serial command to tare scale
void cmd_tare(SerialCommands* sender){}

// serial command to recalibrate scale
void cmd_scale_calibrate(SerialCommands* sender){}

// serial command to explicitly set scale calibration factor
void cmd_scale_set_cal_factor(SerialCommands* sender){}

// serial command to increment scale calibration factor
void cmd_scale_increment_cal_factor(SerialCommands* sender){}

// serial command to decrement scale calibration factor
void cmd_scale_decrement_cal_factor(SerialCommands* sender){}

//Note: Commands are case sensitive
SerialCommand cmd_motor_set_stop_("SetMotorStop", cmd_motor_set_stop);
SerialCommand cmd_motor_set_max_cw_("SetMotorMaxCW", cmd_motor_set_max_cw);
SerialCommand cmd_motor_set_max_ccw_("SetMotorMaxCCW", cmd_motor_set_max_ccw);
SerialCommand cmd_motor_set_forward_duration_("SetMotorFwdTime", cmd_motor_set_forward_duration);
SerialCommand cmd_motor_set_forward_speed_("SetMotorFwdSpeed", cmd_motor_set_forward_speed);
SerialCommand cmd_motor_set_reverse_duration_("SetMotorRevTime", cmd_motor_set_reverse_duration);
SerialCommand cmd_motor_set_reverse_speed_("SetMotorRevSpeed", cmd_motor_set_reverse_speed);
SerialCommand cmd_motor_set_interfeed_duration_("SetMotorInterfeedTime", cmd_motor_set_interfeed_duration);
SerialCommand cmd_feed_once_("Feed", cmd_feed_once);
SerialCommand cmd_feed_qty_("FeedQty", cmd_feed_qty);
SerialCommand cmd_measure_("Measure", cmd_measure);
SerialCommand cmd_tare_("Tare", cmd_tare);
SerialCommand cmd_scale_calibrate_("CalibrateScale", cmd_scale_calibrate);
SerialCommand cmd_scale_set_cal_factor_("ScaleSetCalFactor", cmd_scale_set_cal_factor);
SerialCommand cmd_scale_increment_cal_factor_("+", cmd_scale_increment_cal_factor, true);
SerialCommand cmd_scale_decrement_cal_factor_("-", cmd_scale_decrement_cal_factor, true);


void SetupSerialCommands()
{
  Serial.println("initializing serial commmands");

  serial_commands_.SetDefaultHandler(cmd_unrecognized);
  serial_commands_.AddCommand(&cmd_motor_set_stop_);
  serial_commands_.AddCommand(&cmd_motor_set_max_cw_);
  serial_commands_.AddCommand(&cmd_motor_set_forward_duration_);
  serial_commands_.AddCommand(&cmd_motor_set_forward_speed_);
  serial_commands_.AddCommand(&cmd_motor_set_reverse_duration_);
  serial_commands_.AddCommand(&cmd_motor_set_reverse_speed_);
  serial_commands_.AddCommand(&cmd_motor_set_interfeed_duration_);
  serial_commands_.AddCommand(&cmd_feed_once_);
  serial_commands_.AddCommand(&cmd_feed_qty_);
  serial_commands_.AddCommand(&cmd_measure_);
  serial_commands_.AddCommand(&cmd_tare_);
  serial_commands_.AddCommand(&cmd_scale_calibrate_);
  serial_commands_.AddCommand(&cmd_scale_set_cal_factor_);
  serial_commands_.AddCommand(&cmd_scale_increment_cal_factor_);
  serial_commands_.AddCommand(&cmd_scale_decrement_cal_factor_);
}