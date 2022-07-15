#include <Arduino.h>
#include <defines.h>
#include <protection.h>
#include <variables.h>

void backflowControl() {
  if (output_mode == 0) {
    bypass_enabled = 1;
  } else {
    bypass_enabled = voltageInput > voltageOutput + voltageDropout;
  }

  digitalWrite(backflow_MOSFET, bypass_enabled);
}

mppt_error safety_checks() {
  mppt_error e = mppt_error::OK;

  backflowControl();

  if (temperature > temperatureMax)
    e |= mppt_error::OVERTEMPERATURE;
  if (currentInput > currentInAbsolute)
    e |= mppt_error::INPUT_OVERCURRENT;
  if (currentOutput > currentOutAbsolute)
    e |= mppt_error::OUTPUT_OVERCURRENT;
  if (voltageOutput > voltageBatteryMax + voltageBatteryThresh)
    e |= mppt_error::OUTPUT_OVERVOLTAGE;
  if (voltageInput < vInSystemMin && voltageOutput < vInSystemMin)
    e |= mppt_error::FATALLY_LOW_VOLTAGE;

  if (output_mode == 0) {
    // PSU MODE
    if (voltageInput < voltageOutput + voltageDropout)
      e |= mppt_error::INPUT_UNDERVOLTAGE;
  } else {
    // BATTERY MODE
    if (voltageOutput < vInSystemMin)
      e |= mppt_error::BATTERY_NOT_CONNECTED;
    if (voltageInput < voltageBatteryMax + voltageDropout)
      e |= mppt_error::INPUT_UNDERVOLTAGE;
  }

  return e;
}
