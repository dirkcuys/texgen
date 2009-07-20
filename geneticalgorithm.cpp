#include <vector>

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

	typename vector<Gene>::iterator gene_it = population.begin();
	for (; gene_it != population.end(); ++gene_it)
	{
		fitnessFunction.calculate(*gene_it);
	}
}

