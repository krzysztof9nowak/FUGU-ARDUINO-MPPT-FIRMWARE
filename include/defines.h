#pragma once

//====================================== USER PARAMETERS ===========================================//
// The parameters below are the default parameters used when the MPPT charger settings have not     //
// been set or saved through the LCD menu interface or mobile phone WiFi app. Some parameters here  //
// would allow you to override or unlock features for advanced users (settings not on the LCD menu) //
//==================================================================================================//
#define backflow_MOSFET 27          //SYSTEM PARAMETER - Backflow MOSFET
#define buck_IN         33          //SYSTEM PARAMETER - Buck MOSFET Driver PWM Pin
#define buck_EN         32          //SYSTEM PARAMETER - Buck MOSFET Driver Enable Pin
#define LED             2           //SYSTEM PARAMETER - LED Indicator GPIO Pin
#define FAN             16          //SYSTEM PARAMETER - Fan GPIO Pin
#define ADC_ALERT       34          //SYSTEM PARAMETER - Fan GPIO Pin
#define TempSensor      35          //SYSTEM PARAMETER - Temperature Sensor GPIO Pin
#define buttonLeft      18          //SYSTEM PARAMETER - 
#define buttonRight     17          //SYSTEM PARAMETER -
#define buttonBack      19          //SYSTEM PARAMETER - 
#define buttonSelect    23          //SYSTEM PARAMETER -

