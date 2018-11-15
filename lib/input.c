#include "include/input.h"
#include "include/cge.h"

/* Check if keyboard is being pressed */
int keyPressed()
{
	if(input.EventType==KEY_EVENT)
	{
		return 1;
	}else{
		return 0;
	}
}

/* Return keypress as char (ASCII + Extended ASCII) */
int getKey()
{
	return input.Event.KeyEvent.wVirtualKeyCode;
}

/* Check if left mouse button is clicked */
int leftMouseClick()
{
	return (input.Event.MouseEvent.dwButtonState==1);
}

/* Check if right mouse button is clicked */
int rightMouseClick()
{
	return (input.Event.MouseEvent.dwButtonState==2);
}

/* Check for double click */
int doubleClick()
{
	return (input.Event.MouseEvent.dwEventFlags==2);
}

/* Return mouse position x */
int getMouseX()
{
	return input.Event.MouseEvent.dwMousePosition.X;
}

/* Return mouse position y */
int getMouseY()
{
	return input.Event.MouseEvent.dwMousePosition.Y;
}