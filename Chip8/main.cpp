#include <iostream>
#include "SDLHeaders.h"
#include "Chip8.h"
#include "LTimer.h"
#include "ChipRenderer.h"

const int SCREEN_FPS = 500;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

ChipRenderer chipRenderer;
Chip8 chip8;

void display();

int main(int argc, char *argv[])
{
	chipRenderer.init();
	chip8.loadGame("pong2.c8");

	SDL_Event event;
	bool quit = false;
	LTimer fpsTimer;
	LTimer capTimer;
	int countedFrames = 0;
	fpsTimer.start();
	while (!quit) {
		capTimer.start();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				chipRenderer.keyDown(chip8, event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				chipRenderer.keyUp(chip8, event.key.keysym.sym);
				break;
			}
		}
		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		if (chip8.drawFlag)
		{
			chipRenderer.renderFrame(chip8.gfx);
			chip8.drawFlag = false;
		}
		chip8.emulateCycle();
		++countedFrames;
		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	chipRenderer.destroy();
	return EXIT_SUCCESS;
}

void loop()
{
	chip8.emulateCycle();
	if (chip8.drawFlag)
	{
		//chip8.debugRender();
		// Processed frame
		chip8.drawFlag = false;
	}
}
