#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_MP3_TX 33 // dfplayer(FIXED)
#define PIN_MP3_RX 32 // dfplayer(FIXED)

// DOM1
#define PIN_SERVO1_TABLE 14
#define PIN_SERVO1_ARM 17
#define SR_EYE1 0
#define SR_BAZUKA1 1

// DOM2
#define PIN_SERVO2_TABLE 4
#define PIN_SERVO2_ARM 18
#define SR_EYE2 2
#define SR_BAZUKA2 3

// DOM3
#define PIN_SERVO3_TABLE 19
#define PIN_SERVO3_ARM 23
#define SR_EYE3 4
#define SR_BAZUKA3 5
