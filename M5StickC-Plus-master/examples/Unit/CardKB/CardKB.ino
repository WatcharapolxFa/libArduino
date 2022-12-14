#include <M5StickCPlus.h>
#include <Wire.h>

#define CARDKB_ADDR 0x5F

void setup() {
    M5.begin();
    Wire.begin(32, 33);
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(1, 10);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
    M5.Lcd.printf("IIC Address: 0x5F\n");
    M5.Lcd.printf(">>");
}
void loop() {
    Wire.requestFrom(CARDKB_ADDR, 1);
    while (Wire.available()) {
        char c = Wire.read();  // receive a byte as characterif
        if (c != 0) {
            M5.Lcd.printf("%c", c);
            Serial.println(c, HEX);
            // M5.Speaker.beep();
        }
    }
    // delay(10);
}
