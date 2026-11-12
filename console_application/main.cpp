#include <iostream>
#include <cstdlib>

#include "../lib/include/Matrix.h"
#include "../lib/include/ZeroGenerator.h"
#include "../lib/include/RandomGenerator.h"
#include "../lib/include/ConstGenerator.h"
#include "../lib/include/InputGenerator.h"
#include "../lib/include/Task1Exercise.h"
#include "../lib/include/Task2Exercise.h"

/**
 * @brief enum для выбора генератора
 */
enum gen {zero_fill, random_fill, const_fill, input_fill};

/**
 * @brief enum для выбора задания
 */
enum task {task1_choice, task2_choice};

/**
 * @brief Функция проверки, что указатель на сообщение непустой
 * @param message - сообщение
 * @return ничего не возвращает, если указатель непустой, иначе - завершает программу
 */
void checkMessage(const char* message);

/**
 * @brief Функция для получения целого положительного числа
 * @param message - сообщение
 * @return полученное число, если ввод успешен и пройдена проверка, иначе - завершает программу
 */
size_t getPos(const char* message);

/**
 * @brief Функция для получения целого числа
 * @param message - сообщение
 * @return полученное число, если ввод успешен, иначе - завершает программу
 */
int getInt(const char* message);

/**
 * @brief Функция выбора генератора и запуска обработки матрицы
 * @param matrix - ссылка на матрицу matrix
 * @param message - сообщение
 */
void chooseGenerator(Matrix<int>& matrix, const char* message);

/**
 * @brief Функция заполнения матрицы, вывода и выполнения задания
 * @param matrix - ссылка на матрицу matrix
 * @param generator - константная ссылка на генератор
 */
void processMatrix(Matrix<int>& matrix, const Generator& generator);

/**
 * @brief Функция выбора и выполнения задания
 * @param matrix - ссылка на матрицу matrix
 */
void runTask(const Matrix<int>& matrix);

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена успешно
 */
int main(void) {

	const size_t rows = getPos("Введите количество строк:");
	const size_t columns = getPos("Введите количество столбцов:");

	Matrix<int> matrix(rows, columns);

	chooseGenerator(matrix, "Выберите тип заполнения массива:");

	return 0;
}

void checkMessage(const char* message) {
	if (message == nullptr) {
		std::cerr << "Ошибка: передан пустой указатель на сообщение" << std::endl;
		std::exit(1);
	}
}

size_t getPos(const char* message) {
	checkMessage(message);
	size_t value = 0;
	std::cout << message << std::endl;
	if (std::cin >> value && value > 0) {
		return value;
	}
	std::cerr << "Некорректный ввод (введено не целое положительное число)" << std::endl;
	std::exit(1);
}

int getInt(const char* message) {
	checkMessage(message);
	int value = 0;
	std::cout << message << std::endl;
	if (std::cin >> value) return value;
	std::cerr << "Некорректный ввод (введено не целое число)" << std::endl;
	std::exit(1);
}

void chooseGenerator(Matrix<int>& matrix, const char* message) {
	checkMessage(message);
	std::cout << message << std::endl;
	std::cout << zero_fill << " - нулями\n"
		<< random_fill << " - случайными числами\n"
		<< const_fill << " - одинаковым числом (константой)\n"
		<< input_fill << " - ввод с клавиатуры\n" << std::endl;
	const int var = getInt("");
	switch (var) {
		case zero_fill: {
				  const ZeroGenerator generator{};
				  processMatrix(matrix, generator);
				  break;
				  }
		case random_fill: {
				  const int minVal = getInt("Введите минимум диапазона:");
				  const int maxVal = getInt("Введите максимум диапазона:");
				  const RandomGenerator generator(minVal, maxVal);
				  processMatrix(matrix, generator);
				  break;
				  }
		case const_fill: {
				 const int value = getInt("Введите значение константы:");
				 const ConstGenerator generator(value);
				 processMatrix(matrix, generator);
				 break;
				 }
		case input_fill: {
				 std::cout << "Введите значения массива:" << std::endl;
				 const InputGenerator generator(std::cin);
				 processMatrix(matrix, generator);
				 break;
				 }
		default:
				 std::cerr << "Некорректный выбор" << std::endl;
				 std::exit(1);
	}
}

void processMatrix(Matrix<int>& matrix, const Generator& generator) {
	matrix.fillArray(generator);
	std::cout << "Полученная матрица:\n" << matrix.toString() << std::endl;
	runTask(matrix);
}

void runTask(const Matrix<int>& matrix) {
	std::cout << "Выберите задание:\n"
		<< task1_choice << " - Задание 1. Заменить минимальный элемент каждого столбца нулем\n"
		<< task2_choice << " - Задание 2. Вставить после каждой строки, содержащей максимальный по модулю элемент, последнюю строку" << std::endl;
	const int var = getInt("");

	switch(var) {
		case task1_choice: {
				   const Task1Exercise task(matrix);
				   const Matrix<int> result = task.solve();
				   std::cout << "Результат:\n" << result.toString() << std::endl;
				   break;
				   }
		case task2_choice: {
				   const Task2Exercise task(matrix);
				   const Matrix<int> result = task.solve();
				   std::cout << "Результат:\n" << result.toString() << std::endl;
				   break;
				   }
		default:
				   std::cerr << "Некорректный выбор" << std::endl;
				   std::exit(1);
	}
}
