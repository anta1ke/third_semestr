#include <algorithm>

#include "../include/RandomGenerator.h"

RandomGenerator::RandomGenerator(const int minVal, const int maxVal)
	: minValue(std::min(minVal, maxVal)), maxValue(std::max(minVal, maxVal)), engine(std::random_device{}()), distribution(minValue, maxValue) {}

int RandomGenerator::generate() {
	return distribution(engine);
}
