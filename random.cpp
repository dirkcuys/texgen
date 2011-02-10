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

#include "random.h" 

#include <cstdlib>
#include <cmath>

// returns a value in 0..1
double randomd(){
	return rand()/(1.0+RAND_MAX);
}

// implements the box muller polar form
double gauss(double mean, double deviation)
{
	static bool hasNext = false;
	static double nextRandom;
	
	if (hasNext)
	{
		hasNext = false;
		return mean + nextRandom*deviation;
	}
	
	double y1, y2;
	double d;
	do 
	{
		y1 = 2.0 * randomd() - 1.0;
		y2 = 2.0 * randomd() - 1.0;
		d = y1*y1 + y2*y2;
	} while (d >= 1.0 || d == 0.0);
	
	d = sqrt(-2.0*log(d)/d);
	
	nextRandom = d*y2;
	hasNext = true;
	
	return mean + d*y1*deviation;
}
