#pragma once

#include <memory>
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
		 * @brief Массив людей (осужденные и следователи хранятся как объекты базового типа)
		 */
		std::vector<std::unique_ptr<Person>> people;

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
		 * @brief Конструктор копирования запрещён (архив владеет людьми через unique_ptr)
		 */
		Archive(const Archive&) = delete;

		/**
		 * @brief Конструктор перемещения
		 */
		Archive(Archive&&) noexcept = default;

		/**
		 * @brief Оператор присваивания копированием запрещён
		 */
		Archive& operator=(const Archive&) = delete;

		/**
		 * @brief Оператор присваивания перемещением
		 */
		Archive& operator=(Archive&&) noexcept = default;

		/**
		 * @brief Деструктор
		 */
		~Archive() = default;

		/**
		 * @brief Добавить человека (объект Convict, Investigator или Person).
		 * Если человек с таким ID уже есть или указатель пустой, добавление игнорируется
		 * @param person - уникальный указатель на человека
		 */
		void addPerson(std::unique_ptr<Person> person);

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
		 * @return ссылку на массив людей (коллекция базового типа)
		 */
		const std::vector<std::unique_ptr<Person>>& getPeople() const noexcept;

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
		 * @brief Найти человека по ID
		 * @param id - ID человека
		 * @return указатель на человека, либо nullptr, если не найден
		 */
		const Person* findPersonById(const int id) const;

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
