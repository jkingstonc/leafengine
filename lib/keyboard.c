#include "include/keyboard.h"

/* Check if keyboard is being pressed */
int keyDown()
{
  return kbhit();
}
/* Return keypress as char (ASCII + Extended ASCII) */
int getKeyPress()
{
  return _getch();
}