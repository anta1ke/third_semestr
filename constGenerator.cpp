#include "../include/ConstGenerator.h"

ConstGenerator::ConstGenerator(const int value) : constValue(value) {}

int ConstGenerator::generate() {
	return constValue;
}
