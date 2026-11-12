#pragma once

#include "Matrix.h"

/**
 * @brief Абстрактный класс Exercise
 */
class Exercise {
	protected:
		/**
		 * @brief ссылка на исходную матрицу
		 */
		const Matrix<int>& source;

	public:
		/**
		 * @brief Конструктор
		 * @param src - ссылка на матрицу
		 * @param gen - ссылка на генератор
		 */
		Exercise(const Matrix<int>& src);

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
