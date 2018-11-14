#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <conio.h>

/* Check if keyboard is being pressed */
int keyDown();
/* Return keypress as char (ASCII + Extended ASCII) */
int getKeyPress();

#endif