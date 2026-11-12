#include "../include/Investigator.h"

Investigator::Investigator() : Person() {}

Investigator::Investigator(const std::string& fullName, const std::string& birthDate, const std::string& rank)
	: Person(fullName, birthDate), rank(rank) {}

const std::string& Investigator::getRank() const noexcept {return rank;}

std::string Investigator::getInfo() const {
	std::string result = Person::getInfo();
	result += " | Следователь | Звание: " + rank;
	return result;
}
