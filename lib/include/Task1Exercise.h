#pragma once

#include "Exercise.h"

/**
 * @brief Класс Task1Exercise абстрактного класса Exercise
 */
class Task1Exercise : public Exercise {
	public:
		/**
		 * @brief Конструктор
		 * @param src - ссылка на матрицу
		 */
		explicit Task1Exercise(const Matrix<int>& src);

		/**
		 * @brief Перегруженный деструктор
		 */
		~Task1Exercise() override = default;

		/**
		 * @brief Выполнить задание 1: заменить минимальный элемент каждого столбца нулем
		 * (если минимальных элементов в столбце несколько, заменяется первый сверху)
		 * @return Выполненное задание (новая матрица)
		 */
		Matrix<int> solve() const override;
};
