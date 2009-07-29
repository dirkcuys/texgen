#include "util.h"

#include <cstdlib>

double drandom()
{
	return 1.0*rand()/(1.0 + RAND_MAX);
}
