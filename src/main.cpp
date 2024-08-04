#include <Arduino.h>

// Logger
#define MAIN_TAG "main"

// Servo
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 6
#define DISABLE_MICROS_AS_DEGREE_PARAMETER
#include <ServoEasing.hpp>

// Program
#include "common.h"
#include "controllers/Mp3Controller.h"

ServoEasing servo1Arm;
ServoEasing servo1Table;

void setup() {
    servo1Arm.attach(PIN_SERVO1_ARM, 0);
    servo1Arm.setEasingType(EASE_LINEAR);
    servo1Table.attach(PIN_SERVO1_TABLE, 90);
    servo1Table.setEasingType(EASE_LINEAR);

    setupSound();

    delay(2000);

    dfmp3.loopFolder(1); // BGM
    dfmp3.loop();

    ESP_LOGI(MAIN_TAG, "It's all set up.");
}

void loop() {
    ESP_LOGD(MAIN_TAG, "Start this loop!");

    auto aroundCount = (int) random(1, 3);
    ESP_LOGD(MAIN_TAG, "Look around %d time(s).", aroundCount);

    for (auto i = 0; i < aroundCount; i++) {
        auto degreesPerSecond = (int) random(30, 60);
        ESP_LOGD(MAIN_TAG, "[%d] (Around) Degrees per second is %d", i + 1, degreesPerSecond);
        servo1Table.easeTo(90 + (int) random(15, 45), degreesPerSecond);
        delayWithLoop(500);
        servo1Table.easeTo(90 - (int) random(15, 45), degreesPerSecond);
        delayWithLoop(500);
    }

    delay(1 * 1000);

    {
        auto degreesPerSecond = (int) random(60, 90);
        ESP_LOGD(MAIN_TAG, "(Table) Degrees per second is %d", degreesPerSecond);
        servo1Arm.easeTo(45, degreesPerSecond);
        delayWithLoop(2 * 1000);
        servo1Arm.easeTo(0, degreesPerSecond);
    }

    ESP_LOGD(MAIN_TAG, "Ends this loop.");

    delayWithLoop(2 * 1000);
}
