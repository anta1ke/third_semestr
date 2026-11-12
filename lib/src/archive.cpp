#include <algorithm>
#include <stdexcept>

#include "../include/Archive.h"

void Archive::addConvict(const Convict& convict) {
	if (hasConvict(convict.getId()) || hasInvestigator(convict.getId())) {
		throw std::invalid_argument("Человек с ID " + std::to_string(convict.getId()) + " уже есть в архиве");
	}
	convicts.push_back(convict);
}

void Archive::addInvestigator(const Investigator& investigator) {
	if (hasConvict(investigator.getId()) || hasInvestigator(investigator.getId())) {
		throw std::invalid_argument("Человек с ID " + std::to_string(investigator.getId()) + " уже есть в архиве");
	}
	investigators.push_back(investigator);
}

void Archive::addArticle(const Article& article) {
	auto it = std::find_if(articles.begin(), articles.end(), [&article](const Article& a) {
		return a.getNumber() == article.getNumber();
	});
	if (it != articles.end()) {
		throw std::invalid_argument("Статья " + article.getNumber() + " уже есть в архиве");
	}
	articles.push_back(article);
}

void Archive::addCase(const CriminalCase& criminalCase) {
	auto it = std::find_if(cases.begin(), cases.end(), [&criminalCase](const CriminalCase& c) {
		return c.getNumber() == criminalCase.getNumber();
	});
	if (it != cases.end()) {
		throw std::invalid_argument("Дело с номером " + criminalCase.getNumber() + " уже есть в архиве");
	}

	if (!hasInvestigator(criminalCase.getInvestigatorId())) {
		throw std::invalid_argument("Следователь с ID " + std::to_string(criminalCase.getInvestigatorId()) + " не найден");
	}

	for (const int convictId : criminalCase.getConvictIds()) {
		if (!hasConvict(convictId)) {
			throw std::invalid_argument("Осужденный с ID " + std::to_string(convictId) + " не найден");
		}
	}

	cases.push_back(criminalCase);
}

const std::vector<Convict>& Archive::getConvicts() const noexcept {
	return convicts;
}

const std::vector<Investigator>& Archive::getInvestigators() const noexcept {
	return investigators;
}

const std::vector<CriminalCase>& Archive::getCases() const noexcept {
	return cases;
}

const std::vector<Article>& Archive::getArticles() const noexcept {
	return articles;
}

bool Archive::hasConvict(const int id) const noexcept {
	for (const Convict& c : convicts) {
		if (c.getId() == id) {
			return true;
		}
	}
	return false;
}

bool Archive::hasInvestigator(const int id) const noexcept {
	for (const Investigator& i : investigators) {
		if (i.getId() == id) {
			return true;
		}
	}
	return false;
}

const Convict& Archive::findConvictById(const int id) const {
	for (const Convict& c : convicts) {
		if (c.getId() == id) {
			return c;
		}
	}
	throw std::out_of_range("Осужденный с ID " + std::to_string(id) + " не найден");
}

const Investigator& Archive::findInvestigatorById(const int id) const {
	for (const Investigator& i : investigators) {
		if (i.getId() == id) {
			return i;
		}
	}
	throw std::out_of_range("Следователь с ID " + std::to_string(id) + " не найден");
}

std::string Archive::getCaseInfo(const CriminalCase& criminalCase) const {
	std::string result = criminalCase.getInfo();

	const int investigatorId = criminalCase.getInvestigatorId();
	result += " | Следователь: ";
	result += hasInvestigator(investigatorId) ? findInvestigatorById(investigatorId).getFullName() : "не найден";

	result += " | Осужденные: ";
	if (criminalCase.getConvictIds().empty()) {
		result += "нет";
	}
	bool first = true;
	for (const int convictId : criminalCase.getConvictIds()) {
		if (!first) result += ", ";
		result += hasConvict(convictId) ? findConvictById(convictId).getFullName() : "не найден";
		first = false;
	}
	return result;
}

std::vector<CriminalCase> Archive::findByConvict(const std::string& fullName) const {
	std::vector<CriminalCase> result;
	for (const CriminalCase& c : cases) {
		for (const int convictId : c.getConvictIds()) {
			if (hasConvict(convictId) && findConvictById(convictId).getFullName() == fullName) {
				result.push_back(c);
				break;
			}
		}
	}
	return result;
}

std::vector<CriminalCase> Archive::findByInvestigator(const std::string& fullName) const {
	std::vector<CriminalCase> result;
	for (const CriminalCase& c : cases) {
		const int investigatorId = c.getInvestigatorId();
		if (hasInvestigator(investigatorId) && findInvestigatorById(investigatorId).getFullName() == fullName) {
			result.push_back(c);
		}
	}
	return result;
}

std::vector<CriminalCase> Archive::findByContent(const std::string& keyword) const {
	std::vector<CriminalCase> result;
	if (keyword.empty()) return result;
	for (const CriminalCase& c : cases) {
		if (c.getContent().find(keyword) != std::string::npos) {
			result.push_back(c);
		}
	}
	return result;
}

std::vector<CriminalCase> Archive::findByArticle(const std::string& article) const {
	std::vector<CriminalCase> result;
	for (const CriminalCase& c : cases) {
		if (c.getArticle().getNumber() == article || c.getArticle().getTitle() == article) {
			result.push_back(c);
		}
	}
	return result;
}
