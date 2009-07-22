#include "sdlgl.h"
#include "geneticalgorithm.h"
#include "simplegene.h"
#include "simplefitness.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

	cout << "Starting texgen app" << endl;

	SDLGLMain app;
	Tai::SimpleFitness ff(&app);
	Tai::GeneticAlgorithm<Tai::SimpleGene, Tai::SimpleFitness> ga(ff);

	vector<Tai::SimpleGene> pop;
	for (int i = 0; i < 5; ++i)
	{
		pop.push_back(Tai::randomGene(9));
	}

	ga.setInitialPopulation(pop);

	for (int c = 0; c < 100; ++c)
	{
		cout << "iteration " << c << endl;
		ga.iterate();
	}

	//return app.run();
	return 0;
}
