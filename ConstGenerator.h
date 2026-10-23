#pragma once

#include "Generator.h"

/**
 * @brief Класс ConstGenerator абстрактного класса Generator (заполнение константой)
 */
class ConstGenerator : public Generator {
	private:
		/**
		 * @brief значение константы
		 */
		const int constValue;

	public:
		/**
		 * @brief Конструктор
		 * @param value - значение, которое будет возвращать generate
		 */
		explicit ConstGenerator(const int value);

		/**
		 * @brief Перегруженный деструктор
		 */
		~ConstGenerator() override = default;

		/**
		 * @brief Возвращает значение константы
		 * @return значение, заданное в конструкторе
		 */
		int generate() override;
};
