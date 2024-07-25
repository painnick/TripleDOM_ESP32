#include <Arduino.h>
#include <ServoEasing.hpp>

#include "esp_log.h"

#define MAIN_TAG "main"

#define PIN_SERVO_ARM 27
#define PIN_SERVO_TABLE 12

#define DEGREES_PER_SECOND 30

ServoEasing servo1;
ServoEasing servo2;

void setup() {
    ESP_LOGI(MAIN_TAG, "Connecting OLED...");

    servo1.attach(PIN_SERVO_ARM, 0);
    servo1.setEasingType(EASE_LINEAR);
    servo2.attach(PIN_SERVO_TABLE, 90);
    servo2.setEasingType(EASE_LINEAR);

    delay(5000);
}

void loop() {
//    servo1.startEaseTo(90 - 20, DEGREES_PER_SECOND, START_UPDATE_BY_INTERRUPT);
//    delay(5 * 1000);

    servo2.easeTo(90 +45, DEGREES_PER_SECOND);
    servo2.easeTo(90 - 45, DEGREES_PER_SECOND);
    servo2.easeTo(90, DEGREES_PER_SECOND);

    delay(2 * 1000);

    servo1.easeTo(45, DEGREES_PER_SECOND);
    delay(3 * 1000);

    servo1.easeTo(0, DEGREES_PER_SECOND);
    delay(10 * 1000);
}
