#include "lpc_types.h"
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "pindef.h"
#include "keypad.h"
#include "display.h"

#include <math.h>
#define DEFAULT 1000
#define MAX_AMP 5
#define TIME 100
#define PI 3.14159265358979323846
#define FACTOR 1000

I2C i2c(SDA, SCL);        // sda, scl
Serial pc(1); // tx, rx
Serial port(2);

int main()
{
	pc.write("hello world\n\r");
	char buf[64];
	while (1)
	{
		char one[] = {0xAA};
		char zero[] = {0x00};

		char msg[] = {0xff, 0x00, 0xff};

		//pc.write("I am printing more stuff!");
		port.read(buf);
		sprintf(buf, "%#x ");	
		pc.write(buf);
	}
}
