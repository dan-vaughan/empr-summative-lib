#include "main.h"
#include "display.h"

void reset()
{
	#define LEN 3
    uint8_t cmd[LEN] = 
	   {0b00000000,  // Control byte for Instruction
    	0b00110100,  // Choose Standard instruction set
    	0b00000001}; // Clear the display

	i2c.write(DISPLAY, cmd, LEN);
}

void setup_display()
{
	#define LEN 10
    uint8_t cmd[LEN] = 
	   {0b00000000,  // Control byte for Instruction
    	0b00110100,  // Choose Standard instruction set
   		0b00001100,  // D: Display on, C: curser off, B: blink off
    	0b00000110,	 // I/D: increment, S: no shift
    	0b00110111,	 // Choose Extended instruction set
    	0b00000100,	 // P: left to right, Q: top to bottom
    	0b10011111,	 // Calculate Vlcd with factor '111111' -> Va
    	0b00110100,	 // Choose Standard instruction set
    	0b10000000,  // Set DDRAM address to 0
    	0b00000010}; // return home

	i2c.write(DISPLAY, cmd, LEN);
}

void return_home()
{
	#define LEN 2 
	uint8_t cmd[LEN] = {0x00, 0x02};
	i2c.write(DISPLAY, cmd, LEN);
}

void shift_line()
{
	#define LEN 2 
	uint8_t cmd[LEN] = {0x00, 0xc0};
	i2c.write(DISPLAY, cmd, LEN);
}

void cursor_shift(Shift_Type t, int amount){
	#define LEN 2
	int i;

	if(t==LEFT){		
			uint8_t cmd[LEN] = {0x00, 0x10};
			for (i = 0; i < amount; i++){
				i2c.write(DISPLAY, cmd, LEN);
			}
		}

	if(t==RIGHT){
			uint8_t cmd[LEN] = {0x00, 0x14};
			for (i = 0; i < amount; i++){
				i2c.write(DISPLAY, cmd, LEN);
			}
	}
}

void printchar(char ascii)
{
	#define LEN 2
    uint8_t cmd[LEN] =
	   {0b01000000,  // Control byte for Data
		0x80 + ascii};

	i2c.write(DISPLAY, cmd, LEN);
}

void putcustom(char custom){
	uint8_t cmd[2] =
	 {0b01000000,  // Control byte for Data
	custom};
	i2c.write(DISPLAY, cmd, 2);
}

void printstr(char * str)
{
    int i = 0;
    
    while (str[i] != 0)
    {
        printchar(str[i]);
        i++;        
    }   
}

void clear_display()
{
	printstr("                ");
	shift_line();
	printstr("                ");
	return_home();
}

