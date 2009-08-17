#include "sdlgl.h"

#include "simplegene.h"

#include <iostream>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

SDLGLMain::SDLGLMain(int width, int height)
{

	m_width = width;
	m_height = height;
	
	// set up video
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	SDL_SetVideoMode(m_width,m_height,32,SDL_OPENGL);
	SDL_Surface* sdlImg = SDL_LoadBMP("image.bmp");
	m_originalImage = loadImage(sdlImg);

	glewInit();
	init();

	m_quit = false;
}

SDLGLMain::~SDLGLMain()
{
}

void SDLGLMain::init()
{
	// set opengl attributes
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glShadeModel(GL_FLAT);

	// set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	
	glGenTextures(1, &m_fbTex);
	glBindTexture(GL_TEXTURE_2D, m_fbTex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffersEXT(1, &m_fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_fbTex, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glGenBuffersARB(1, &m_pbo);
	glBindBuffer(GL_PIXEL_PACK_BUFFER_ARB, m_pbo);
	glBufferData(GL_PIXEL_PACK_BUFFER_ARB, m_width*m_height*4, NULL, GL_STREAM_READ);
	glBindBuffer(GL_PIXEL_PACK_BUFFER_ARB, 0);

}

void SDLGLMain::drawTargetImage()
{		
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

		
		glBegin(GL_POINTS);
		for ( int y = 0; y < m_height; y+=2)
		{
			for (int x = 0; x < m_width; x+=2)
			{
				GLfloat xmul = 2.0*x/(float)m_width - 1.0;
				GLfloat ymul = 2.0*y/(float)m_height - 1.0;
				//glColor3ubv(m_originalImage->rawPixels[(y*m_width + x)*3]);
				glColor3ub(m_originalImage->pixels[y*m_width + x].r, m_originalImage->pixels[y*m_width + x].g, m_originalImage->pixels[y*m_width + x].b);
				glVertex3f(xmul, ymul, 0.0);
			}
		}
		glEnd();


	SDL_GL_SwapBuffers();

}

void SDLGLMain::draw()
{
	// render to texture
	//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glTranslatef(0.0, 0.0, -2.0);
	glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex2d(0.0, 0.0);
		glVertex2d(-1.0, -1.0);
		glVertex2d(0.0, -1.0);
		glVertex2d(-1.0, 0.0);
		
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glVertex2d(0.0, 0.0);
		glVertex2d(1.0, 1.0);
		glVertex2d(0.0, 1.0);
		glVertex2d(1.0, 0.0);
	glEnd();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glFlush();
	/*
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	// render to screen
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	
	glBindTexture(GL_TEXTURE_2D, m_fbTex);
	
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_pbo);
	//glReadPixels(0, 0, m_width, m_height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	GLubyte* texBuf = (GLubyte*)glMapBufferARB(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
	if (texBuf != 0)
	{
		glBegin(GL_POINTS);
		for ( int y = 0; y < m_height; y+=2)
		{
			for (int x = 0; x < m_width; x+=2)
			{
				GLfloat xmul = 4.0*x/(float)m_width - 2.0;
				GLfloat ymul = 4.0*y/(float)m_height - 2.0;
				glColor4ubv(&texBuf[ (y*m_width + x)*4 + 0]);
				glVertex3f(xmul, ymul, 0.0);
			}
		}
		glEnd();

		glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB);
	}
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);

	//glBegin(GL_QUADS);
	//	glColor4f(0.4, 0.4, 0.4, 1.0);
	//	glTexCoord2f(0, 0);	glVertex3d(-1.0, -1.0, 1.0);
	//	glTexCoord2f(0, 1);	glVertex3d(-1.0, 1.0, 1.0);
	//	glTexCoord2f(1, 1);	glVertex3d(1.0, 1.0, 0.0);
	//	glTexCoord2f(1, 0);	glVertex3d(1.0, -1.0, 0.0);
	//glEnd();

	glPopMatrix();
	glFlush();*/
	SDL_GL_SwapBuffers();
}

void SDLGLMain::renderGene(const Tai::SimpleGene &gene)
{

	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT);
	
	int cnt = 0;
	glBegin(GL_TRIANGLES);
		while (gene.values().size() - cnt > 10)
		{
			glColor4d(gene.values()[cnt], gene.values()[cnt + 1], gene.values()[cnt + 2], gene.values()[cnt + 3]);
			glVertex2d(2.0*gene.values()[cnt+4] - 1.0, 2.0*gene.values()[cnt+5] - 1.0);
			glVertex2d(2.0*gene.values()[cnt+6] - 1.0, 2.0*gene.values()[cnt+7] - 1.0);
			glVertex2d(2.0*gene.values()[cnt+8] - 1.0, 2.0*gene.values()[cnt+9] - 1.0);
			cnt += 10;
		}
	glEnd();
	
}

GLubyte* SDLGLMain::renderGeneToSurface(const Tai::SimpleGene &gene)
{
	// render to texture
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	
	renderGene(gene);

	//glFlush();
	SDL_GL_SwapBuffers();
	
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, m_fbTex);

	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_pbo);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	GLubyte* texBuf = (GLubyte*)glMapBufferARB(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
	GLubyte *image = new GLubyte[m_width*m_height*4];
	if (texBuf != 0)
	{
		// do something with the texture
		//return texBuf;
		memcpy(image, texBuf, m_width*m_height*4);
		glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB);
	}
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);//*/
	return image;
}

void SDLGLMain::handleEvents(const SDL_Event &event)
{
	switch (event.type)
	{
		case SDL_QUIT:
			m_quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					m_quit = true;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void SDLGLMain::quit()
{
	m_quit = true;
}

void SDLGLMain::processEvents()
{

	SDL_Event event;
	while (SDL_PollEvent( &event) )
	{
		handleEvents(event);
	}
}

int SDLGLMain::run()
{

	while (!m_quit)
	{
		SDL_Event event;
		while (SDL_PollEvent( &event) )
		{
			handleEvents(event);
		}
		draw();
		SDL_Delay(10);
	}

	
	return 0;
}
