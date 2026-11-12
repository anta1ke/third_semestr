#pragma once

#include "Person.h"

/**
 * @brief Класс Convict (осужденный) - наследник класса Person
 */
class Convict : public Person {
	private:
		/**
		 * @brief Приговор (мера наказания)
		 */
		std::string sentence;

	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		Convict();

		/**
		 * @brief Конструктор
		 * @param fullName - ФИО осужденного
		 * @param birthDate - дата рождения
		 * @param sentence - приговор (мера наказания)
		 * @param id - id осужденного (0 для автогенерации)
		 */
		Convict(const std::string& fullName, const std::string& birthDate, const std::string& sentence, const int id = 0);

		/**
		 * @brief Получить приговор
		 * @return приговор (мера наказания)
		 */
		const std::string& getSentence() const noexcept;

		/**
		 * @brief Получение информации об осужденном
		 * @return строка с информацией об осужденном
		 */
		std::string getInfo() const override;
};
