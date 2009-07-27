#ifndef TAI_SIMPLEFITNESS
#define TAI_SIMPLEFITNESS

#include "sdlgl.h"

namespace Tai
{
	// forward declaration
	class SimpleGene;

	class SimpleFitness
	{
	public:
		SimpleFitness(SDLGLMain* sdl) : m_sdl(sdl) {};
		double calculate(SimpleGene&);
	private:
		SDLGLMain* m_sdl;
	};
}; //namespace Tai

#endif //TAI_SIMPLEFITNESS
