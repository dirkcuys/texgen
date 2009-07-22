#include "simplefitness.h"
#include "simplegene.h"

using namespace Tai;

double SimpleFitness::calculate(const SimpleGene& gene)
{
	m_sdl->renderGeneToSurface(gene);
	return 0.0;
}

