#include "../include/Task1Exercise.h"

Task1Exercise::Task1Exercise(const Matrix<int>& src, Generator& gen) : Exercise(src, gen) {}

Matrix<int> Task1Exercise::solve() const {
	Matrix<int> result(source);

	const size_t rows = result.getRows();
	const size_t columns = result.getColumns();

	if (rows == 0 || columns == 0) {return result;}

	for (size_t j = 0; j < columns; j++) {
		size_t minRow = 0;
		for (size_t i = 1; i < rows; i++) {
			if (result[i][j] < result[minRow][j]) {
				minRow = i;
			}
		}
		result[minRow][j] = 0;
	}
	return result;
}
