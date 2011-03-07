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

#ifndef SDLGL_H
#define SDLGL_H

#include "SDL.h"
#include "glew.h"
#include "gl.h"
#include "glu.h"
#include <string>

#include "image.h"
#include "util.h"

namespace Tai
{
	class SimpleGene;
};

/** Class driving openGL rendering and IO */
class SDLGLMain
{
public:
	SDLGLMain(std::string imageName);
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

	bool quit_issued() const { return m_quit; };

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
