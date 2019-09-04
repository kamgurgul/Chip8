#pragma once

#include "SDLHeaders.h"
#include "Chip8.h"
#include <iostream>

#define CHIP_SCREEN_WIDTH 64
#define CHIP_SCREEN_HEIGHT 32

class ChipRenderer
{
public:
	ChipRenderer();
	~ChipRenderer();

	int init();
	void destroy();
	void clearScreen();
	void renderFrame(unsigned char *gfx);
	void keyDown(Chip8 &chip8, SDL_Keycode keycode);
	void keyUp(Chip8 &chip8, SDL_Keycode keycode);

private:
	const int MODIFIER = 10;
	const int DISPLAY_WIDTH = CHIP_SCREEN_WIDTH * MODIFIER;
	const int DISPLAY_HEIGHT = CHIP_SCREEN_HEIGHT * MODIFIER;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;
};

