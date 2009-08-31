#ifndef UTIL_H
#define UTIL_H

template <typename T>
T clamp(const T& val, const T& min, const T& max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
}

#endif //UTIL
