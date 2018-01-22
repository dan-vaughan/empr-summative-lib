#include "i2c.h"
#include "serial.h"
#include "analog.h"

#define DISPLAY 0x3B
#define KEYPAD 0x21

extern I2C i2c;
extern Serial pc;
extern AnalogIn ain;
extern AnalogOut aout;
