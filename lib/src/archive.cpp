#include <algorithm>
#include <stdexcept>

#include "../include/Archive.h"

void Archive::addPerson(const Person& person) {
	if (hasPerson(person.getId())) return;
	people.push_back(&person);
}

void Archive::addArticle(const Article& article) {
	auto it = std::find_if(articles.begin(), articles.end(), [&article](const Article& a) {
		return a.getNumber() == article.getNumber();
	});
	if (it != articles.end()) return;
	articles.push_back(article);
}

void Archive::addCase(const CriminalCase& criminalCase) {
	auto it = std::find_if(cases.begin(), cases.end(), [&criminalCase](const CriminalCase& c) {
		return c.getNumber() == criminalCase.getNumber();
	});
	if (it != cases.end()) return;
	cases.push_back(criminalCase);
}

const std::vector<const Person*>& Archive::getPeople() const noexcept {
	return people;
}

const std::vector<CriminalCase>& Archive::getCases() const noexcept {
	return cases;
}

const std::vector<Article>& Archive::getArticles() const noexcept {
	return articles;
}

bool Archive::hasPerson(const int id) const noexcept {
	for (const Person* p : people) {
		if (p != nullptr && p->getId() == id) {
			return true;
		}
	}
	return false;
}

const Person& Archive::findPersonById(const int id) const {
	for (const Person* p : people) {
		if (p != nullptr && p->getId() == id) {
			return *p;
		}
	}
	throw std::out_of_range("Человек с ID " + std::to_string(id) + " не найден");
}

std::string Archive::getCaseInfo(const CriminalCase& criminalCase) const {
	std::string result = criminalCase.getInfo();

	const int investigatorId = criminalCase.getInvestigatorId();
	result += " | Следователь: ";
	result += hasPerson(investigatorId) ? findPersonById(investigatorId).getFullName() : "не найден";

	result += " | Осужденные: ";
	if (criminalCase.getConvictIds().empty()) {
		result += "нет";
	}
	bool first = true;
	for (const int convictId : criminalCase.getConvictIds()) {
		if (!first) result += ", ";
		result += hasPerson(convictId) ? findPersonById(convictId).getFullName() : "не найден";
		first = false;
	}
	return result;
}

std::vector<const CriminalCase*> Archive::findByConvict(const std::string& fullName) const {
	std::vector<const CriminalCase*> result;
	for (const CriminalCase& c : cases) {
		for (const int convictId : c.getConvictIds()) {
			if (!hasPerson(convictId)) continue;
			const Person& person = findPersonById(convictId);
			if (dynamic_cast<const Convict*>(&person) != nullptr && person.getFullName() == fullName) {
				result.push_back(&c);
				break;
			}
		}
	}
	return result;
}

std::vector<const CriminalCase*> Archive::findByInvestigator(const std::string& fullName) const {
	std::vector<const CriminalCase*> result;
	for (const CriminalCase& c : cases) {
		if (!hasPerson(c.getInvestigatorId())) continue;
		const Person& person = findPersonById(c.getInvestigatorId());
		if (dynamic_cast<const Investigator*>(&person) != nullptr && person.getFullName() == fullName) {
			result.push_back(&c);
		}
	}
	return result;
}

std::vector<const CriminalCase*> Archive::findByContent(const std::string& keyword) const {
	std::vector<const CriminalCase*> result;
	if (keyword.empty()) return result;
	for (const CriminalCase& c : cases) {
		if (c.getContent().find(keyword) != std::string::npos) {
			result.push_back(&c);
		}
	}
	return result;
}

std::vector<const CriminalCase*> Archive::findByArticle(const std::string& article) const {
	std::vector<const CriminalCase*> result;
	for (const CriminalCase& c : cases) {
		if (c.getArticle().getNumber() == article || c.getArticle().getTitle() == article) {
			result.push_back(&c);
		}
	}
	return result;
}
