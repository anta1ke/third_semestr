#include "../include/Convict.h"

Convict::Convict() : Person() {}

Convict::Convict(const std::string& fullName, const std::string& birthDate, const std::string& sentence, const int id)
	: Person(fullName, birthDate, id), sentence(sentence) {}

const std::string& Convict::getSentence() const noexcept {return sentence;}

std::string Convict::getInfo() const {
	std::string result = Person::getInfo();
	result += " | Осужденный | Приговор: " + sentence;
	return result;
}
