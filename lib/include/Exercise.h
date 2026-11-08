#pragma once

#include "Matrix.h"
#include "Generator.h"

/**
 * @brief Абстрактный класс Exercise
 */
class Exercise {
	protected:
		/**
		 * @brief ссылка на исходную матрицу
		 */
		const Matrix<int>& source;

		/**
		 * @brief Ссылка на генератор значений
		 */
		Generator& generator;

	public:
		/**
		 * @brief Конструктор
		 * @param src - ссылка на матрицу
		 * @param gen - ссылка на генератор
		 */
		Exercise(const Matrix<int>& src, Generator& gen);

		/**
		 * @brief Виртуальный деструктор
		 */
		virtual ~Exercise() = default;

		/**
		 * @brief Виртуальный метод решения задания
		 * @return новая матрица - результат решения задания
		 */
		virtual Matrix<int> solve() const = 0;
};
