#pragma once

#include <iosfwd>

#include "Generator.h"

/**
 * @brief Класс InputGenerator абстрактного класса Generator (ввод значений из потока)
 */
class InputGenerator : public Generator {
	private:
		/**
		 * @brief поток ввода
		 */
		std::istream& input;

	public:
		/**
		 * @brief Конструктор
		 * @param inputValue - ссылка на поток ввода
		 */
		explicit InputGenerator(std::istream& inputValue);

		/**
		 * @brief Перегруженный деструктор
		 */
		~InputGenerator() override = default;

		/**
		 * @brief Прочитать число из потока
		 * @return прочитанное число, либо 0 при ошибке
		 */
		int generate() override;
};
