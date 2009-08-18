#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <cmath>

// returns a value in 0..1
double randomd();

// implements the box muller polar form
double gauss(double mean = 0.0, double deviation = 1.0);

#endif //RANDOM_H
