#ifndef TRIPLEDOM_ESP32_DOMCONTROLLER_H
#define TRIPLEDOM_ESP32_DOMCONTROLLER_H

#include <ServoEasing.h>

class DOMController {
public:
    DOMController(int table, int arm, int eye, int bazuka);
    void setup();
    void turnTable();
    void turnArm();
    void loop();

protected:
    int _TablePin;
    int _ArmPin;
    int _EyeSRIndex;
    int _BazukaSRIndex;

    ServoEasing servoArm;
    ServoEasing servoTable;
};

#endif //TRIPLEDOM_ESP32_DOMCONTROLLER_H
