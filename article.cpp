#include "../include/Article.h"

Article::Article(const std::string& number, const std::string& title) : number(number), title(title) {}

const std::string& Article::getNumber() const noexcept {return number;}

const std::string& Article::getTitle() const noexcept {return title;}

std::string Article::toString() const {
	return number + " (" + title + ")";
}
