#pragma once

#include "Person.h"

/**
 * @brief Класс Investigator (следователь) - наследник класса Person
 */
class Investigator : public Person {
	private:
		/**
		 * @brief Звание следователя
		 */
		std::string rank;

	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		Investigator();

		/**
		 * @brief Конструктор
		 * @param fullName - ФИО следователя
		 * @param birthDate - дата рождения
		 * @param rank - звание
		 */
		Investigator(const std::string& fullName, const std::string& birthDate, const std::string& rank);

		/**
		 * @brief Получить звание следователя
		 * @return звание следователя
		 */
		const std::string& getRank() const noexcept;

		/**
		 * @brief Получение информации о следователе
		 * @return строка с информацией о следователе
		 */
		std::string getInfo() const override;
};
