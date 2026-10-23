#pragma once

#include <random>

#include "Generator.h"

/**
 * @brief Генератор случайных чисел в диапазоне от minValue до maxValue
 */
class RandomGenerator : public Generator {
	private:
		/**
		 * @brief Минимальное значение диапазона генерации
		 */
		int minValue;

		/**
		 * @brief Максимальное значение диапазона генерации
		 */
		int maxValue;

		/**
		 * @brief Движок генерации псевдослучайных чисел
		 */
		std::mt19937 engine;

		/**
		 * @brief Равномерное распределение целых чисел для движка
		 */
		std::uniform_int_distribution<int> distribution;

	public:
		/**
		 * @brief Конструктор (если границы заданы наоборот, они меняются местами)
		 * @param minVal - минимальное значение диапазона
		 * @param maxVal - максимальное значение диапазона
		 */
		RandomGenerator(const int minVal, const int maxVal);

		/**
		 * @brief Перегруженный деструктор
		 */
		~RandomGenerator() override = default;

		/**
		 * @brief Генерация случайного числа
		 * @return сгенерированное число из диапазона [minValue; maxValue]
		 */
		int generate() override;
};
