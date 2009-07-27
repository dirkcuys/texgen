#include "image.h"

#include <cstdlib>
#include <cstring>
#include "SDL.h"

Image* loadImage(SDL_Surface *surface){
	
	int bpp = surface->format->BytesPerPixel;
	Image *image = new Image();
	image->w = surface->w;
	image->h = surface->h;
	image->pixels = new Pixel[image->w*image->h];
		
	for (int y = 0; y < surface->h; ++y){
		for (int x = 0; x < surface->w; ++x){
			/* Here p is the address to the pixel we want to retrieve */
			Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
			switch(bpp) {
				case 1:
					SDL_GetRGB(*p,surface->format,&image->pixels[image->w*y+x].r,&image->pixels[image->w*y+x].g,&image->pixels[image->w*y+x].b);	
				case 2:
					SDL_GetRGB(*(Uint16 *)p,surface->format,&image->pixels[image->w*y+x].r,&image->pixels[image->w*y+x].g,&image->pixels[image->w*y+x].b);	
				case 3:
					if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
						SDL_GetRGB(p[0] << 16 | p[1] << 8 | p[2],surface->format,&image->pixels[image->w*y+x].r,&image->pixels[image->w*y+x].g,&image->pixels[image->w*y+x].b);	
					}	
					else
						SDL_GetRGB(p[0] | p[1] << 8 | p[2] << 16,surface->format,&image->pixels[image->w*y+x].r,&image->pixels[image->w*y+x].g,&image->pixels[image->w*y+x].b);	
				case 4:
					SDL_GetRGB(*(Uint32 *)p,surface->format,&image->pixels[image->w*y+x].r,&image->pixels[image->w*y+x].g,&image->pixels[image->w*y+x].b);	
				//default:
			}
		}
	}
	return image;
}

Image* randomImage(int w, int h){
	
	Image *image = new Image;
	image->w = w;
	image->h = h;
	image->pixels = new Pixel[w*h];
	for (int cnt = 0; cnt < w*h; ++cnt){
		image->pixels[cnt].r = (Uint8) (256.0*random()/(RAND_MAX + 1.0));
		image->pixels[cnt].g = (Uint8) (256.0*random()/(RAND_MAX + 1.0));
		image->pixels[cnt].b = (Uint8) (256.0*random()/(RAND_MAX + 1.0));
	}
	return image;
	
}

Image* copyImage(Image* image){
	Image* ni = new Image;
	ni->w = image->w;
	ni->h = image->h;
	ni->fitness = image->fitness;
	ni->pixels = new Pixel[ni->w*ni->h];
	memcpy(ni->pixels,image->pixels,sizeof(image->pixels));
	return ni;
}

void freeImage(Image* image){
	delete [] image->pixels;
	//image->pixels = 0;
	delete image;
	//image = 0;
}

SDL_Surface* image2sdl(Image* image){

	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;
    
	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
		on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	surface = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, 32, rmask, gmask, bmask, amask);
	if(surface == NULL) {
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
		
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
   
	for (int y = 0; y < image->h; ++y){
		for (int x = 0; x < image->w; ++x){
			Uint32 pixel = SDL_MapRGB(surface->format,image->pixels[y*image->w+x].r,image->pixels[y*image->w+x].g,image->pixels[y*image->w+x].b);
			Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		
			switch(bpp) {
				case 1:
					*p = pixel;
					break;
		
				case 2:
					*(Uint16 *)p = pixel;
					break;

				case 3:
					if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
						p[0] = (pixel >> 16) & 0xff;
						p[1] = (pixel >> 8) & 0xff;
						p[2] = pixel & 0xff;
					} else {
						p[0] = pixel & 0xff;
						p[1] = (pixel >> 8) & 0xff;
						p[2] = (pixel >> 16) & 0xff;
					}
					break;
		
				case 4:
					*(Uint32 *)p = pixel;
					break;
			}
		}
	}

	return surface;
}

