#pragma once

#include "Generator.h"

/**
 * @brief Класс ZeroGenerator абстрактного класса Generator (заполнение нулями)
 */
class ZeroGenerator : public Generator {
	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		ZeroGenerator() = default;

		/**
		 * @brief Перегруженный деструктор
		 */
		~ZeroGenerator() override = default;

		/**
		 * @brief Возвращает ноль
		 * @return всегда 0
		 */
		int generate() override;
};
