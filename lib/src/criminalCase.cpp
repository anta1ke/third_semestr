#include <algorithm>
#include <stdexcept>

#include "../include/CriminalCase.h"
#include "../include/Archive.h"

CriminalCase::CriminalCase() : year(0), investigatorId(0) {}

CriminalCase::CriminalCase(const Archive& archive, const std::string& number, const int year, const std::string& content, const Article& article, const int investigatorId)
	: number(number), year(year), content(content), article(article), investigatorId(investigatorId) {
	if (archive.hasCase(number)) {
		throw std::invalid_argument("Дело с номером " + number + " уже есть в архиве");
	}
	if (!archive.hasInvestigator(investigatorId)) {
		throw std::invalid_argument("Следователь с ID " + std::to_string(investigatorId) + " не найден");
	}
} {}

const std::string& CriminalCase::getNumber() const noexcept {return number;}

int CriminalCase::getYear() const noexcept {return year;}

const std::string& CriminalCase::getContent() const noexcept {return content;}

const Article& CriminalCase::getArticle() const noexcept {return article;}

int CriminalCase::getInvestigatorId() const noexcept {return investigatorId;}

const std::vector<int>& CriminalCase::getConvictIds() const noexcept {
	return convictIds;
}

void CriminalCase::addConvictId(const Archive& archive, const int convictId) {
	if (!archive.hasConvict(convictId)) {
		throw std::invalid_argument("Осужденный с ID " + std::to_string(convictId) + " не найден");
	}
	if (hasConvict(convictId)) {
		throw std::invalid_argument("Осужденный с ID " + std::to_string(convictId) + " уже добавлен в дело");
	}
	convictIds.push_back(convictId);
}

bool CriminalCase::hasConvict(const int convictId) const noexcept {
	return std::find(convictIds.begin(), convictIds.end(), convictId) != convictIds.end();
}

std::string CriminalCase::getInfo() const {
	std::string result = "Дело № " + number;
	result += " | Год: " + std::to_string(year);
	result += " | Статья: " + article.toString();
	result += " | Содержание: " + content;
	return result;
}
