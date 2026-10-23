#include "../include/Person.h"

int Person::nextId = 1;

Person::Person() : id(nextId++) {}

Person::Person(const std::string& fullName, const std::string& birthDate, const int id)
	: id(id > 0 ? id : nextId++), fullName(fullName), birthDate(birthDate) {
	if (this->id >= nextId) {
		nextId = this->id + 1;
	}
}

int Person::getId() const noexcept {return id;}

const std::string& Person::getFullName() const noexcept {return fullName;}

const std::string& Person::getBirthDate() const noexcept {return birthDate;}

std::string Person::getInfo() const {
	return "ID: " + std::to_string(id) +
		" | ФИО: " + fullName +
		" | Дата рождения: " + birthDate;
}
