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

#include "simplefitness.h"

#include "simplegene.h"
#include "image.h"

#include <iostream>

using namespace Tai;
using namespace std;

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
		//*
		double pixelFitness2 = 0;
		for (int j = 0; j < 3; ++j)
		{

			double tmp = genImage[4*i + j] - img->rawPixels[3*i + j];
			pixelFitness2 += tmp*tmp;
		}
		totalFitness += pixelFitness2;//*/

		/*
   		long r,g,b;
	    long rmean;

		rmean = ( (int)genImage[4*i] + (int)img->rawPixels[3*i] ) / 2;
		r = (int)genImage[4*i] - (int)img->rawPixels[3*i];
		g = (int)genImage[4*i + 1] - (int)img->rawPixels[3*i + 1];
		b = (int)genImage[4*i + 2] - (int)img->rawPixels[3*i + 2];
		totalFitness += (((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8);//*/

	}
	//gene.fitness(totalFitness/(size*3*m_sdl->width()*m_sdl->height())*10 + (gene.length()<10)?totalFitness:gene.length() );
	//gene.fitness(totalFitness/(255*255*3*m_sdl->width()*m_sdl->height()));
	gene.fitness(totalFitness);
	free(genImage);
	return gene.fitness();
}


