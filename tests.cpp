#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <utility>

#include "../lib/include/Matrix.h"
#include "../lib/include/ZeroGenerator.h"
#include "../lib/include/ConstGenerator.h"
#include "../lib/include/RandomGenerator.h"
#include "../lib/include/InputGenerator.h"
#include "../lib/include/Task1Exercise.h"
#include "../lib/include/Task2Exercise.h"

// Matrix: конструкторы

TEST(MatrixConstructors, DefaultIsEmpty) {
    const Matrix<int> m;
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getColumns(), 0u);
    EXPECT_EQ(m.toString(), "");
}

TEST(MatrixConstructors, SizedMatrixIsZeroFilled) {
    const Matrix<int> m(3, 4);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m.getColumns(), 4u);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(MatrixConstructors, DoubleMatrixIsZeroFilled) {
    const Matrix<double> m(2, 2);
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            EXPECT_DOUBLE_EQ(m[i][j], 0.0);
        }
    }
}

// Matrix: копирование и перемещение

TEST(MatrixCopy, CopyIsDeep) {
    Matrix<int> a(2, 2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    Matrix<int> b = a;     // конструктор копирования
    b[0][0] = 999;

    EXPECT_EQ(a[0][0], 1);  // оригинал не изменился
    EXPECT_EQ(b[0][0], 999);
}

TEST(MatrixCopy, CopyAssignmentIsDeep) {
    Matrix<int> a(2, 2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    Matrix<int> b;
    b = a;                 // оператор присваивания копированием
    b[1][1] = 777;

    EXPECT_EQ(a[1][1], 4);
    EXPECT_EQ(b[1][1], 777);
}

TEST(MatrixMove, MoveConstructorLeavesSourceEmpty) {
    Matrix<int> a(2, 2);
    a[0][0] = 42;

    Matrix<int> b = std::move(a);
    EXPECT_EQ(b[0][0], 42);
    EXPECT_EQ(a.getRows(), 0u);
    EXPECT_EQ(a.getColumns(), 0u);
}

TEST(MatrixMove, MoveAssignmentMovesData) {
    Matrix<int> a(2, 2);
    a[1][1] = 8;

    Matrix<int> b;
    b = std::move(a);
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b[1][1], 8);
}

TEST(MatrixCopy, SelfAssignmentIsSafe) {
    Matrix<int> a(2, 2);
    a[0][0] = 5;
    Matrix<int>& ref = a;
    a = ref;               // не должно сломаться
    EXPECT_EQ(a[0][0], 5);
}

// Matrix: операторы сравнения

TEST(MatrixEquality, EqualMatrices) {
    const Matrix<int> a(2, 2);
    const Matrix<int> b(2, 2);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(MatrixEquality, DifferentValues) {
    const Matrix<int> a(2, 2);
    Matrix<int> b(2, 2);
    b[0][0] = 1;
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(MatrixEquality, DifferentSizes) {
    const Matrix<int> a(2, 2);
    const Matrix<int> b(3, 3);
    EXPECT_FALSE(a == b);
}

// Matrix: ввод/вывод

TEST(MatrixIO, ToStringFormat) {
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    EXPECT_EQ(m.toString(), "1 2\n3 4");
}

TEST(MatrixIO, OutputFormat) {
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    std::ostringstream os;
    os << m;
    EXPECT_EQ(os.str(), "2 2\n1 2\n3 4");
}

TEST(MatrixIO, InputRoundtrip) {
    std::istringstream is("2 3\n1 2 3\n4 5 6");
    Matrix<int> m;
    is >> m;

    EXPECT_EQ(m.getRows(), 2u);
    EXPECT_EQ(m.getColumns(), 3u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][2], 6);
}

TEST(MatrixIO, InputFailsOnBadData) {
    std::istringstream is("2 3\n1 2 3\n4 5 x");
    Matrix<int> m;
    is >> m;
    EXPECT_FALSE(is);
}

// Matrix: заполнение генератором

TEST(MatrixFill, FillWithConstant) {
    Matrix<int> m(2, 3);
    ConstGenerator gen(7);
    m.fillArray(gen);

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(m[i][j], 7);
        }
    }
}

TEST(MatrixFill, FillWithZeros) {
    Matrix<int> m(2, 2);
    ConstGenerator constGen(5);
    m.fillArray(constGen);

    ZeroGenerator zeroGen;
    m.fillArray(zeroGen);

    EXPECT_EQ(m, Matrix<int>(2, 2));
}

TEST(MatrixFill, FillFromStream) {
    std::istringstream is("1 2 3 4");
    InputGenerator gen(is);

    Matrix<int> m(2, 2);
    m.fillArray(gen);

    EXPECT_EQ(m.toString(), "1 2\n3 4");
}

// Generators

TEST(ZeroGeneratorTest, ReturnsZero) {
    ZeroGenerator gen;
    EXPECT_EQ(gen.generate(), 0);
    EXPECT_EQ(gen.generate(), 0);
}

TEST(ConstGeneratorTest, ReturnsConstant) {
    ConstGenerator gen(42);
    EXPECT_EQ(gen.generate(), 42);
    EXPECT_EQ(gen.generate(), 42);
    EXPECT_EQ(gen.generate(), 42);
}

TEST(RandomGeneratorTest, ValuesInRange) {
    RandomGenerator gen(-10, 10);
    for (int i = 0; i < 1000; i++) {
        const int v = gen.generate();
        EXPECT_GE(v, -10);
        EXPECT_LE(v, 10);
    }
}

TEST(RandomGeneratorTest, SwapsMinMaxIfReversed) {
    RandomGenerator gen(10, -10);   // нарочно наоборот
    for (int i = 0; i < 100; i++) {
        const int v = gen.generate();
        EXPECT_GE(v, -10);
        EXPECT_LE(v, 10);
    }
}

TEST(InputGeneratorTest, ReadsFromStream) {
    std::istringstream is("10 20 30");
    InputGenerator gen(is);
    EXPECT_EQ(gen.generate(), 10);
    EXPECT_EQ(gen.generate(), 20);
    EXPECT_EQ(gen.generate(), 30);
}

TEST(InputGeneratorTest, ReturnsZeroOnBadInput) {
    std::istringstream is("abc");
    InputGenerator gen(is);
    EXPECT_EQ(gen.generate(), 0);
}

// Task1: заменить минимальный элемент каждого столбца нулем

TEST(Task1Test, SimpleCase) {
    // Столбец 0: минимум -4 (строка 1)
    // Столбец 1: минимум -8 (строка 2)
    // Столбец 2: минимум -6 (строка 1)
    Matrix<int> m(3, 3);
    const int data[3][3] = {
        { 1,  2,  3},
        {-4,  5, -6},
        { 7, -8,  9}
    };
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m[i][j] = data[i][j];

    ZeroGenerator dummyGen;
    const Task1Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    EXPECT_EQ(result[1][0], 0);
    EXPECT_EQ(result[2][1], 0);
    EXPECT_EQ(result[1][2], 0);

    // остальные элементы не меняются
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[1][1], 5);
    EXPECT_EQ(result[2][2], 9);
}

TEST(Task1Test, OnlyFirstMinimumIsReplaced) {
    Matrix<int> m(3, 1);
    m[0][0] = 5; m[1][0] = 2; m[2][0] = 2;

    ZeroGenerator dummyGen;
    const Task1Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    EXPECT_EQ(result[0][0], 5);
    EXPECT_EQ(result[1][0], 0);
    EXPECT_EQ(result[2][0], 2);
}

TEST(Task1Test, OriginalIsNotModified) {
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    ZeroGenerator dummyGen;
    const Task1Exercise task(m, dummyGen);
    task.solve();

    // исходная матрица должна остаться прежней
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
}

TEST(Task1Test, EmptyMatrixReturnsEmpty) {
    const Matrix<int> m;
    ZeroGenerator dummyGen;
    const Task1Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    EXPECT_EQ(result.getRows(), 0u);
    EXPECT_EQ(result.getColumns(), 0u);
}

// Task2: вставить после каждой строки с максимальным по модулю элементом последнюю строку

TEST(Task2Test, SimpleCase) {
    // Максимальный по модулю элемент -9 в строке 1 → после неё вставляем последнюю строку
    Matrix<int> m(3, 2);
    m[0][0] = 1;  m[0][1] = 2;
    m[1][0] = -9; m[1][1] = 3;
    m[2][0] = 4;  m[2][1] = 5;

    ZeroGenerator dummyGen;
    const Task2Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    EXPECT_EQ(result.getRows(), 4u);
    EXPECT_EQ(result.getColumns(), 2u);
    EXPECT_EQ(result.toString(), "1 2\n-9 3\n4 5\n4 5");
}

TEST(Task2Test, MaximumInLastRow) {
    // Максимум в последней строке → после неё вставляется её копия
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 7; m[1][1] = 3;

    ZeroGenerator dummyGen;
    const Task2Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    EXPECT_EQ(result.toString(), "1 2\n7 3\n7 3");
}

TEST(Task2Test, MultipleRowsContainingMax) {
    Matrix<int> m(3, 2);
    m[0][0] = 5;  m[0][1] = 1;
    m[1][0] = 2;  m[1][1] = 3;
    m[2][0] = -5; m[2][1] = 0;

    ZeroGenerator dummyGen;
    const Task2Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    // максимум по модулю = 5 в строках 0 и 2
    EXPECT_EQ(result.getRows(), 5u);
    EXPECT_EQ(result.toString(), "5 1\n-5 0\n2 3\n-5 0\n-5 0");
}

TEST(Task2Test, SingleRow) {
    Matrix<int> m(1, 2);
    m[0][0] = 3; m[0][1] = 4;

    ZeroGenerator dummyGen;
    const Task2Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    EXPECT_EQ(result.toString(), "3 4\n3 4");
}

TEST(Task2Test, OriginalIsNotModified) {
    Matrix<int> m(3, 3);
    m[0][0] = 1; m[1][0] = 2; m[2][0] = 3;
    m[0][1] = 4; m[1][1] = 5; m[2][1] = 6;
    m[0][2] = 7; m[1][2] = 8; m[2][2] = 9;

    ZeroGenerator dummyGen;
    const Task2Exercise task(m, dummyGen);
    task.solve();

    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[2][2], 9);
}

TEST(Task2Test, EmptyMatrixReturnsEmpty) {
    const Matrix<int> m;
    ZeroGenerator dummyGen;
    const Task2Exercise task(m, dummyGen);
    const Matrix<int> result = task.solve();

    EXPECT_EQ(result.getRows(), 0u);
    EXPECT_EQ(result.getColumns(), 0u);
}
