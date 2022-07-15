#pragma once

#include <protection.h>

extern bool                                  
MPPT_mode               ,           //   USER PARAMETER - Enable MPPT algorithm, when disabled charger uses CC-CV algorithm 
output_mode             ,           //   USER PARAMETER - 0 = PSU MODE, 1 = Charger Mode  
disableFlashAutoLoad    ,           //   USER PARAMETER - Forces the MPPT to not use flash saved settings, enabling this "1" defaults to programmed firmware settings.
enablePPWM              ,           //   USER PARAMETER - Enables Predictive PWM, this accelerates regulation speed (only applicable for battery charging application)
enableWiFi              ,           //   USER PARAMETER - Enable WiFi Connection
enableFan               ,           //   USER PARAMETER - Enable Cooling Fan
enableBluetooth         ,           //   USER PARAMETER - Enable Bluetooth Connection
overrideFan             ;           //   USER PARAMETER - Fan always on
extern int
serialTelemMode         ,           //  USER PARAMETER - Selects serial telemetry data feed (0 - Disable Serial, 1 - Display All Data, 2 - Display Essential, 3 - Number only)
pwmResolution           ,          //  USER PARAMETER - PWM Bit Resolution 
pwmFrequency            ,       //  USER PARAMETER - PWM Switching Frequency - Hz (For Buck)
temperatureFan          ,          //  USER PARAMETER - Temperature threshold for fan to turn on
temperatureMax          ,          //  USER PARAMETER - Overtemperature, System Shudown When Exceeded (deg C)
millisRoutineInterval   ,         //  USER PARAMETER - Time Interval Refresh Rate For Routine Functions (ms)
millisSerialInterval    ,           //  USER PARAMETER - Time Interval Refresh Rate For USB Serial Datafeed (ms)
millisWiFiInterval      ,        //  USER PARAMETER - Time Interval Refresh Rate For WiFi Telemetry (ms)
backlightSleepMode      ;          //  USER PARAMETER - 0 = Never, 1 = 10secs, 2 = 5mins, 3 = 1hr, 4 = 6 hrs, 5 = 12hrs, 6 = 1 day, 7 = 3 days, 8 = 1wk, 9 = 1month

extern float 
voltageBatteryMax       ,     //   USER PARAMETER - Maximum Battery Charging Voltage (Output V)
voltageBatteryMin       ,     //   USER PARAMETER - Minimum Battery Charging Voltage (Output V)
currentCharging         ;     //   USER PARAMETER - Maximum Charging Current (A - Output)


//================================== CALIBRATION PARAMETERS =======================================//
// The parameters below can be tweaked for designing your own MPPT charge controllers. Only modify //
// the values below if you know what you are doing. The values below have been pre-calibrated for  //
// MPPT charge controllers designed by TechBuilder (Angelo S. Casimiro)                            //
//=================================================================================================//
extern int
ADC_GainSelect          ,          //  CALIB PARAMETER - ADC Gain Selection (0→±6.144V 3mV/bit, 1→±4.096V 2mV/bit, 2→±2.048V 1mV/bit)
avgCountVS              ,          //  CALIB PARAMETER - Voltage Sensor Average Sampling Count (Recommended: 3)
avgCountCS              ,          //  CALIB PARAMETER - Current Sensor Average Sampling Count (Recommended: 4)
avgCountTS              ;        //  CALIB PARAMETER - Temperature Sensor Average Sampling Count
extern float
inVoltageDivRatio       ,    //  CALIB PARAMETER - Input voltage divider sensor ratio (change this value to calibrate voltage sensor)
outVoltageDivRatio      ,    //  CALIB PARAMETER - Output voltage divider sensor ratio (change this value to calibrate voltage sensor)
vOutSystemMax           ,    //  CALIB PARAMETER - 
cOutSystemMax           ,    //  CALIB PARAMETER - 
ntcResistance           ,   //  CALIB PARAMETER - NTC temp sensor's resistance. Change to 10000.00 if you are using a 10k NTC
voltageDropout          ,     //  CALIB PARAMETER - Buck regulator's dropout voltage (DOV is present due to Max Duty Cycle Limit)
voltageBatteryThresh    ,     //  CALIB PARAMETER - Power cuts-off when this voltage is reached (Output V)
currentInAbsolute       ,    //  CALIB PARAMETER - Maximum Input Current The System Can Handle (A - Input)
currentOutAbsolute      ,    //  CALIB PARAMETER - Maximum Output Current The System Can Handle (A - Input)
PPWM_margin             ,    //  CALIB PARAMETER - Minimum Operating Duty Cycle for Predictive PWM (%)
PWM_MaxDC               ,    //  CALIB PARAMETER - Maximum Operating Duty Cycle (%) 90%-97% is good
efficiencyRate          ,     //  CALIB PARAMETER - Theroretical Buck Efficiency (% decimal)
currentMidPoint         ,     //  CALIB PARAMETER - Current Sensor Midpoint (V)
currentSensV            ,     //  CALIB PARAMETER - Current Sensor Sensitivity (mV/A)
vInSystemMin            ;     //  CALIB PARAMETER - 

//===================================== SYSTEM PARAMETERS =========================================//
// Do not change parameter values in this section. The values below are variables used by system   //
// processes. Changing the values can damage the MPPT hardware. Kindly leave it as is! However,    //
// you can access these variables to acquire data needed for your mods.                            //
//=================================================================================================//
extern bool
buck_enabled            ,           // SYSTEM PARAMETER - Buck Enable Status
fan_enabled             ,           // SYSTEM PARAMETER - Fan activity status (1 = On, 0 = Off)
bypass_enabled          ,           // SYSTEM PARAMETER - 
chargingPause         ,           // SYSTEM PARAMETER - 
buttonRightStatus     ,           // SYSTEM PARAMETER -
buttonLeftStatus      ,           // SYSTEM PARAMETER - 
buttonBackStatus      ,           // SYSTEM PARAMETER - 
buttonSelectStatus    ,           // SYSTEM PARAMETER -
buttonRightCommand    ,           // SYSTEM PARAMETER - 
buttonLeftCommand     ,           // SYSTEM PARAMETER - 
buttonBackCommand     ,           // SYSTEM PARAMETER - 
buttonSelectCommand   ,           // SYSTEM PARAMETER -
settingMode           ,           // SYSTEM PARAMETER -
setMenuPage           ,           // SYSTEM PARAMETER -
boolTemp              ,           // SYSTEM PARAMETER -
flashMemLoad          ,           // SYSTEM PARAMETER -  
confirmationMenu      ,           // SYSTEM PARAMETER -      
WIFI                  ;           // SYSTEM PARAMETER - 

extern int
inputSource           ,           // SYSTEM PARAMETER - 0 = MPPT has no power source, 1 = MPPT is using solar as source, 2 = MPPTis using battery as power source
avgStoreTS            ,           // SYSTEM PARAMETER - Temperature Sensor uses non invasive averaging, this is used an accumulator for mean averaging
temperature           ,           // SYSTEM PARAMETER -
sampleStoreTS         ,           // SYSTEM PARAMETER - TS AVG nth Sample
pwmMax                ,           // SYSTEM PARAMETER -
pwmMaxLimited         ,           // SYSTEM PARAMETER -
PWM                   ,           // SYSTEM PARAMETER -
PPWM                  ,           // SYSTEM PARAMETER -
pwmChannel            ,           // SYSTEM PARAMETER -
batteryPercent        ,           // SYSTEM PARAMETER -
menuPage              ,           // SYSTEM PARAMETER -
subMenuPage           ,           // SYSTEM PARAMETER -
conv1                 ,           // SYSTEM PARAMETER -
conv2                 ,           // SYSTEM PARAMETER -
intTemp               ;           // SYSTEM PARAMETER -

extern mppt_error err;


extern float
VSI                   ,      // SYSTEM PARAMETER - Raw input voltage sensor ADC voltage
VSO                   ,      // SYSTEM PARAMETER - Raw output voltage sensor ADC voltage
CSI                   ,      // SYSTEM PARAMETER - Raw current sensor ADC voltage
CSI_converted         ,      // SYSTEM PARAMETER - Actual current sensor ADC voltage 
TS                    ,      // SYSTEM PARAMETER - Raw temperature sensor ADC value
powerInput            ,      // SYSTEM PARAMETER - Input power (solar power) in Watts
powerInputPrev        ,      // SYSTEM PARAMETER - Previously stored input power variable for MPPT algorithm (Watts)
powerOutput           ,      // SYSTEM PARAMETER - Output power (battery or charing power in Watts)
voltageInput          ,      // SYSTEM PARAMETER - Input voltage (solar voltage)
voltageInputPrev      ,      // SYSTEM PARAMETER - Previously stored input voltage variable for MPPT algorithm
voltageOutput         ,      // SYSTEM PARAMETER - Input voltage (battery voltage)
currentInput          ,      // SYSTEM PARAMETER - Output power (battery or charing voltage)
currentOutput         ,      // SYSTEM PARAMETER - Output current (battery or charing current in Amperes)
TSlog                 ,      // SYSTEM PARAMETER - Part of NTC thermistor thermal sensing code
ADC_BitReso           ,      // SYSTEM PARAMETER - System detects the approriate bit resolution factor for ADS1015/ADS1115 ADC
energy_wh                    ,      // SYSTEM PARAMETER - Stores the accumulated energy harvested (Watt-Hours)
outputDeviation       ,      // SYSTEM PARAMETER - Output Voltage Deviation (%)
buckEfficiency        ,      // SYSTEM PARAMETER - Measure buck converter power conversion efficiency (only applicable to my dual current sensor version)
floatTemp             ,
vOutSystemMin         ;     //  CALIB PARAMETER - 
extern unsigned long 
currentErrorMillis    ,           //SYSTEM PARAMETER -
currentButtonMillis   ,           //SYSTEM PARAMETER -
currentRoutineMillis  ,           //SYSTEM PARAMETER -
currentWiFiMillis     ,           //SYSTEM PARAMETER - 
currentMenuSetMillis  ,           //SYSTEM PARAMETER - 
prevButtonMillis      ,           //SYSTEM PARAMETER -
prevRoutineMillis     ,           //SYSTEM PARAMETER -
prevErrorMillis       ,           //SYSTEM PARAMETER -
prevWiFiMillis        ,           //SYSTEM PARAMETER -
secondsElapsed        ;           //SYSTEM PARAMETER - 