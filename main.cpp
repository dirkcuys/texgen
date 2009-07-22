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

	std::vector<Tai::SimpleGene> pop;
	for (int i = 0; i < 20; ++i)
	{
		pop.push_back(Tai::randomGene(int(4*rand()/(1.0 + RAND_MAX))));
	}

	ga.setInitialPopulation(pop);

	for (int c = 0; c < 100; ++c)
	{
		ga.iterate();
	}

	//return app.run();
	return 0;
}
