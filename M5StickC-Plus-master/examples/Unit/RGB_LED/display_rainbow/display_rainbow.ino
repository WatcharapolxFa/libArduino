/*
    Please install FastLED library first.
    In arduino library manage search FastLED
*/
#include <M5StickCPlus.h>
#include "FastLED.h"

#define Neopixel_PIN 32
#define NUM_LEDS     30

CRGB leds[NUM_LEDS];
uint8_t gHue                              = 0;
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t userTaskHandle        = 0;

void setup() {
    M5.begin();
    // M5.Lcd.clear(BLACK);
    M5.Lcd.setRotation(3);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(20, 2);
    M5.Lcd.println("Neopixel Example");
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(15, 35);
    M5.Lcd.println("Display");
    M5.Lcd.setCursor(30, 55);
    M5.Lcd.println("rainbow effect");

    // Neopixel initialization
    FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(10);
    xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2,
                            NULL, 1);
}

void loop() {
}

void FastLEDshowESP32() {
    if (userTaskHandle == 0) {
        userTaskHandle = xTaskGetCurrentTaskHandle();
        xTaskNotifyGive(FastLEDshowTaskHandle);
        const TickType_t xMaxBlockTime = pdMS_TO_TICKS(200);
        ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
        userTaskHandle = 0;
    }
}

void FastLEDshowTask(void *pvParameters) {
    for (;;) {
        fill_rainbow(leds, NUM_LEDS, gHue, 7);  // rainbow effect
        FastLED.show();  // must be executed for neopixel becoming effective
        EVERY_N_MILLISECONDS(20) {
            gHue++;
        }
    }
}
