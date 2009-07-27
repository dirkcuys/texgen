#include "simplefitness.h"
#include "simplegene.h"

#include "image.h"

using namespace Tai;

double SimpleFitness::calculate(SimpleGene& gene)
{
	unsigned char* genImage = m_sdl->renderGeneToSurface(gene);
	Image* img = m_sdl->getImage();
	double totalFitness = 0;
	for (int i = 0; i < m_sdl->width()*m_sdl->height(); ++i)
	{
		double pixelFitness2 = 0;
		for (int j = 0; j < 3; ++j)
		{
			double tmp = genImage[4*i + j] - img->pixels[i].p[j];
			pixelFitness2 += tmp*tmp;
		}
		totalFitness += pixelFitness2;
	}
	//gene.fitness(totalFitness/(255*255*3*m_sdl->width()*m_sdl->height())*10 + gene.length());
	gene.fitness(totalFitness/(255*255*3*m_sdl->width()*m_sdl->height()));
	free(genImage);
	return gene.fitness();
}

