#include "lpc17xx_pinsel.h"

char labels[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};


void checkrow(char b, char mask, int row, void (*action)(int));
void keypad_check(void (*action)(int));
