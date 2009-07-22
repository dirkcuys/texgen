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
		void mutate(double probability, double factor);

		static SimpleGene crossOver(const SimpleGene&, const SimpleGene&);

	private:
		std::vector<double> m_values;
		double m_fitness;
	};
}; //namespace Tai

#endif //TAI_SIMPLEGENE_H
