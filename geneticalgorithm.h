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

#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <functional>

#include "property.h"

namespace Tai
{
	template <class Gene, class FitnessFunction>
	class GeneticAlgorithm
	{
	public:
		typedef Gene GeneType;

		GeneticAlgorithm(const FitnessFunction &);
		~GeneticAlgorithm();
	
		void iterate();

		void setInitialPopulation(const std::vector<Gene> &);
		const GeneType& bestGene(){ return population[0];};
		const GeneType& worstGene(){ return population[population.size()-1];};

		//lng::Property<double> someValue;

	private:
		std::vector<Gene> population;
		FitnessFunction fitnessFunction;

		struct MoreFit : public std::binary_function<Gene, Gene, bool>
		{
			bool operator()(const Gene& g1, const Gene& g2)
			{
				return g1.fitness() < g2.fitness();
			}
		};
		
		std::vector<double> m_vResults;

	};
}; //namespace Tai

#include "geneticalgorithm.cpp"

#endif //GENETICALGORITHM_H
