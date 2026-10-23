#pragma once

#include <string>
#include <vector>

#include "Article.h"

/**
 * @brief Класс CriminalCase (Дело)
 */
class CriminalCase {
	private:
		/**
		 * @brief Номер дела
		 */
		std::string number;

		/**
		 * @brief Год дела
		 */
		int year;

		/**
		 * @brief Содержание дела
		 */
		std::string content;

		/**
		 * @brief Статья преступления
		 */
		Article article;

		/**
		 * @brief ID следователя, который вёл дело
		 */
		int investigatorId;

		/**
		 * @brief ID осужденных по делу
		 */
		std::vector<int> convictIds;

	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		CriminalCase();

		/**
		 * @brief Конструктор
		 * @param number - номер дела
		 * @param year - год дела
		 * @param content - содержание дела
		 * @param article - статья преступления
		 * @param investigatorId - ID следователя
		 */
		CriminalCase(const std::string& number, const int year, const std::string& content, const Article& article, const int investigatorId);

		/**
		 * @brief Получить номер дела
		 * @return номер дела
		 */
		const std::string& getNumber() const noexcept;

		/**
		 * @brief Получить год дела
		 * @return год дела
		 */
		int getYear() const noexcept;

		/**
		 * @brief Получить содержание дела
		 * @return содержание дела
		 */
		const std::string& getContent() const noexcept;

		/**
		 * @brief Получить статью преступления
		 * @return ссылку на статью
		 */
		const Article& getArticle() const noexcept;

		/**
		 * @brief Получить ID следователя
		 * @return ID следователя, который вёл дело
		 */
		int getInvestigatorId() const noexcept;

		/**
		 * @brief Получить ID осужденных по делу
		 * @return Массив ID осужденных
		 */
		const std::vector<int>& getConvictIds() const noexcept;

		/**
		 * @brief Добавить осужденного по делу
		 * @param convictId - ID осужденного
		 */
		void addConvictId(const int convictId);

		/**
		 * @brief Проверить, проходит ли осужденный с данным ID по делу
		 * @param convictId - ID осужденного
		 * @return true - если проходит, иначе false
		 */
		bool hasConvict(const int convictId) const noexcept;

		/**
		 * @brief Получение информации о деле
		 * @return строка с информацией о деле
		 */
		std::string getInfo() const;
};
