#ifndef IMAGE_H
#define IMAGE_H

#include "SDL.h"

typedef struct {
	Uint8 r;
	Uint8 g;
	Uint8 b;
} Pixel;

typedef struct {
	union {
		Pixel* pixels;
		Uint8* rawPixels;
	};
	int w;
	int h;
	double fitness;
} Image;

Image* loadImage(SDL_Surface *surface);

Image* randomImage(int w, int h);

Image* copyImage(Image*);

void freeImage(Image* image);

SDL_Surface* image2sdl(Image* image);

#endif //IMAGE_H
