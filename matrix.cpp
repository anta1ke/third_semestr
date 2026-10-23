#include <iostream>
#include <utility>

#include "../include/Matrix.h"

template <typename T>
Matrix<T>::Matrix() : rows(0), columns(0), arr(nullptr) {}

template <typename T>
Matrix<T>::Matrix(const size_t r, const size_t c) : rows(r), columns(c), arr(nullptr) {
	if (rows == 0 || columns == 0) {
		return;
	}
	arr = new T* [rows];
	for (size_t i = 0; i < rows; i++) {
		arr[i] = new T[columns]();
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns), arr(nullptr) {
	if (rows == 0 || columns == 0) {
		return;
	}
	arr = new T* [rows];
	for (size_t i = 0; i < rows; i++) {
		arr[i] = new T[columns]();
		for (size_t j = 0; j < columns; j++) {
			arr[i][j] = other.arr[i][j];
		}
	}
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept : rows(other.rows), columns(other.columns), arr(other.arr) {
	other.rows = 0;
	other.columns = 0;
	other.arr = nullptr;
}

template <typename T>
Matrix<T>::~Matrix() {
	if (arr != nullptr) {
		for (size_t i = 0; i < rows; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
	if (this == &other) return *this;
	Matrix temp(other);

	std::swap(rows, temp.rows);
	std::swap(columns, temp.columns);
	std::swap(arr, temp.arr);

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
	if (this == &other) return *this;
	Matrix temp(std::move(other));

	std::swap(rows, temp.rows);
	std::swap(columns, temp.columns);
	std::swap(arr, temp.arr);

	return *this;
}

template <typename T>
size_t Matrix<T>::getRows() const noexcept {return rows;}

template <typename T>
size_t Matrix<T>::getColumns() const noexcept {return columns;}

template <typename T>
T* Matrix<T>::operator[](const size_t index) {
	return arr[index];
}

template <typename T>
const T* Matrix<T>::operator[](const size_t index) const {
	return arr[index];
}

template <typename T>
std::string Matrix<T>::toString() const {
	std::string result;
	if (rows == 0 || columns == 0) {
		return result;
	}
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			result += std::to_string(arr[i][j]);
			if (j + 1 < columns) {
				result += ' ';
			}
		}
		if (i + 1 < rows) {
			result += '\n';
		}
	}

	return result;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other) const {
	if (rows != other.rows) return false;
	if (columns != other.columns) return false;
	if (rows == 0 || columns == 0) return true;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			if (arr[i][j] != other.arr[i][j]) return false;
		}
	}
	return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& other) const {
	return !(*this == other);
}

template <typename T>
void Matrix<T>::fillArray(Generator& generator) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			arr[i][j] = static_cast<T>(generator.generate());
		}
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& M) {
	os << M.getRows() << ' ' << M.getColumns() << '\n';
	os << M.toString();
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& M) {
	size_t newRows = 0;
	size_t newColumns = 0;
	is >> newRows >> newColumns;
	if (!is) return is;
	if ((newRows == 0) != (newColumns == 0)) {
		is.setstate(std::ios::failbit);
		return is;
	} else if (newRows == 0 && newColumns == 0) {
		M = Matrix<T>();
		return is;
	}
	Matrix<T> temp(newRows, newColumns);
	for (size_t i = 0; i < newRows; i++) {
		for (size_t j = 0; j < newColumns; j++) {
			if (!(is >> temp[i][j])) return is;
		}
	}
	M = std::move(temp);
	return is;
}

// Явная инстанциация шаблона для используемых типов
template class Matrix<int>;
template class Matrix<double>;

template std::ostream& operator<<(std::ostream& os, const Matrix<int>& M);
template std::ostream& operator<<(std::ostream& os, const Matrix<double>& M);

template std::istream& operator>>(std::istream& is, Matrix<int>& M);
template std::istream& operator>>(std::istream& is, Matrix<double>& M);
