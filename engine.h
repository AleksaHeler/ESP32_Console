#ifndef ENGINE_H
#define ENGINE_H

#define USE_DOUBLE_BUFFER // Wether to use seperate buffer to store rendered data and only then display it

// Double buffer: renderer draws to this buffer, and then on vSync copies it to the screen
// Although this may reduce framerate a bit, it can save us from displaying unfinished renders.
// So we can use 'buffer' in code, while actually having control over what exact buffer is used

#include <stdint.h>
#include <stdarg.h>

#define SCREEN_W 200
#define SCREEN_H 150

#define setp(X, Y, R, G, B) vga.dot((X), (Y), vga.RGB(R, G, B))


typedef struct {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} camera_t;

typedef struct
{
	double x;
	double y;
	int texture;
} sprite_t;

#endif
