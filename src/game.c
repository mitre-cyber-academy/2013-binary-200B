#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include <time.h>
#include <unistd.h>

#define KEY_LENGTH 128
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 300
int main(int argc, char* argv[])
{
	char keyBuff[128];
	char correctKey[128];
	FILE* keyFile;
	size_t numRead;
	time_t sysTime;
	long int randNum;
	SDL_Rect screenRect, lr;
	SDL_Surface* screen;
	Uint32 black;
	Uint32 white;
	int h, bl, tl, tmpx, tmpy, count, chrSpc;
	if(argc < 2)
	{
		printf("Usage: %s <keyFile>\n", argv[0]);
		printf("\nkeyFile - The file containing your CD Key\n");
		exit(0);
	}
	else
	{
		keyFile = fopen(argv[1], "rb");
		if(keyFile == NULL)
		{
			perror("Error - couldn't open key file");
			exit(1);
		}
		numRead = fread(keyBuff, KEY_LENGTH, 1, keyFile);
		if(numRead != 1)
		{
			fprintf(stderr, "Error: couldn't read whole key\n");
			exit(2);
		}
		//Compute the time:
		sysTime = time(NULL);
		randNum = random();
		for(count = 0; count < KEY_LENGTH; count ++)
		{
			correctKey[count] = 
				(sysTime ^ randNum ^ count);
			randNum = random();
			sysTime = time(NULL);
		}
		//Compare the `correct' key with the provided one:
		for(count = 0; count < KEY_LENGTH; count ++)
		{
			if(correctKey[count] != keyBuff[count])
				break;
		}
		if(count != KEY_LENGTH)
		{
			fprintf(stderr, "Error: invalid CD Key\n");
			exit(3);
		}
		//Otherwise, display the key (via SDL)
		if(SDL_Init(SDL_INIT_VIDEO < 0))
		{
			fprintf(stderr, "Error, unable to initialize game interface: %s\n",
					SDL_GetError());
			exit(4);
		}
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_SWSURFACE);
		if(screen == NULL)
		{
			fprintf(stderr, "Unable to initialize window: %s\n", SDL_GetError());
			exit(5);
		}
		screenRect.x = screenRect.y = 0;
		screenRect.w = SCREEN_WIDTH;
		screenRect.h = SCREEN_HEIGHT;
		black = SDL_MapRGB(screen->format, 0,0,0);
		white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
		SDL_FillRect(screen, &screenRect, black);
		bl = 165;
		tl = 135;
		chrSpc = 10;
		h = bl - tl;
		lr.h = lr.w = 3;
		lr.x = 10;
		//Flag is MCA-B17EC0D3
		//Draw the letters:
		//m
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		for(lr.y = tl; lr.y < h / 2 + tl; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		for(; lr.y > tl; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//C
		tmpx = lr.x;
		for(lr.y = tl + h/2; lr.y < bl; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = tl + h/2; lr.y > tl; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//A
		for(lr.y = bl; lr.y > tl; lr.y -= 2)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
			if(lr.y <= tl + h/2)
			{
				tmpy = lr.y;
				lr.y = tl + h/2;
				SDL_FillRect(screen, &lr, white);
				lr.y = tmpy;
			}
		}
		for(lr.y = tl; lr.y < bl; lr.y += 2)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
			if(lr.y <= bl - h/2)
			{
				tmpy = lr.y;
				lr.y = tl + h/2;
				SDL_FillRect(screen, &lr, white);
				lr.y = tmpy;
			}
		}
		lr.x += chrSpc;
		//-
		tmpx = lr.x;
		for(lr.y = tl + h/2; lr.x < tmpx + chrSpc; lr.x ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//B
		//A B is two backwards Cs with a line on the left
		//Line:
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		tmpx = lr.x;
		//bottom upward line of B
		for(lr.y = bl; lr.y > bl - h/4; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		//Top upward part of b
		for(lr.y = bl - h/2; lr.y > bl - 3*h/4; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		//top downward line of b:
		lr.x = tmpx;
		for(lr.y = tl; lr.y < tl + h/4; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		//top bottom line of b:
		lr.x = tmpx;
		for(lr.y = tl + h/2; lr.y < bl - h/4; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;

		//1
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;

		//7 - a 1 with a hat:
		lr.y = tl;
		for(tmpx = lr.x; lr.x < tmpx + chrSpc; lr.x ++)
			SDL_FillRect(screen, &lr, white);
		for(; lr.y < bl; lr.y ++)
			SDL_FillRect(screen, &lr, white);
		lr.x += chrSpc;

		//E - a 1 with 3 lines
		//1
		for(lr.y = tl; lr.y < bl; lr.y ++)
			SDL_FillRect(screen, &lr, white);
		for(tmpx = lr.x; lr.x < tmpx + chrSpc; lr.x ++)
		{
			//Top:
			lr.y = tl;
			SDL_FillRect(screen, &lr, white);
			//Mid:
			lr.y += h / 2;
			SDL_FillRect(screen, &lr, white);
			//Bottom:
			lr.y = bl;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;

		//C
		tmpx = lr.x;
		for(lr.y = tl + h/2; lr.y < bl; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = tl + h/2; lr.y > tl; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;

		//0 (two C's back to back)
		tmpx = lr.x;
		for(lr.y = tl + h/2; lr.y < bl; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = tl + h/2; lr.y > tl; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		tmpx = lr.x;
		for(lr.y = tl; lr.y < tl + h/2; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = bl; lr.y > tl + h/2; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;

		//D
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		tmpx = lr.x;
		for(lr.y = bl; lr.y > tl + h/2; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = tl; lr.y < tl + h/2; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;

		//A 3 is a backwards E:
		for(tmpx = lr.x; lr.x < tmpx + chrSpc; lr.x ++)
		{
			//Top:
			lr.y = tl;
			SDL_FillRect(screen, &lr, white);
			//Mid:
			lr.y += h / 2;
			SDL_FillRect(screen, &lr, white);
			//Bottom:
			lr.y = bl;
			SDL_FillRect(screen, &lr, white);
		}
		for(lr.y = tl; lr.y < bl; lr.y ++)
			SDL_FillRect(screen, &lr, white);
		lr.x += chrSpc;
		

		//Display the flag:
		lr.y = 0;
		lr.w = 1;
		lr.h = SCREEN_HEIGHT;
		for(lr.x = 0; lr.x < SCREEN_WIDTH; lr.x ++)
		{
			SDL_UpdateRect(screen, lr.x, lr.y, 
				lr.w, lr.h);
			usleep(10000);
		}
		sleep(3);
	}
	return 0;
}
