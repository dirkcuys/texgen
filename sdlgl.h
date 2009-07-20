#ifndef SDLGL_H
#define SDLGL_H

#include "SDL.h"
#include "glew.h"
#include "gl.h"
#include "glu.h"

class SDLGLMain
{
public:
	SDLGLMain();
	~SDLGLMain();

	void init();
	void draw();
	void handleEvents(const SDL_Event &);

	void quit();

	int run();

protected:
	SDLGLMain(const SDLGLMain&);
	SDLGLMain& operator=(const SDLGLMain&);

private:
	bool m_quit;
	GLuint m_fbo;
	GLuint m_fbTex;
	GLuint m_pbo;
	GLuint m_width;
	GLuint m_height;

};

#endif //SDLGL_H
