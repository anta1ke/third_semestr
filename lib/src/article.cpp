#include <stdexcept>

#include "../include/Article.h"
#include "../include/Archive.h"

Article::Article(const Archive& archive, const std::string& number, const std::string& title) : number(number), title(title) {
	if (archive.hasArticle(number)) {
		throw std::invalid_argument("Статья " + number + " уже есть в архиве");
	}
}

const std::string& Article::getNumber() const noexcept {return number;}

const std::string& Article::getTitle() const noexcept {return title;}

std::string Article::toString() const {
	return number + " (" + title + ")";
}
