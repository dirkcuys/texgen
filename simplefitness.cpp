#include "simplefitness.h"
#include "simplegene.h"

#include "image.h"

using namespace Tai;

double SimpleFitness::calculate(SimpleGene& gene)
{
	unsigned char* genImage = m_sdl->renderGeneToSurface(gene);
	Image* img = m_sdl->getImage();
	double totalFitness = 0;
	int w = m_sdl->width();
	int h = m_sdl->height();
	int size = w*h;
	for (int i = 0; i < size; ++i)
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
	//gene.fitness(totalFitness/(255*255*3*m_sdl->width()*m_sdl->height()));
	gene.fitness(totalFitness);
	free(genImage);
	return gene.fitness();
}

