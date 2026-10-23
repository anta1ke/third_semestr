#include <cstdlib>
#include <vector>

#include "../include/Task2Exercise.h"

Task2Exercise::Task2Exercise(const Matrix<int>& src, Generator& gen) : Exercise(src, gen) {}

Matrix<int> Task2Exercise::solve() const {
	const size_t rows = source.getRows();
	const size_t columns = source.getColumns();

	if (rows == 0 || columns == 0) {return Matrix<int>(source);}

	long long maxAbs = std::llabs(static_cast<long long>(source[0][0]));
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			const long long curAbs = std::llabs(static_cast<long long>(source[i][j]));
			if (curAbs > maxAbs) {
				maxAbs = curAbs;
			}
		}
	}

	std::vector<bool> hasMax(rows, false);
	size_t insertCount = 0;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			if (std::llabs(static_cast<long long>(source[i][j])) == maxAbs) {
				hasMax[i] = true;
				insertCount++;
				break;
			}
		}
	}

	const size_t lastRow = rows - 1;
	Matrix<int> result(rows + insertCount, columns);
	size_t current = 0;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			result[current][j] = source[i][j];
		}
		current++;
		if (hasMax[i]) {
			for (size_t j = 0; j < columns; j++) {
				result[current][j] = source[lastRow][j];
			}
			current++;
		}
	}

	return result;
}
