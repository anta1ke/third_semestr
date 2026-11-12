#pragma once

#include <string>
#include <vector>

#include "Person.h"
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
		 * @brief Массив указателей на людей (осужденные и следователи хранятся как объекты базового типа).
		 * Архив не владеет людьми: сами объекты создаются снаружи и должны жить дольше архива
		 */
		std::vector<const Person*> people;

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
		 * @brief Добавить человека (объект Convict, Investigator или Person).
		 * Если человек с таким ID уже есть, добавление игнорируется
		 * @param person - ссылка на человека (объект должен жить дольше архива)
		 */
		void addPerson(const Person& person);

		/**
		 * @brief Добавить статью (статья с уже существующим номером игнорируется)
		 * @param article - статья
		 */
		void addArticle(const Article& article);

		/**
		 * @brief Добавить дело (дело с уже существующим номером игнорируется)
		 * @param criminalCase - дело
		 */
		void addCase(const CriminalCase& criminalCase);

		/**
		 * @brief Получить список людей
		 * @return ссылку на массив указателей на людей (коллекция базового типа)
		 */
		const std::vector<const Person*>& getPeople() const noexcept;

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
		 * @brief Проверить, есть ли в архиве человек с данным ID
		 * @param id - ID человека
		 * @return true - если человек есть, иначе false
		 */
		bool hasPerson(const int id) const noexcept;

		/**
		 * @brief Найти человека по ID
		 * @param id - ID человека
		 * @return ссылку на человека
		 * @throw std::out_of_range - если человека с таким ID нет (проверить заранее можно через hasPerson)
		 */
		const Person& findPersonById(const int id) const;

		/**
		 * @brief Получить информацию о деле с именами следователя и осужденных
		 * @param criminalCase - ссылка на дело
		 * @return строка с подробной информацией о деле
		 */
		std::string getCaseInfo(const CriminalCase& criminalCase) const;

		/**
		 * @brief Найти дела по ФИО осужденного
		 * @param fullName - ФИО осужденного
		 * @return массив указателей на найденные дела (действительны до следующего addCase)
		 */
		std::vector<const CriminalCase*> findByConvict(const std::string& fullName) const;

		/**
		 * @brief Найти дела, которые вёл данный следователь
		 * @param fullName - ФИО следователя
		 * @return массив указателей на найденные дела (действительны до следующего addCase)
		 */
		std::vector<const CriminalCase*> findByInvestigator(const std::string& fullName) const;

		/**
		 * @brief Найти дела по содержанию (поиск подстроки, чувствителен к регистру)
		 * @param keyword - искомый фрагмент текста (пустой фрагмент даёт пустой результат)
		 * @return массив указателей на найденные дела (действительны до следующего addCase)
		 */
		std::vector<const CriminalCase*> findByContent(const std::string& keyword) const;

		/**
		 * @brief Найти дела по статье преступления
		 * @param article - номер статьи либо характер преступления
		 * @return массив указателей на найденные дела (действительны до следующего addCase)
		 */
		std::vector<const CriminalCase*> findByArticle(const std::string& article) const;
};
