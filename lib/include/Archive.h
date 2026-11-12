#pragma once

#include <string>
#include <vector>

#include "Convict.h"
#include "Investigator.h"
#include "Article.h"
#include "CriminalCase.h"

/**
 * @brief Класс Archive (архив уголовного розыска)
 */
class Archive {
	private:
		/**
		 * @brief Массив осужденных
		 */
		std::vector<Convict> convicts;

		/**
		 * @brief Массив следователей
		 */
		std::vector<Investigator> investigators;

		/**
		 * @brief Массив дел
		 */
		std::vector<CriminalCase> cases;

		/**
		 * @brief Массив статей
		 */
		std::vector<Article> articles;

	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		Archive() = default;

		/**
		 * @brief Деструктор
		 */
		~Archive() = default;

		/**
		 * @brief Добавить осужденного
		 * @param convict - ссылка на осужденного (в архив сохраняется копия)
		 * @throw std::invalid_argument - если человек с таким ID уже есть в архиве
		 */
		void addConvict(const Convict& convict);

		/**
		 * @brief Добавить следователя
		 * @param investigator - ссылка на следователя (в архив сохраняется копия)
		 * @throw std::invalid_argument - если человек с таким ID уже есть в архиве
		 */
		void addInvestigator(const Investigator& investigator);

		/**
		 * @brief Добавить статью
		 * @param article - статья
		 * @throw std::invalid_argument - если статья с таким номером уже есть в архиве
		 */
		void addArticle(const Article& article);

		/**
		 * @brief Добавить дело
		 * @param criminalCase - дело
		 * @throw std::invalid_argument - если дело с таким номером уже есть, если следователя
		 * с ID дела нет в архиве или если кого-то из осужденных дела нет в архиве
		 */
		void addCase(const CriminalCase& criminalCase);

		/**
		 * @brief Получить список осужденных
		 * @return ссылку на массив осужденных
		 */
		const std::vector<Convict>& getConvicts() const noexcept;

		/**
		 * @brief Получить список следователей
		 * @return ссылку на массив следователей
		 */
		const std::vector<Investigator>& getInvestigators() const noexcept;

		/**
		 * @brief Получить список дел
		 * @return ссылку на массив дел
		 */
		const std::vector<CriminalCase>& getCases() const noexcept;

		/**
		 * @brief Получить список статей
		 * @return ссылку на массив статей
		 */
		const std::vector<Article>& getArticles() const noexcept;

		/**
		 * @brief Проверить, есть ли в архиве осужденный с данным ID
		 * @param id - ID осужденного
		 * @return true - если есть, иначе false
		 */
		bool hasConvict(const int id) const noexcept;

		/**
		 * @brief Проверить, есть ли в архиве следователь с данным ID
		 * @param id - ID следователя
		 * @return true - если есть, иначе false
		 */
		bool hasInvestigator(const int id) const noexcept;

		/**
		 * @brief Найти осужденного по ID
		 * @param id - ID осужденного
		 * @return ссылку на осужденного
		 * @throw std::out_of_range - если осужденного с таким ID нет (проверить заранее можно через hasConvict)
		 */
		const Convict& findConvictById(const int id) const;

		/**
		 * @brief Найти следователя по ID
		 * @param id - ID следователя
		 * @return ссылку на следователя
		 * @throw std::out_of_range - если следователя с таким ID нет (проверить заранее можно через hasInvestigator)
		 */
		const Investigator& findInvestigatorById(const int id) const;

		/**
		 * @brief Получить информацию о деле с именами следователя и осужденных
		 * @param criminalCase - ссылка на дело
		 * @return строка с подробной информацией о деле
		 */
		std::string getCaseInfo(const CriminalCase& criminalCase) const;

		/**
		 * @brief Найти дела по ФИО осужденного
		 * @param fullName - ФИО осужденного
		 * @return массив найденных дел (копии)
		 */
		std::vector<CriminalCase> findByConvict(const std::string& fullName) const;

		/**
		 * @brief Найти дела, которые вёл данный следователь
		 * @param fullName - ФИО следователя
		 * @return массив найденных дел (копии)
		 */
		std::vector<CriminalCase> findByInvestigator(const std::string& fullName) const;

		/**
		 * @brief Найти дела по содержанию (поиск подстроки, чувствителен к регистру)
		 * @param keyword - искомый фрагмент текста (пустой фрагмент даёт пустой результат)
		 * @return массив найденных дел (копии)
		 */
		std::vector<CriminalCase> findByContent(const std::string& keyword) const;

		/**
		 * @brief Найти дела по статье преступления
		 * @param article - номер статьи либо характер преступления
		 * @return массив найденных дел (копии)
		 */
		std::vector<CriminalCase> findByArticle(const std::string& article) const;
};
