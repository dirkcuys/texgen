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

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include "random.h"

using namespace Tai;
using namespace std;

template <class Gene, class FitnessFunction>
GeneticAlgorithm<Gene,FitnessFunction>::GeneticAlgorithm(const FitnessFunction& ff) : fitnessFunction(ff)
{
}

template <class Gene, class FitnessFunction>
GeneticAlgorithm<Gene,FitnessFunction>::~GeneticAlgorithm()
{
}

template <class Gene, class FitnessFunction>
void GeneticAlgorithm<Gene,FitnessFunction>::iterate()
{

	// Selection for crossover
	// Mutation
	// Fitness Calculation
	// Selection of next generation
	
	int populationSize = population.size();
	//population.reserve(2*populationSize);

	for (int cnt = 0; cnt < populationSize; ++cnt)
	{
		int mate = int(randomd()*populationSize);
		while (mate == cnt && populationSize > 2)
		{
			mate = int(randomd()*populationSize);
		}

		Gene offspring;
		
		//if (randomd() > 0.5)
		//{
		//	offspring = Gene::crossOver(population[cnt], population[mate]);
		//}
		//else
		{
			offspring = population[cnt];
		}
		//Gene offspring(population[cnt]);// = Gene::crossOver(population[cnt], population[mate]);
		offspring.mutate(0.07, 0.01, 0.05, 0.05);
		//offspring.mutate(0.1, 0.5*(cnt + 1.0)/populationSize);
		fitnessFunction.calculate(offspring);
		if (offspring.fitness() < population[cnt].fitness())
		{
			population[cnt] = offspring;
		}
		//population.push_back(offspring);
	}


	/*typename vector<Gene>::iterator gene_it = population.begin();
	for (; gene_it != population.end(); ++gene_it)
	{
		fitnessFunction.calculate(*gene_it);
	}*/

	sort(population.begin(), population.end(), MoreFit());

	// kill of weaker part of population
	/*while (population.size() > populationSize)
	{
		population.pop_back();
	}*/
}

template<class Gene, class FitnessFunction>
void GeneticAlgorithm<Gene,FitnessFunction>::setInitialPopulation(const vector<Gene>& initialPopulation)
{
	population = initialPopulation;
	
	typename vector<Gene>::iterator gene_it = population.begin();
	for (; gene_it != population.end(); ++gene_it)
	{
		fitnessFunction.calculate(*gene_it);
	}

	sort(population.begin(), population.end(), MoreFit());
}
