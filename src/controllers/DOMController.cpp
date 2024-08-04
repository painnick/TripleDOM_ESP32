#include "DOMController.h"

// Logger
#define DOM_TAG "DOM"

DOMController::DOMController(int table, int arm, int eye, int bazuka) :
        _TablePin(table),
        _ArmPin(arm),
        _EyeSRIndex(eye),
        _BazukaSRIndex(bazuka) {
}

void DOMController::setup() {
    servoTable.attach(_TablePin, 90);
    servoTable.setEasingType(EASE_LINEAR);
    servoArm.attach(_ArmPin, 0);
    servoArm.setEasingType(EASE_LINEAR);
}

void DOMController::turnTable() {
    auto degreesPerSecond = (int) random(30, 60);
    ESP_LOGD(DOM_TAG, "(TurnTable) Degrees per second is %d", degreesPerSecond);
    servoTable.easeTo(90 + (int) random(15, 45), degreesPerSecond);
    delay(500);
    servoTable.easeTo(90 - (int) random(15, 45), degreesPerSecond);
    delay(500);
}

void DOMController::turnArm() {
    auto degreesPerSecond = (int) random(60, 90);
    ESP_LOGD(DOM_TAG, "(Table) Degrees per second is %d", degreesPerSecond);
    servoArm.easeTo(45, degreesPerSecond);
    delay(2 * 1000);
    servoArm.easeTo(0, degreesPerSecond);
}

void DOMController::loop() {
    // Do something
}