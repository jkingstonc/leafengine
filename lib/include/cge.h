#include <windows.h>
#include <time.h>
#include "maths.h"

#ifndef CGE_H
#define CGE_H

#define WIDTH 100
#define HEIGHT 50

#define FONT_SIZE_X 12
#define FONT_SIZE_Y 15

/* Colours use ASCII + Extended Ascii encoding */
#define SYMBOL_SHADE_LIGHT 176
#define SYMBOL_SHADE_MEDIUM 177
#define SYMBOL_SHADE_FULL 178
#define SYMBOL_FILL 219
#define SYMBOL_RECTANGLE_SMALL 220
#define SYMBOL_PILLAR_LEFT 221
#define SYMBOL_PILLAR_RIGHT 222
#define SYMBOL_RECTANGLE_LARGE 223
#define SYMBOL_SQUARE 254

/* 16 Colour range, 16 backgrounds, 256 colour and background combinations */
#define COLOUR_BLACK 0
#define COLOUR_DARK_BLUE 1
#define COLOUR_GREEN 2
#define COLOUR_LIGHT_BLUE 3
#define COLOUR_RED 4
#define COLOUR_PURPLE 5
#define COLOUR_YELLOW 6
#define COLOUR_LIGHT_GRAY 7
#define COLOUR_GRAY 8
#define COLOUR_BLUE 9
#define COLOUR_LIGHT_GREEN 10
#define COLOUR_TEAL 11
#define COLOUR_LIGHT_RED 12
#define COLOUR_MAGENTA 13
#define COLOUR_CREAM 14
#define COLOUR_WHITE 15
/* Colour macros can be extended further to include backgrounds */


/* write (output) handle */
extern HANDLE writeHandler;
/* read (input) handle */
extern HANDLE readHandler;

/* Hold input records */
extern INPUT_RECORD input;

/* Interaction events */
extern DWORD dwEvents;
/* Previous console display mode */
extern DWORD dwPreviousMode;
/* New console display mode */
extern DWORD dwNewMode;

/* Window size coordinates, be sure to start index at zero! */
extern SMALL_RECT windowSize;

/* A COORD struct for specificying the console's screen buffer dimensions */
extern COORD bufferSize;

/* Setting up different variables for passing to WriteConsoleOutput */
extern COORD characterBufferSize;
extern COORD characterPosition;
extern SMALL_RECT consoleWriteArea;

/* A CHAR_INFO structure containing data about a single character */
extern CHAR_INFO consoleBuffer[WIDTH * HEIGHT];

/* Window title */
extern char * title;

/* Current time variables */
extern clock_t startTimer, endTimer;
/* Time between frames */
extern double deltaTime;
/* Track render time delay */
extern double updateTimer;
/* Render time delay (desired FPS)*/
extern double updateTime;
/* track FPS */
extern double FPS;
/* Game loop control variable */
extern int running;


/* Engine functionality */
/* Setup main window functionalities */
void setupCge();
/* Exit function */
void exitCge();
/* Initialise window settings (must be called when changes are made) */
void setWindowInfo();
/* Set window title */
void setTitle(char * t);
/* Set font size */
void setFont(int sx, int sy);

/* Process the time events, rendering events and post-processing events */
void process();
/* Render the screen buffer */
void render();

/* Character Functionality */
/* Write single character to the screen buffer */
void writeChar(int x, int y, int colour, char c);
/* Read single character from the screen buffer */
char readChar(int x, int y);

/* Character Array Functionality */
/* Write character array (string) to the screen buffer */
void writeCharArray(int x, int y, int colour, char * array);
/* Read a character array (string) from the screen buffer */
void readCharArray(int x0, int y0, int x1, int y1, int ** array);

/* Draw Abstract Functionality */
/* Draw a line between 2 points to the screen buffer */
void drawLine(int x0, int y0, int x1, int y1, int colour, int c);
/* Draw a triangle comprised of 3 points to the screen buffer */
void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int colour, int c);
/* Draw a circle with a center and a radius to the screen buffer */
void drawCircle(int cx, int cy, int r, int colour, int c);
/* Fill between 2 points to the screen buffer */
void fill(int x0, int y0, int x1, int y1,int colour, int c);

/* Text Functionality */

/* Other Functionality */
/* Clear buffer by setting buffer to a single colour & character */
void clear(int colour,char c);

#endif