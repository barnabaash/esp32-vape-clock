#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <esp_timer.h>
#include <SmokeDisplay.h>

const char* WIFI_SSID = "SSID";
const char* WIFI_PASS = "password";

//                   A  B  C  D  E  F
DisplaySolo4 hourDisp(0, 1, 3, 4, 5, 6);
DisplaySolo4 minDisp (7, 10, 20, 21, 2, 8);

// Charlieplex: gyakran kell hívni az update()-et (21 szegmens)
static void refreshCb(void*) {
  hourDisp.update();
  minDisp.update();
}

void setup() {
  hourDisp.begin();
  minDisp.begin();

  esp_timer_create_args_t args = {};
  args.callback = refreshCb;
  args.dispatch_method = ESP_TIMER_TASK;
  args.name = "disp";
  esp_timer_handle_t timer;
  esp_timer_create(&args, &timer);
  esp_timer_start_periodic(timer, 300);   // 300 µs -> ~160 Hz frissítés

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", "pool.ntp.org", "time.google.com");
}

void loop() {
  static int lastH = -1, lastM = -1;
  struct tm t;
  if (getLocalTime(&t, 0)) {
    if (t.tm_hour != lastH) { lastH = t.tm_hour; hourDisp.set(lastH); }
    if (t.tm_min  != lastM) { lastM = t.tm_min;  minDisp.set(lastM); }
  }

  static uint32_t lastBlink = 0;
  static bool on = false;
  if (millis() - lastBlink >= 500) {
    lastBlink = millis();
    on = !on;
    if (on) { minDisp.batteryGreen(); minDisp.dropletGreen(); }
    else    { minDisp.batteryOff();   minDisp.dropletOff();   }
  }
}