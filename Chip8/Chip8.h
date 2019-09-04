#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Chip8
{
public:
	Chip8();
	~Chip8();

	bool drawFlag;

	bool loadGame(const char * filename);
	void emulateCycle();
	void debugRender();

	unsigned char  gfx[64 * 32];	// Total amount of pixels: 2048
	unsigned char  key[16];

private:
	unsigned short pc;				// Program counter
	unsigned short opcode;			// Current opcode
	unsigned short I;				// Index register
	unsigned short sp;				// Stack pointer

	unsigned char  V[16];			// V-regs (V0-VF)
	unsigned short stack[16];		// Stack (16 levels)
	unsigned char  memory[4096];	// Memory (size = 4k)		

	unsigned char  delay_timer;		// Delay timer
	unsigned char  sound_timer;		// Sound timer

	void init();
};

