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
		GeneticAlgorithm(const FitnessFunction &);
		~GeneticAlgorithm();
	
		void iterate();

		void setInitialPopulation(const std::vector<Gene> &);
		typedef Gene GeneType;

	private:
		std::vector<Gene> population;
		FitnessFunction fitnessFunction;

		struct MoreFit : public std::binary_function<Gene, Gene, bool>
		{
			bool operator()(const Gene& g1, const Gene& g2)
			{
				return g1.fitness() > g2.fitness();
			}
		};

	};
}; //namespace Tai

#include "geneticalgorithm.cpp"

#endif //GENETICALGORITHM_H
