#include "sdlgl.h"
#include "geneticalgorithm.h"
#include "simplegene.h"
#include "simplefitness.h"
#include "util.h"
#include "random.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

	srand(time(0));

	if (argc < 2)
	{
		cout << "Usage: texgen image.bmp" << endl;
		return 0;
	}

	string imagePath(argv[1]);
	cout << imagePath << endl;

	SDLGLMain app(imagePath);
	Tai::SimpleFitness ff(&app);
	Tai::GeneticAlgorithm<Tai::SimpleGene, Tai::SimpleFitness> ga(ff);

	vector<Tai::SimpleGene> pop;
	for (int i = 0; i < 1; ++i)
	{
		//pop.push_back(Tai::randomGene(int(1 + drandom()*5 )) );
		pop.push_back(Tai::randomGene(1) );
	}

	ga.setInitialPopulation(pop);

	for (int c = 0; !app.quit_issued(); ++c)
	{
		cout << "iteration " << c << ": ";
		ga.iterate();
		app.renderGene(ga.bestGene());
		//app.drawTargetImage();
		cout << "best gene fitness=" << ga.bestGene().fitness() << ", length=" << ga.bestGene().length() << endl;
		app.processEvents();
	}

	//return app.run();
	return 0;
}
