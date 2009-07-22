#include "simplegene.h"

using namespace Tai;
using namespace std;


SimpleGene::SimpleGene()
{
	m_fitness = 0;
}

SimpleGene::~SimpleGene()
{
}

int SimpleGene::length() const
{
	return m_values.size();
}

double SimpleGene::fitness() const
{
	return m_fitness;
}

double SimpleGene::fitness(double fitness_)
{
	m_fitness = fitness_;
	return m_fitness;
}
	
void SimpleGene::mutate(double probability, double factor)
{
	vector<double>::iterator value_it = m_values.begin();

	for (; value_it != m_values.end(); ++value_it)
	{
		double randomValue = rand()/(RAND_MAX + 1.0);
		if (randomValue < probability)
		{
			*value_it += factor*rand()/(RAND_MAX + 1.0);
		}
	}
	m_fitness = 0;
}

//static function
SimpleGene SimpleGene::crossOver(const SimpleGene& lhs, const SimpleGene& rhs)
{
	// TODO do the crossover
	return SimpleGene();
}

SimpleGene Tai::randomGene(int size)
{
	vector<double> tmp;
	tmp.reserve(10*size);
	vector<double>::iterator it = tmp.begin();
	for (; it != tmp.end(); ++it)
	{
		*it = 2*(rand()/(1.0 + RAND_MAX)) - 1.0;
	}
	SimpleGene sg;
	sg.values(tmp);
	return sg;
}
