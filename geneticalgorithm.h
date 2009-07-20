#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>

namespace Tai
{
	template <class Gene, class FitnessFunction>
	class GeneticAlgorithm
	{
	public:
		GeneticAlgorithm(const FitnessFunction &);
		~GeneticAlgorithm();
	
		void iterate();

		typedef Gene GeneType;

	private:
		std::vector<Gene> population;
		FitnessFunction fitnessFunction;

	};
}; //namespace Tai

#include "geneticalgorithm.cpp"

#endif //GENETICALGORITHM_H
