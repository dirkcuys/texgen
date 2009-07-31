#ifndef SDLGL_H
#define SDLGL_H

#include "SDL.h"
#include "glew.h"
#include "gl.h"
#include "glu.h"
#include "image.h"
#include "util.h"

namespace Tai
{
	class SimpleGene;
};

class SDLGLMain
{
public:
	SDLGLMain(int width, int height);
	~SDLGLMain();

	void init();
	void drawTargetImage();
	void draw();
	void handleEvents(const SDL_Event &);
	void quit();
	void processEvents();
	int run();

	void renderGene(const Tai::SimpleGene&);
	GLubyte* renderGeneToSurface(const Tai::SimpleGene&);

	Image* getImage(){ return m_originalImage; };

	GLuint width() const { return m_width; };
	GLuint height() const { return m_height; };

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
	Image *m_originalImage;

};

#endif //SDLGL_H
