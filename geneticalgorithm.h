#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <functional>

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

	};
}; //namespace Tai

#include "geneticalgorithm.cpp"

#endif //GENETICALGORITHM_H
