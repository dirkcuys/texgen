#ifndef TAI_SIMPLEFITNESS
#define TAI_SIMPLEFITNESS

namespace Tai
{
	// forward declaration
	class SimpleGene;

	class SimpleFitness
	{
	public:
		double calculate(const SimpleGene&);
	};
}; //namespace Tai

#endif //TAI_SIMPLEFITNESS
