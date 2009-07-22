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
