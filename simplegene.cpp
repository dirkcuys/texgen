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
	
	int c1 = int((rand()/(1.0 + RAND_MAX))*lhs.length());
	int c2 = int((rand()/(1.0 + RAND_MAX))*rhs.length());
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
		tmp.push_back(4.0*(rand()/(1.0 + RAND_MAX)) - 2.0);
		if ( (cnt - 3) % 10 == 0)
		{
			tmp[cnt] = rand()/(1.0 + RAND_MAX);
		}
	}
	SimpleGene sg;
	sg.values(tmp);
	return sg;
}
