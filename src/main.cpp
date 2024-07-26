#include <Arduino.h>

#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 6
#define DISABLE_MICROS_AS_DEGREE_PARAMETER
#include <ServoEasing.hpp>

#define MAIN_TAG "main"

#define PIN_SERVO_ARM 27
#define PIN_SERVO_TABLE 13

ServoEasing servoArm;
ServoEasing servoTable;

void setup() {
    servoArm.attach(PIN_SERVO_ARM, 0);
    servoArm.setEasingType(EASE_LINEAR);
    servoTable.attach(PIN_SERVO_TABLE, 90);
    servoTable.setEasingType(EASE_LINEAR);

    delay(5000);

    ESP_LOGI(MAIN_TAG, "It's all set up.");
}

void loop() {
    ESP_LOGD(MAIN_TAG, "Start this loop!");

    auto aroundCount = (int) random(1, 3);
    ESP_LOGD(MAIN_TAG, "Look around %d time(s).", aroundCount);

    for (auto i = 0; i < aroundCount; i++) {
        auto degreesPerSecond = (int) random(30, 60);
        ESP_LOGD(MAIN_TAG, "[%d] (Around) Degrees per second is %d", i + 1, degreesPerSecond);
        servoTable.easeTo(90 + (int) random(15, 45), degreesPerSecond);
        delay(500);
        servoTable.easeTo(90 - (int) random(15, 45), degreesPerSecond);
        delay(500);
    }

    delay(1 * 1000);

    {
        auto degreesPerSecond = (int) random(60, 90);
        ESP_LOGD(MAIN_TAG, "(Table) Degrees per second is %d", degreesPerSecond);
        servoArm.easeTo(45, degreesPerSecond);
        delay(2 * 1000);
        servoArm.easeTo(0, degreesPerSecond);
    }

    ESP_LOGD(MAIN_TAG, "Ends this loop.");

    delay(2 * 1000);
}
