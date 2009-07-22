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
	
	int populationSize = population.size();
	population.reserve(2*populationSize);

	for (int cnt = 0; cnt < populationSize; ++cnt)
	{
		int mate = int(populationSize*rand()/(1.0 * RAND_MAX));
		while (mate == cnt && populationSize > 2)
		{
			mate = int(populationSize*rand()/(1.0 * RAND_MAX));
		}

		Gene offspring = Gene::crossOver(population[cnt], population[mate]);
		offspring.mutate(0.5, 0.1);
		population.push_back(offspring);
	}


	typename vector<Gene>::iterator gene_it = population.begin();
	for (; gene_it != population.end(); ++gene_it)
	{
		fitnessFunction.calculate(*gene_it);
	}

	sort(population.begin(), population.end(), MoreFit());

	// kill of weaker part of population
	while (population.size() > populationSize)
	{
		population.pop_back();
	}
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
