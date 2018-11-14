#include "include/cge.h"

/* Window size coordinates, be sure to start index at zero! */
SMALL_RECT windowSize = {0, 0, WIDTH, HEIGHT};

/* A COORD struct for specificying the console's screen buffer dimensions */
COORD bufferSize = {WIDTH, HEIGHT};

/* Setting up different variables for passing to WriteConsoleOutput */
COORD characterBufferSize = {WIDTH, HEIGHT};
COORD characterPosition = {0, 0};
SMALL_RECT consoleWriteArea = {0, 0, WIDTH, HEIGHT };

/* A CHAR_INFO structure containing data about a single character */
CHAR_INFO consoleBuffer[WIDTH * HEIGHT];

/* A variable to hold the font info */
CONSOLE_FONT_INFOEX lpConsoleCurrentFontEx;


/* write (output) handle */
HANDLE writeHandler;
/* read (input) handle */
HANDLE readHandler;

/* Title of window */
char * title = "CGE";

/* Current time variables */
clock_t startTimer, endTimer;
/* Time between frames */
double deltaTime;
/* Track render time delay */
double updateTimer=0;
/* Render time delay (desired FPS)*/
double updateTime=1/60;
/* track FPS */
double FPS;
/* Game loop control variable */
int running=1;

/* Setup main window functionalities */
void setupCge(){
  /* initialize handles */
  writeHandler = GetStdHandle(STD_OUTPUT_HANDLE);
  readHandler = GetStdHandle(STD_INPUT_HANDLE);

  /* Set the console's title */
  SetConsoleTitle(title);

  /* Set the screen font properties */
  setFont(FONT_SIZE_X, FONT_SIZE_Y);

  /* Set the window size */
  setWindowInfo();

  /* Set the screen's buffer size */
  SetConsoleScreenBufferSize(writeHandler, bufferSize);
  
  /* Initialise game loop logic*/
  startTimer=clock();
}
/* Initialise window settings (must be called when changes are made) */
void setWindowInfo()
{
  /* Refresh the console info */
  SetConsoleWindowInfo(writeHandler, TRUE, &windowSize);
}
/* Set window title */
void setTitle(char * t)
{
  SetConsoleTitle(t);
}
/* Set font size */
void setFont(int sx, int sy)
{
  lpConsoleCurrentFontEx.cbSize = sizeof(CONSOLE_FONT_INFOEX);
  lpConsoleCurrentFontEx.dwFontSize.X = sx;
  lpConsoleCurrentFontEx.dwFontSize.Y = sy;
  /* 
  WARNING => 
  Commented out code below doesn't seem to work
  it causes rendering to not occur and needs fixing
  
  lpConsoleCurrentFontEx.FontWeight = 500;
  lpConsoleCurrentFontEx.nFont = 1;
  lpConsoleCurrentFontEx.FontFamily = FF_DECORATIVE;
  lstrcpyW(lpConsoleCurrentFontEx.FaceName, L"Ariel");
  
  */
  SetCurrentConsoleFontEx ( writeHandler, FALSE, &lpConsoleCurrentFontEx );
  setWindowInfo();
}
/* Process the time events, rendering events and post-processing events */
void process()
{
	/* Check if enough times has passed to perform the next process */
	if(updateTimer>updateTime) 
    {
	  /* Render, clear the screen and reset the update timer for the next process */
      render();
      clear(COLOUR_BLACK, SYMBOL_FILL);
      updateTimer=0;
    }
	/* Post processing events; calculate deltaTime & FPS, update the process timer variables */
    endTimer=clock();
    deltaTime = ((double) (endTimer - startTimer)) / CLOCKS_PER_SEC;
    FPS=1/deltaTime;
    updateTimer+=deltaTime;
	startTimer=clock();
}
/* Render the screen buffer */
void render(){
  /* Write character buffer to the console buffer */
  WriteConsoleOutputA(writeHandler, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}
/* Write single character to the screen buffer */
void writeChar(int x, int y, int colour, char c) // Write a char to x y
{
  if (!(x>WIDTH) && !(x<0) && !(y>HEIGHT) && !(y<0))
  {
    consoleBuffer[x + WIDTH * y].Char.AsciiChar = c;
    consoleBuffer[x + WIDTH * y].Attributes = colour;
  }
}
/* Read single character from the screen buffer */
char readChar(int x, int y) // Read char at x y
{
  return consoleBuffer[x + WIDTH * y].Char.AsciiChar;
}
/* Write character array (string) to the screen buffer */
void writeCharArray(int x, int y, int colour, char * array) // Write an array of chars at x y
{
  int i;
  for(i=0;i<=sizeof(array)/sizeof(char);i++){
	writeChar(x+i,y,colour,array[i]);
  }
}
/* Read a character array (string) from the screen buffer */
void readCharArray(int x0, int y0, int x1, int y1, int ** array)
{
  int size=(x1 + WIDTH * y1)-(x0 + WIDTH * y0);
  int * tmp = malloc(size);
  int i;
  for(i=0; i<=size; i++)
  {
    tmp[i]=consoleBuffer[(x0 + WIDTH * y0)+i].Char.AsciiChar;
  }
  *array=tmp;
}
/* Draw a line between 2 points to the screen buffer */
void drawLine(int x0, int y0, int x1, int y1, int colour,int c) // Draw line of char between x and y
{
  Vec2df point0;
  point0.x = x0;
  point0.y = y0;
  Vec2df point1;
  point1.x = x1;
  point1.y = y1;

  int num = diagonalDistance(point0, point1);
  Vec2di points[num + 1];
  int i;
  for (i = 0; i <= num; i++) {
    float t = ((num == 0) ? 0.0 : (float) i / (float) num);
    Vec2di temp = roundPoint(lerpPoint(point0, point1, t));
    if (temp.x > WIDTH || temp.x < 0 || temp.y > HEIGHT || temp.y < 0) {
      continue;
    } else {
      writeChar(temp.x, temp.y, colour, c);
    }
  }
}
/* Draw a triangle comprised of 3 points to the screen buffer */
void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int colour,int c)
{
  drawLine(x0,y0,x1,y1,colour,c);
  drawLine(x1,y1,x2,y2,colour,c);
  drawLine(x2,y2,x0,y0,colour,c);
}
/* Draw a circle with a center and a radius to the screen buffer */
void drawCircle(int cx, int cy, int r, int colour, int c)
{
  int x = r-1;
  int y = 0;
  int dx = 1;
  int dy = 1;
  int err = dx - (r << 1);

  while (x >= y)
  {
    writeChar(cx + x, cy + y, colour, c);
    writeChar(cx + y, cy + x, colour, c);
    writeChar(cx - y, cy + x, colour, c);
    writeChar(cx - x, cy + y, colour, c);
    writeChar(cx - x, cy - y, colour, c);
    writeChar(cx - y, cy - x, colour, c);
    writeChar(cx + y, cy - x, colour, c);
    writeChar(cx + x, cy - y, colour, c);

    if (err <= 0)
    {
      y++;
      err += dy;
      dy += 2;
    }

    if (err > 0)
    {
      x--;
      dx += 2;
      err += dx - (r << 1);
    }
  }
}
/* Fill between 2 points to the screen buffer */
void fill(int x0, int y0, int x1, int y1, int colour, int c)
{
  int i;
  int j;
  for (j=y0;j<y1;j++)
  {
    for(i=x0;i<x1;i++)
    {
      writeChar(i,j,colour,c);
    }
  }
}
/* Clear buffer by setting buffer to a single colour & character */
void clear(int colour, char c)
{
  int x,y;
  for (y = 0; y < HEIGHT; ++y)
  {
    for (x = 0; x < WIDTH; ++x)
    {
      writeChar(x,y,colour,c);
    }
  }
}