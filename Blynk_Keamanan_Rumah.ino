// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "TMPL3hpengtc"
#define BLYNK_DEVICE_NAME           "Alarm Rumah"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#define OBSTACLE 13
#define BUTTON 16
#define BUZZER 14

#include "BlynkEdgent.h"

BlynkTimer timer;

bool alarm = 0;

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(OBSTACLE, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  BlynkEdgent.begin();
  timer.setInterval(2000L, myTimerEvent);
}

void loop() {
  BlynkEdgent.run();
  timer.run();

  if (digitalRead(OBSTACLE) == 1) {
    alarm = 1;
  } else if (digitalRead(BUTTON) == 1) {
    alarm = 0;
  }

  if (alarm == 1) {
    timer.setTimeout(500L, alarmLow);
    timer.setTimeout(500L, alarmHigh);
  } else {
    noTone(BUZZER);
  }
}

void myTimerEvent()
{
  Blynk.virtualWrite(V0, alarm);
}

BLYNK_WRITE(V0)
{
  alarm = param.asInt();
}

void alarmLow() {
  tone(BUZZER, 1500);
}

void alarmHigh() {
  tone(BUZZER, 2000);
}
