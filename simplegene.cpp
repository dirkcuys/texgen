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
	m_fitness = 0;
	
	// mutate one value of some triagles
	for (int gi = 0; gi < m_values.size()/18.0; ++gi)
	{
		double randomValue = randomd();
		if (randomValue < mutateProb)
		{
			int ii = int(randomd()*18); // index in gene
			m_values[ii] += gauss(0.0, mutateFactor);
			if (ii % 18 > 5) // keep colors in (0,1)
				clamp(m_values[ii], 0.0, 1.0);
		}
	}
	
	// only mutate one value
	/*if (randomd() < mutateProb)
	{
		int mgene = int(m_values.size()*randomd());
		m_values[mgene] += gauss(0.0, mutateFactor);
		if (mgene % 18 > 5) // keep colors in (0,1)
				clamp(m_values[mgene], 0.0, 1.0);
		//return;
	}*/

	// try to shrink or grow if a value wasn't already mutated
	if (randomd() < growProb) // add a gene
	{
		grow();
	}
	else 
	{
		if (randomd() < shrinkProb)
		{
			shrink();
		}
	}
}

void SimpleGene::grow()
{
	m_values.reserve(m_values.size() + 18);
	double cx = randomd();
	double cy = randomd();
	for (int cnt = 0; cnt < 3; ++cnt)
	{
		//m_values.push_back(2.0*randomd() - 1.0);
		m_values.push_back(cx + gauss(0.0, 0.1));
		m_values.push_back(cy + gauss(0.0, 0.1));
	}
	
	for (int cntc = 6; cntc < 18; ++cntc)
	{
		m_values.push_back(randomd());
	}
}

void SimpleGene::shrink()
{
	double randomValue = m_values.size()/18.0*randomd();
	int dgene = 18*int(randomValue);
	for (int cnt = 17; cnt >= 0; --cnt)
	{
		swap(m_values[dgene + cnt], m_values.back());
		m_values.pop_back();
	}
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
	tmp.reserve(18*size);
	for (int cnt = 0; cnt < 18*size; ++cnt)
	{
			tmp.push_back(randomd());
	}
	SimpleGene sg;
	sg.values(tmp);
	return sg;
}
