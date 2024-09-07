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
#include "controllers/DOMController.h"

DOMController DOM1(PIN_SERVO1_TABLE, PIN_SERVO1_ARM, SR_EYE1, SR_BAZUKA1);
DOMController DOM2(PIN_SERVO2_TABLE, PIN_SERVO2_ARM, SR_EYE2, SR_BAZUKA2);
DOMController DOM3(PIN_SERVO3_TABLE, PIN_SERVO3_ARM, SR_EYE3, SR_BAZUKA3);

void setup() {
    setupSound();

    DOM1.setup();
    DOM2.setup();
    DOM3.setup();

    delay(2000);

    dfmp3.loopFolder(1); // BGM
    dfmp3.loop();

    ESP_LOGI(MAIN_TAG, "It's all set up.");
}

void loop() {
    ESP_LOGD(MAIN_TAG, "Start this loop!");

    auto aroundCount1 = (int) random(1, 3);
    for (auto i = 0; i < aroundCount1; i++) {
        DOM1.turnTable();
    }
    auto aroundCount2 = (int) random(1, 3);
    for (auto i = 0; i < aroundCount2; i++) {
        DOM2.turnTable();
    }
    auto aroundCount3 = (int) random(1, 3);
    for (auto i = 0; i < aroundCount3; i++) {
        DOM3.turnTable();
    }

    delay(1 * 1000);

    DOM1.turnArm();
    DOM2.turnArm();
    DOM3.turnArm();

    ESP_LOGD(MAIN_TAG, "Ends this loop.");

    delayWithLoop(2 * 1000);
}
