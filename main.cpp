#include "sdlgl.h"
#include "geneticalgorithm.h"
#include "simplegene.h"
#include "simplefitness.h"
#include "util.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

	srand(time(0));
	cout << "Starting texgen app" << endl;

	SDLGLMain app(130,80);
	Tai::SimpleFitness ff(&app);
	Tai::GeneticAlgorithm<Tai::SimpleGene, Tai::SimpleFitness> ga(ff);

	vector<Tai::SimpleGene> pop;
	for (int i = 0; i < 20; ++i)
	{
		pop.push_back(Tai::randomGene(int(1 + drandom()*5 )) );
	}

	ga.setInitialPopulation(pop);

	for (int c = 0; c < 100000; ++c)
	{
		cout << "iteration " << c << ": ";
		ga.iterate();
		app.renderGene(ga.bestGene());
		//app.drawTargetImage();
		cout << "best gene fitness=" << ga.bestGene().fitness() << ", length=" << ga.bestGene().length() << endl;
		app.processEvents();
		if (app.quit_issued())
			break;
	}

	//return app.run();
	return 0;
}
