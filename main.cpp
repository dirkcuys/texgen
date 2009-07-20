#include "sdlgl.h"
#include "geneticalgorithm.h"
#include "simplegene.h"
#include "simplefitness.h"

#include <iostream>

int main(int argc, char **argv)
{

	std::cout << "Starting texgen app" << std::endl;

	SDLGLMain app;
	Tai::SimpleFitness ff;
	Tai::GeneticAlgorithm<Tai::SimpleGene, Tai::SimpleFitness> ga(ff);
	ga.iterate();

	return app.run();
}
