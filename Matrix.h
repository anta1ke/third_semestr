#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>

#include "Generator.h"

/**
 * @brief Шаблонный класс Matrix (двумерный массив)
 * @tparam T - тип элементов массива (арифметический тип, реализация доступна для int и double)
 */
template <typename T>
class Matrix {
	private:
		/**
		 * @brief количество строк в массиве
		 */
		size_t rows;

		/**
		 * @brief количество столбцов в массиве
		 */
		size_t columns;

		/**
		 * @brief указатель на массив
		 */
		T** arr;

	public:
		/**
		 * @brief Конструктор по умолчанию (пустая матрица)
		 */
		Matrix();

		/**
		 * @brief Конструктор матрицы rows * columns, заполненной нулями (создание матрицы из размеров)
		 * @param r - количество строк массива
		 * @param c - количество столбцов массива
		 */
		Matrix(const size_t r, const size_t c);

		/**
		 * @brief Конструктор копирования
		 * @param other - ссылка на другую матрицу
		 */
		Matrix(const Matrix& other);

		/**
		 * @brief Конструктор перемещения
		 * @param other - ссылка на другую (временную) матрицу
		 */
		Matrix(Matrix&& other) noexcept;

		/**
		 * @brief Деструктор
		 */
		~Matrix();

		/**
		 * @brief Оператор присваивания копированием
		 * @param other - ссылка на другую матрицу
		 * @return ссылку на скопированную матрицу
		 */
		Matrix& operator=(const Matrix& other);

		/**
		 * @brief Оператор присваивания перемещением
		 * @param other - ссылка на другую (временную) матрицу
		 * @return ссылку на перемещённую матрицу
		 */
		Matrix& operator=(Matrix&& other) noexcept;

		/**
		 * @brief Оператор "равно"
		 * @param other - ссылка на другую матрицу
		 * @return true - если матрицы равны, иначе false
		 */
		bool operator==(const Matrix& other) const;

		/**
		 * @brief Оператор "не равно"
		 * @param other - ссылка на другую матрицу
		 * @return true - если матрицы не равны, иначе false
		 */
		bool operator!=(const Matrix& other) const;

		/**
		 * @brief Вывести содержимое массива в строку
		 * @return Содержимое массива (элементы через пробел, строки через перевод строки)
		 */
		std::string toString() const;

		/**
		 * @brief Получить указатель на строку по индексу (только чтение)
		 * @param index - номер строки
		 * @return указатель на строку по индексу
		 */
		const T* operator[](const size_t index) const;

		/**
		 * @brief Получить указатель на строку по индексу
		 * @param index - номер строки
		 * @return указатель на строку по индексу
		 */
		T* operator[](const size_t index);

		/**
		 * @brief Функция получения количества строк массива
		 * @return число строк
		 */
		size_t getRows() const noexcept;

		/**
		 * @brief Функция получения количества столбцов массива
		 * @return число столбцов
		 */
		size_t getColumns() const noexcept;

		/**
		 * @brief Заполнение массива, используя абстрактный класс Generator
		 * @param generator - ссылка на генератор значений
		 */
		void fillArray(Generator& generator);
};

/**
 * @brief Перегрузка оператора сдвига влево (вывод матрицы в поток)
 * @param os - поток вывода
 * @param M - ссылка на матрицу M
 * @return перегруженный поток вывода
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& M);

/**
 * @brief Перегрузка оператора сдвига вправо (ввод матрицы из потока)
 * @param is - поток ввода
 * @param M - ссылка на матрицу M
 * @return перегруженный поток ввода
 */
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& M);
