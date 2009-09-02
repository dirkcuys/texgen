/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "simplegene.h"

#include "util.h"
#include "random.h"

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
	
void SimpleGene::mutate(double mutateProb, double mutateFactor, double growProb, double shrinkProb)
{
	for (int cnt = 0; cnt < m_values.size(); ++cnt)
	{
		double randomValue = randomd();
		if (randomValue < mutateProb)
		{
			m_values[cnt] += gauss(0.0, mutateFactor);
			if (cnt % 10 > 5) // keep colors in bound
				clamp(m_values[cnt], 0.0, 1.0);
		}
	}

	double randomValue = randomd();
	if (randomValue < growProb) // add a gene
	{
		for (int cnt = 0; cnt < 6; ++cnt)
		{
			m_values.push_back(2.0*randomd() - 1.0);
		}
		for (int cnt = 6; cnt < 10; ++cnt)
		{
			m_values.push_back(0.2*randomd());
		}
	}
	else 
	{
		randomValue = randomd();
		if (randomValue < shrinkProb)// probability)
		{
			randomValue = m_values.size()/10.0*randomd();
			int dgene = 10*int(randomValue);
			for (int cnt = 9; cnt >= 0; --cnt)
			{
				swap(m_values[dgene + cnt], m_values.back());
				m_values.pop_back();
			}
		}
	}

	m_fitness = 0;
}

//static function
SimpleGene SimpleGene::crossOver(const SimpleGene& lhs, const SimpleGene& rhs)
{
	// TODO do the crossover
	
	int c1 = int(randomd()*lhs.length());
	int c2 = int(randomd()*rhs.length());
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
			tmp.push_back(randomd());
	}
	SimpleGene sg;
	sg.values(tmp);
	return sg;
}
