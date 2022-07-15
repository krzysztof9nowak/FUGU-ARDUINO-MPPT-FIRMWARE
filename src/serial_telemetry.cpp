#include <Arduino.h>
#include <defines.h>
#include <serial_telemetry.h>
#include <variables.h>

#define SSHOW_INT(name, val) printf(name ": %d ", val)
#define SHOW_INT(x) SSHOW_INT(#x, x)

#define SSHOW_FLOAT(name, val, prec) printf(name ": %." #prec "f ", val)
#define SHOW_FLOAT(x) SSHOW_FLOAT(#x, x, 3)

void telemetry_task(void *) {
  while (true) {
    if (serialTelemMode == 1) { // 1 - Display All
      printf("---\n");
      SHOW_INT((int)err);
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
      printf("\n");

      SSHOW_FLOAT("Wh", energy_wh, 2);
      SSHOW_INT("temp", temperature);

      SSHOW_FLOAT("CSMPV", currentMidPoint, 3);
      SSHOW_FLOAT("CSV", CSI_converted, 3);
      SSHOW_FLOAT("VO Dev", outputDeviation, 1);
      SSHOW_INT("SOC", batteryPercent);
      SSHOW_INT("T", (int)secondsElapsed);
      printf("\n\n");
    } else if (serialTelemMode == 2) { // 2 - Display Essential Data
      printf("---\n");
      SSHOW_FLOAT("PI", powerInput, 0);
      SHOW_INT(PWM);
      SHOW_INT(PPWM);
      SSHOW_FLOAT("VI", voltageInput, 1);
      SSHOW_FLOAT("VO", voltageOutput, 1);
      SSHOW_FLOAT("CI", currentInput, 2);
      SSHOW_FLOAT("CO", currentOutput, 2);
      printf("\n");
      SSHOW_FLOAT("Wh", energy_wh, 2);
      SSHOW_INT("temp", temperature);
      SSHOW_INT("EN", buck_enabled);
      SSHOW_INT("FAN", fan_enabled);
      SSHOW_INT("SOC", batteryPercent);
      SSHOW_INT("T", (int)secondsElapsed);
      printf("\n\n");
    }
    delay(millisSerialInterval);
  }
}
