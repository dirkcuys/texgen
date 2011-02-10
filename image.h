/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

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
