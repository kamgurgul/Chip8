#include "ChipRenderer.h"

ChipRenderer::ChipRenderer()
{
}


ChipRenderer::~ChipRenderer()
{
}

int ChipRenderer::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not init: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	window = SDL_CreateWindow(
		"Chip-8",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		DISPLAY_WIDTH,
		DISPLAY_HEIGHT,
		0);
	if (window == NULL) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	return 0;
}

void ChipRenderer::destroy()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ChipRenderer::clearScreen()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void ChipRenderer::renderFrame(unsigned char *gfx)
{
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for (int y = 0; y < CHIP_SCREEN_HEIGHT; ++y)
		for (int x = 0; x < CHIP_SCREEN_WIDTH; ++x) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			if (gfx[(y * CHIP_SCREEN_WIDTH) + x] == 1) {
				SDL_Rect r;
				r.x = x * MODIFIER;
				r.y = y * MODIFIER;
				r.w = MODIFIER;
				r.h = MODIFIER;
				SDL_RenderFillRect(renderer, &r);
			}
		}

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void ChipRenderer::keyDown(Chip8 &chip8, SDL_Keycode keycode)
{
	if (keycode == SDLK_1)         chip8.key[0x1] = 1;
	else if (keycode == SDLK_2)    chip8.key[0x2] = 1;
	else if (keycode == SDLK_3)    chip8.key[0x3] = 1;
	else if (keycode == SDLK_4)    chip8.key[0xC] = 1;

	else if (keycode == SDLK_q)    chip8.key[0x4] = 1;
	else if (keycode == SDLK_w)    chip8.key[0x5] = 1;
	else if (keycode == SDLK_e)    chip8.key[0x6] = 1;
	else if (keycode == SDLK_r)    chip8.key[0xD] = 1;

	else if (keycode == SDLK_a)    chip8.key[0x7] = 1;
	else if (keycode == SDLK_s)    chip8.key[0x8] = 1;
	else if (keycode == SDLK_d)    chip8.key[0x9] = 1;
	else if (keycode == SDLK_f)    chip8.key[0xE] = 1;

	else if (keycode == SDLK_z)    chip8.key[0xA] = 1;
	else if (keycode == SDLK_x)    chip8.key[0x0] = 1;
	else if (keycode == SDLK_c)    chip8.key[0xB] = 1;
	else if (keycode == SDLK_v)    chip8.key[0xF] = 1;
}

void ChipRenderer::keyUp(Chip8 &chip8, SDL_Keycode keycode)
{
	if (keycode == SDLK_1)         chip8.key[0x1] = 0;
	else if (keycode == SDLK_2)    chip8.key[0x2] = 0;
	else if (keycode == SDLK_3)    chip8.key[0x3] = 0;
	else if (keycode == SDLK_4)    chip8.key[0xC] = 0;

	else if (keycode == SDLK_q)    chip8.key[0x4] = 0;
	else if (keycode == SDLK_w)    chip8.key[0x5] = 0;
	else if (keycode == SDLK_e)    chip8.key[0x6] = 0;
	else if (keycode == SDLK_r)    chip8.key[0xD] = 0;

	else if (keycode == SDLK_a)    chip8.key[0x7] = 0;
	else if (keycode == SDLK_s)    chip8.key[0x8] = 0;
	else if (keycode == SDLK_d)    chip8.key[0x9] = 0;
	else if (keycode == SDLK_f)    chip8.key[0xE] = 0;

	else if (keycode == SDLK_z)    chip8.key[0xA] = 0;
	else if (keycode == SDLK_x)    chip8.key[0x0] = 0;
	else if (keycode == SDLK_c)    chip8.key[0xB] = 0;
	else if (keycode == SDLK_v)    chip8.key[0xF] = 0;
}