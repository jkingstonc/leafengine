#include <stdio.h>
#include <math.h>

#include "lib/include/leafengine.h"

/* Width and height of the map */
int mapHeight = 50;
int mapWidth = 50;

/* Player position & angle */
double playerX=10;
double playerY=10;
double playerA;

/* Field of view in radians */
double FOV = 3.14159/2;
/* Max ray cast depth */
double depth;

/* Speed of player controls */
double walkSpeed=50.0;
double turnSpeed=20.0;

/* Key pressed */
int key;

int main()
{
  /* Setup display */
  setupCge();
  clear(COLOUR_BLACK,SYMBOL_FILL);

  /* Map array */
  char map[mapWidth*mapHeight];
  /* Max ray cast depth */
  double depth=(mapWidth*mapHeight)/2;
  
  /* Populating map in arbitary way */
  for(int x=0;x<mapWidth;x++)
  {
	for(int y=0;y<mapHeight;y++)
	  {
	  if(x%5==0 && y%5==0)
	  {
		map[y*mapWidth+x]='#';
	  }else{
		map[y*mapWidth+x]='.';
	  }
	}
  }

  while(running)
  {

    if(keyDown()) {
      key=getKeyPress();
      switch (key)
      {
        case 'w': {
		  /* Move player */
          playerX+=sin(playerA)*walkSpeed*deltaTime;
          playerY+=cos(playerA)*walkSpeed*deltaTime;
		  
		  /* Check if player is out of bounds */
          if(map[(int)playerY * mapWidth + (int)playerX]=='#' || playerX > mapWidth || playerX < 0 || playerY > mapHeight || playerY < 0)
          {
			/* Move player back */
            playerX-=sin(playerA)*walkSpeed*deltaTime;
            playerY-=cos(playerA)*walkSpeed*deltaTime;
          }
          break;
        }
        case 's': {
	      /* Move player */
          playerX-=sin(playerA)*walkSpeed*deltaTime;
          playerY-=cos(playerA)*walkSpeed*deltaTime;
		  
		  /* Check if player is out of bounds */
          if(map[(int)playerY * mapWidth + (int)playerX]=='#' || playerX > mapWidth || playerX < 0 || playerY > mapHeight || playerY < 0)
          {
			/* Move player back */
            playerX+=sin(playerA)*walkSpeed*deltaTime;
            playerY+=cos(playerA)*walkSpeed*deltaTime;
          }
          break;
        }
        case 'd': {
		  /* Change player angle */
          playerA-=turnSpeed*deltaTime;
          break;
        }
        case 'a': {
		  /* Change player angle */	
          playerA+=turnSpeed*deltaTime;
          break;
        }
        default: break;
      }
    }

    /* Drawing stuff here */
	
	/* Draw the map if it isnt a blank space (not a '.') */
    for(int x=0;x<mapWidth;x++)
    {
	  for(int y=0;y<mapHeight;y++)
	  {
	    if(map[y*mapWidth+x] != '.') writeChar(x+2,y+2,COLOUR_DARK_BLUE,map[y*mapWidth+x]);
	  }
    }

	/* Cast rays, in this case the same width as the screen */
    for(int x=0;x<WIDTH;x++)
    {
	  /* Calculate ray angle based on player rotaion, and the current x value across the width of the screen */
      double rayAngle = (playerA - FOV/2.0) + ((double)x/(double)WIDTH) * FOV;
	  /* Initialise variable to hold the distance to the wall the ray has traveled */
      double distanceToWall=0.0;
	  /* Has the ray hit a wall */
      int hitWall=0;
	  /* Increment ray distance ammount */
      double rayIncrement=0.01;
	  /* Do until the ray hits a wall or until the ray has reached the maximum ray depth */
      while(!hitWall && distanceToWall<depth)
      {
		/* Increment ray distance */
        distanceToWall+=rayIncrement;
		/* values used to calculate the next position the ray is at */
        double lookX = sin(rayAngle);
        double lookY = cos(rayAngle);
		
		/* Current ray position, taken by the player position, plus the current ray distance multiplied by the sin of the angle */
        int testX = (int)(playerX + lookX * distanceToWall);
        int testY = (int)(playerY + lookY * distanceToWall);

		/* Checking if the ray position is out of bounds */
        if(testX < 0 || testX >= mapWidth || testY < 0 || testY > mapHeight)
        {
		  /* Ray has hit wall */
          hitWall = 1;
          distanceToWall=mapWidth;
        }else if(map[testY * mapWidth + testX] == '#')
        {
		  /* Ray has hit wall */
          hitWall = 1;
        }else{
		  /* Ray hasnt hit wall, shade area ray has traversed */
          writeChar(2 + testX, 2 + testY, COLOUR_PURPLE, SYMBOL_SHADE_LIGHT);
        }
      }
    }
	/* Draw character at player position */
    writeChar(2+playerX,2+playerY,COLOUR_WHITE,'@');
    
	/* Process game */
	process();
  }
  getchar();

  return 0;
}
