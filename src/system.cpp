#include <Arduino.h>
#include <defines.h>
#include <variables.h>
#include <EEPROM.h>                 //SYSTEM PARAMETER  - EEPROM Library (By: Arduino)
#include <system.h>
#include <sensors.h>

void System_Processes(){
  ///////////////// FAN COOLING /////////////////
  if(enableFan==true){
    if(enableDynamicCooling==false){                                   //STATIC PWM COOLING MODE (2-PIN FAN - no need for hysteresis, temp data only refreshes after 'avgCountTS' or every 500 loop cycles)                       
      if(overrideFan==true){fan_enabled=true;}                           //Force on fan
      else if(temperature>=temperatureFan){fan_enabled=1;}               //Turn on fan when set fan temp reached
      else if(temperature<temperatureFan){fan_enabled=0;}                //Turn off fan when set fan temp reached
      digitalWrite(FAN,fan_enabled);                                     //Send a digital signal to the fan MOSFET
    }
    else{}                                                             //DYNAMIC PWM COOLING MODE (3-PIN FAN - coming soon)
  }
  else{digitalWrite(FAN,LOW);}                                         //Fan Disabled
  
  //////////// LOOP TIME STOPWATCH ////////////
  loopTimeStart = micros();                                            //Record Start Time
  loopTime = (loopTimeStart-loopTimeEnd)/1000.000;                     //Compute Loop Cycle Speed (mS)
  loopTimeEnd = micros();                                              //Record End Time


  ///////////// LOW POWER MODE /////////////
  if(lowPowerMode==1){}   
  else{}      
}