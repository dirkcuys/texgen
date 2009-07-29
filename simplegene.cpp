#include "simplegene.h"

#include "util.h"

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
		double randomValue = drandom();
		if (randomValue < probability)
		{
			*value_it += factor*(2.0*drandom()-1);
			//*value_it = drandom();
		}
	}
	m_fitness = 0;
}

//static function
SimpleGene SimpleGene::crossOver(const SimpleGene& lhs, const SimpleGene& rhs)
{
	// TODO do the crossover
	
	int c1 = int(drandom()*lhs.length());
	int c2 = int(drandom()*rhs.length());
	c2 = c2 - (c2 % 10) + (c1 % 10);

	SimpleGene sg;
	sg.m_values.reserve(c1 + rhs.length() - c2);
	for (int i = 0; i < c1; ++i)
	{
		sg.m_values.push_back(lhs.m_values[i]);
	}
	for (int i = c2; i < rhs.length(); ++i)
	{
		sg.m_values.push_back(rhs.m_values[i]);
	}

	return sg;
}

SimpleGene Tai::randomGene(int size)
{
	vector<double> tmp;
	tmp.reserve(10*size);
	for (int cnt = 0; cnt < 10*size; ++cnt)
	{
			tmp.push_back(drandom());
	}
	SimpleGene sg;
	sg.values(tmp);
	return sg;
}
