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

		int getLength();
		void mutate();

	private:
		std::vector<double> values;
	};
}; //namespace Tai

#endif //TAI_SIMPLEGENE_H
