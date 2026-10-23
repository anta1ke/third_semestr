#include <istream>

#include "../include/InputGenerator.h"

InputGenerator::InputGenerator(std::istream& inputValue) : input(inputValue) {}

int InputGenerator::generate() {
	int value = 0;
	input >> value;
	return value;
}
