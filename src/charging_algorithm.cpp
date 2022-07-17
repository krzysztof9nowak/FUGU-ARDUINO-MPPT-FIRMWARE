#include <Arduino.h>
#include <defines.h>
#include <variables.h>
#include <sensors.h>
#include <charging_algorithm.h>
#include <esp_log.h>

static const char* TAG = "charging";

void buck_enable(){                                                                  //Enable MPPT Buck Converter
  buck_enabled = 1;
  digitalWrite(buck_EN,HIGH);
  digitalWrite(LED,HIGH);
}
void buck_disable(){                                                                 //Disable MPPT Buck Converter
  buck_enabled = 0; 
  digitalWrite(buck_EN,LOW);
  digitalWrite(LED,LOW);
  PWM = 0;
}   
void predictivePWM(){                                                                //PREDICTIVE PWM ALGORITHM 
  if(voltageInput<=0){PPWM=0;}                                                       //Prevents Indefinite Answer when voltageInput is zero
  else{PPWM =(PPWM_margin*pwmMax*voltageOutput)/(100.00*voltageInput);}              //Compute for predictive PWM Floor and store in variable
  PPWM = constrain(PPWM,0,pwmMaxLimited);
}   

void PWM_Modulation(){
  if(output_mode==0){PWM = constrain(PWM,0,pwmMaxLimited);}                          //PSU MODE PWM = PWM OVERFLOW PROTECTION (limit floor to 0% and ceiling to maximim allowable duty cycle)
  else{
    predictivePWM();                                                                 //Runs and computes for predictive pwm floor
    PWM = constrain(PWM,PPWM,pwmMaxLimited);                                         //CHARGER MODE PWM - limit floor to PPWM and ceiling to maximim allowable duty cycle)                                       
  } 
  ledcWrite(pwmChannel,PWM);                                                         //Set PWM duty cycle and write to GPIO when buck is enabled
  buck_enable();                                                                     //Turn on MPPT buck (IR2104)
}
     
void Charging_Algorithm(){
  if(err != mppt_error::OK || chargingPause==1){buck_disable();}                                       //ERROR PRESENT  - Turn off MPPT buck when error is present or when chargingPause is used for a pause override
  else{
    if(PWM == 0 && false){
      buck_disable();                                                                //Disable buck before PPWM initialization
      ESP_LOGI(TAG, "Solar panel detected");
      delay(1000);

      Read_Sensors();
      predictivePWM();
      PWM = PPWM;
    }  
    else{                                                                            //NO ERROR PRESENT  - Continue power conversion              
      int step_size = 1;
      /////////////////////// CC-CV BUCK PSU ALGORITHM ////////////////////////////// 
      if(MPPT_mode==0){                                                              //CC-CV PSU MODE
        if(currentOutput>currentCharging)       {PWM-=step_size;}                             //Current Is Above → Decrease Duty Cycle
        else if(voltageOutput>voltageBatteryMax){PWM-=step_size;}                             //Voltage Is Above → Decrease Duty Cycle   
        else if(voltageOutput<voltageBatteryMax){PWM+=step_size;}                             //Increase duty cycle when output is below charging voltage (for CC-CV only mode)
      }     
        /////////////////////// MPPT & CC-CV CHARGING ALGORITHM ///////////////////////  
      else{                                                                                                                                                         
        if(currentOutput>currentCharging){PWM-=step_size;}                                      //Current Is Above → Decrease Duty Cycle
        else if(voltageOutput>voltageBatteryMax){PWM-=step_size;}                               //Voltage Is Above → Decrease Duty Cycle   
        else{                                                                          //MPPT ALGORITHM
          if(powerInput>powerInputPrev && voltageInput>voltageInputPrev)     {PWM-=step_size;}  //  ↑P ↑V ; →MPP  //D--
          else if(powerInput>powerInputPrev && voltageInput<voltageInputPrev){PWM+=step_size;}  //  ↑P ↓V ; MPP←  //D++
          else if(powerInput<powerInputPrev && voltageInput>voltageInputPrev){PWM+=step_size;}  //  ↓P ↑V ; MPP→  //D++
          else if(powerInput<powerInputPrev && voltageInput<voltageInputPrev){PWM-=step_size;}  //  ↓P ↓V ; ←MPP  //D--
          else if(voltageOutput<voltageBatteryMax)                           {PWM+=step_size;}  //  MP MV ; MPP Reached - 
          powerInputPrev   = powerInput;                                               //Store Previous Recorded Power
          voltageInputPrev = voltageInput;                                             //Store Previous Recorded Voltage        
        }   
      }
      PWM_Modulation();                                                              //Set PWM signal to Buck PWM GPIO                                                                       
    }
  }
}
