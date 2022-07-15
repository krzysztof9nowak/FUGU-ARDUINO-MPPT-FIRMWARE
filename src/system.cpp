#include <Arduino.h>
#include <EEPROM.h> //SYSTEM PARAMETER  - EEPROM Library (By: Arduino)
#include <defines.h>
#include <sensors.h>
#include <system.h>
#include <variables.h>

void System_Processes() {
  fan_enabled = enableFan && (overrideFan || temperature >= temperatureFan);
  digitalWrite(FAN, fan_enabled);
}