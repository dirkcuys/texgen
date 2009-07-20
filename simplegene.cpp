#include "simplegene.h"

using namespace Tai;
using namespace std;


SimpleGene::SimpleGene()
{
}

SimpleGene::~SimpleGene()
{
}

int SimpleGene::getLength()
{
	return values.size();
}
	
void SimpleGene::mutate(double probability, double factor)
{
	vector<double>::iterator value_it = values.begin();

	for (; value_it != values.end(); ++value_it)
	{
		double randomValue = rand()/(RAND_MAX + 1.0);
		if (randomValue < probability)
		{
			*value_it += factor*rand()/(RAND_MAX + 1.0);
		}
	}
}

//static function
SimpleGene SimpleGene::crossOver(const SimpleGene& lhs, const SimpleGene& rhs)
{
	// TODO do the crossover
	return SimpleGene();
}
