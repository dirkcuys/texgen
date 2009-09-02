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

#ifndef TAI_SIMPLEGENE_H
#define TAI_SIMPLEGENE_H

#include <vector>

namespace Tai
{
	class SimpleGene
	{
	public:
		SimpleGene();
		~SimpleGene();

		int length() const;
		double fitness() const;
		/// Sets and returns the new value
		double fitness( double );
		void mutate(double mutateProb, double factor, double growProb, double shrinkProb);

		const std::vector<double>& values() const { return m_values; };
		void values(std::vector<double> values_) { m_values = values_; };

		static SimpleGene crossOver(const SimpleGene&, const SimpleGene&);

	private:
		std::vector<double> m_values;
		double m_fitness;
	};

	SimpleGene randomGene(int size);
}; //namespace Tai

#endif //TAI_SIMPLEGENE_H
