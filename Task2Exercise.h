#pragma once

#include "Exercise.h"

/**
 * @brief Класс Task2Exercise абстрактного класса Exercise
 */
class Task2Exercise : public Exercise {
	public:
		/**
		 * @brief Конструктор
		 * @param src - ссылка на матрицу
		 * @param gen - ссылка на генератор
		 */
		Task2Exercise(const Matrix<int>& src, Generator& gen);

		/**
		 * @brief Перегруженный деструктор
		 */
		~Task2Exercise() override = default;

		/**
		 * @brief Выполнить задание 2: вставить после каждой строки, содержащей максимальный
		 * по модулю элемент, последнюю строку (последняя строка берётся из исходной матрицы)
		 * @return Выполненное задание (новая матрица)
		 */
		Matrix<int> solve() const override;
};
