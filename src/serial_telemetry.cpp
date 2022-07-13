#include <Arduino.h>
#include <defines.h>
#include <variables.h>
#include <serial_telemetry.h>

#define SSHOW_INT(name, val) printf(name ": %d ", val)
#define SHOW_INT(x) SSHOW_INT(#x, x)

#define SSHOW_FLOAT(name, val, prec) printf(name ": %." #prec "f ", val)
#define SHOW_FLOAT(x) SSHOW_FLOAT(#x, x, 3)

void Onboard_Telemetry(){    
  currentSerialMillis = millis();
  if(currentSerialMillis-prevSerialMillis>=millisSerialInterval){   //Run routine every millisRoutineInterval (ms)
    prevSerialMillis = currentSerialMillis;                         //Store previous time

    if(serialTelemMode==1){                                    // 1 - Display All        
      SHOW_INT(ERR);
      SHOW_INT(FLV);
      SHOW_INT(BNC);
      SHOW_INT(IUV);
      SHOW_INT(IOC);
      SHOW_INT(IOC); 
      SHOW_INT(OOV); 
      SHOW_INT(OOC);
      SHOW_INT(OTE); 
      SHOW_INT(REC);
      SHOW_INT(MPPT_mode);
      SHOW_INT(output_mode);

      printf("\n");
      SSHOW_INT("BYP", bypass_enabled);
      SSHOW_INT("EN", buck_enabled);
      SSHOW_INT("FAN", fan_enabled);
      SHOW_INT(WIFI);

      printf("\n");
      SSHOW_FLOAT("PI", powerInput, 0);
      SHOW_INT(PWM);
      SHOW_INT(PPWM);
      SSHOW_FLOAT("VI", voltageInput, 1);
      SSHOW_FLOAT("VO", voltageOutput, 1);
      SSHOW_FLOAT("CI", currentInput, 2);
      SSHOW_FLOAT("CO", currentOutput, 2);



      Serial.print(" Wh:");    Serial.print(Wh,2); 
      Serial.print(" Temp:");  Serial.print(temperature,1);  
      Serial.print(" "); 
      Serial.print(" CSMPV:"); Serial.print(currentMidPoint,3);  
      Serial.print(" CSV:");   Serial.print(CSI_converted,3);   
      Serial.print(" VO%Dev:");Serial.print(outputDeviation,1);   
      Serial.print(" SOC:");   Serial.print(batteryPercent);Serial.print("%"); 
      Serial.print(" T:");     Serial.print(secondsElapsed); 
      Serial.print(" LoopT:"); Serial.print(loopTime,3);Serial.print("ms");  
      printf("\n");
    }
    else if(serialTelemMode==2){ // 2 - Display Essential Data
      Serial.print(" PI:");    Serial.print(powerInput,0); 
      Serial.print(" PWM:");   Serial.print(PWM); 
      Serial.print(" PPWM:");  Serial.print(PPWM); 
      Serial.print(" VI:");    Serial.print(voltageInput,1); 
      Serial.print(" VO:");    Serial.print(voltageOutput,1); 
      Serial.print(" CI:");    Serial.print(currentInput,2); 
      Serial.print(" CO:");    Serial.print(currentOutput,2); 
      Serial.print(" Wh:");    Serial.print(Wh,2); 
      Serial.print(" Temp:");  Serial.print(temperature,1);  
      Serial.print(" EN:");    Serial.print(buck_enabled);
      Serial.print(" FAN:");   Serial.print(fan_enabled);   
      Serial.print(" SOC:");   Serial.print(batteryPercent);Serial.print("%"); 
      Serial.print(" T:");     Serial.print(secondsElapsed); 
      Serial.print(" LoopT:"); Serial.print(loopTime,3);Serial.print("ms");  
      printf("\n");
    }

  } 
}
