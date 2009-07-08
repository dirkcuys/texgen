#include "sdlgl.h"

#include <iostream>

int main(int argc, char **argv)
{

	std::cout << "Starting texgen app" << std::endl;

	SDLGLMain app;

	return app.run();
}
