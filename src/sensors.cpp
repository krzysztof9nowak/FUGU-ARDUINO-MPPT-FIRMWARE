#include <Arduino.h>
#include <defines.h>
#include <variables.h>
#include <Adafruit_ADS1X15.h>
#include <sensors.h>

extern Adafruit_ADS1015 ads;

void adc_set_gain(){
  if(ADC_GainSelect==0){ads.setGain(GAIN_TWOTHIRDS);ADC_BitReso= 0.1875;}  // Gain: 2/3x  Range: +/- 6.144V
  else if(ADC_GainSelect==1){ads.setGain(GAIN_ONE);ADC_BitReso= 0.125;}    // Gain: 1x    Range: +/- 4.096V  
  else if(ADC_GainSelect==2){ads.setGain(GAIN_TWO);ADC_BitReso= 0.0625;}   // Gain: 2x    Range: +/- 2.048V    
}

void resetVariables(){
  secondsElapsed = 0;
}

void Read_Sensors(){
  /////////// TEMPERATURE SENSOR /////////////
  if(sampleStoreTS<=avgCountTS){                               //TEMPERATURE SENSOR - Lite Averaging
    // TS = TS + analogRead(TempSensor);
    sampleStoreTS++;   
  }
  else{
    TS = TS/sampleStoreTS;
    TSlog = log(ntcResistance*(4095.00/TS-1.00));
    temperature = (1.0/(1.009249522e-03+2.378405444e-04*TSlog+2.019202697e-07*TSlog*TSlog*TSlog))-273.15;
    sampleStoreTS = 0;
    TS = 0;
  }
  /////////// VOLTAGE & CURRENT SENSORS /////////////
  VSI = 0.0000;      //Clear Previous Input Voltage 
  VSO = 0.0000;      //Clear Previous Output Voltage  
  CSI = 0.0000;      //Clear Previous Current  

  //VOLTAGE SENSOR - Instantenous Averaging   
  for(int i = 0; i<avgCountVS; i++){
    VSI = VSI + ads.computeVolts(ads.readADC_SingleEnded(3));
    VSO = VSO + ads.computeVolts(ads.readADC_SingleEnded(1));
  }
  voltageInput  = (VSI/avgCountVS)*inVoltageDivRatio; 
  voltageOutput = (VSO/avgCountVS)*outVoltageDivRatio; 

  
  //CURRENT SENSOR - Instantenous Averaging   
  for(int i = 0; i<avgCountCS; i++){
    CSI = CSI + ads.computeVolts(ads.readADC_SingleEnded(2));
  }
  CSI_converted = (CSI/avgCountCS)*1.325;
  currentInput  = ((CSI_converted-currentMidPoint)*-1)/currentSensV;  
  if(currentInput<0){currentInput=0.0000;}
  if(voltageOutput<=0){currentOutput = 0.0000;}
  else{currentOutput = (voltageInput*currentInput)/voltageOutput;}

  //POWER SOURCE DETECTION
  if(voltageInput<=3 && voltageOutput<=3){inputSource=0;}  //System is only powered by USB port
  else if(voltageInput>voltageOutput)    {inputSource=1;}  //System is running on solar as power source
  else if(voltageInput<voltageOutput)    {inputSource=2;}  //System is running on batteries as power source
  
  //////// AUTOMATIC CURRENT SENSOR CALIBRATION ////////
  bool no_errors_for_calibration = (err & (mppt_error::FATALLY_LOW_VOLTAGE | mppt_error::OUTPUT_OVERVOLTAGE)) == mppt_error::OK;
  if(buck_enabled==0 && no_errors_for_calibration){                 
    currentMidPoint = ((CSI/avgCountCS)*1.3250)-0.003;
  }
  
  //POWER COMPUTATION - Through computation
  powerInput      = voltageInput*currentInput;
  powerOutput     = voltageInput*currentInput*efficiencyRate;
  outputDeviation = (voltageOutput/voltageBatteryMax)*100.000;

  //STATE OF CHARGE - Battery Percentage
  batteryPercent  = ((voltageOutput-voltageBatteryMin)/(voltageBatteryMax-voltageBatteryMin))*101;
  batteryPercent  = constrain(batteryPercent,0,100);

  //TIME DEPENDENT SENSOR DATA COMPUTATION
  currentRoutineMillis = millis();
  if(currentRoutineMillis-prevRoutineMillis>=millisRoutineInterval){   //Run routine every millisRoutineInterval (ms)
    prevRoutineMillis = currentRoutineMillis;                          //Store previous time
    energy_wh = energy_wh+(powerInput/(3600.000*(1000.000/millisRoutineInterval)));  //Accumulate and compute energy harvested (3600s*(1000/interval))
  } 

  //OTHER DATA
  secondsElapsed = millis()/1000;                                      //Gets the time in seconds since the was turned on  and active
}
