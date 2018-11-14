#include "lib/include/leafengine.h"

int main()
{
	
  setupCge();
  
  int key;

  while(running)
  {
    if(keyDown()) 
	{
      key=getKeyPress();
      switch (key)
      {
        default: break;
      }
    }

    /* Drawing starts here */

    /* Drawing ends here */
	
	process();
  }

  return 0;
}