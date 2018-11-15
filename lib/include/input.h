#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <conio.h>

/* Check if keyboard is being pressed */
int keyPressed();
/* Return keypress as char (ASCII + Extended ASCII) */
int getKey();

/* Check if left mouse button is clicked */
int leftMouseClick();
/* Check if right mouse button is clicked */
int rightMouseClick();
/* Check for double click */
int doubleClick();

/* Return mouse position x */
int getMouseX();
/* Return mouse position y */
int getMouseY();

#endif