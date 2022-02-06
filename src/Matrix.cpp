//
// Created by khristoforova-dasha on 09.01.2022.
//

#include "../include/Matrix.h"

template<size_t Rows, typename Field = Rational>
using SquareMatrix = Matrix<Rows, Rows, Field>;

template<size_t Rows, size_t Columns, typename Field = Rational>
std::ostream& operator<<(std::ostream& out, const Matrix<Rows, Columns, Field>& object) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            std::cerr << object.getElem(i, j) << " ";
        }
        std::cerr << '\n';
    }
    return out;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field>::Matrix(std::initializer_list<vector<Field>> list) {
    for (auto& row : list) {
        matrix.emplace_back(row);
    }
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field>::Matrix() {
    matrix.resize(Rows);
    for (size_t i = 0; i < Rows; ++i) {
        Row row(Columns);
        matrix[i] = row;
        if (Rows == Columns) matrix[i][i] = 1;
    }
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field>::Matrix(const vector<vector<Field>> &other) {
    for (size_t i = 0; i < Rows; ++i) {
        matrix.emplace_back(other[i]);
    }
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field>::Matrix(const Matrix<Rows, Columns, Field> &other) {
    matrix = other.matrix;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> &Matrix<Rows, Columns, Field>::operator=(const Matrix<Rows, Columns, Field> &other) {
    matrix = other.matrix;
    return *this;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> &Matrix<Rows, Columns, Field>::operator+=(const Matrix<Rows, Columns, Field> &other) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> &Matrix<Rows, Columns, Field>::operator-=(const Matrix<Rows, Columns, Field> &other) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Rows, Field> &Matrix<Rows, Columns, Field>::operator*=(const Matrix<Rows, Rows, Field> &other) {
    static_assert(Rows == Columns);
    *this = *this * other;
    return *this;
}

template<size_t Rows, size_t Columns, typename Field>
void Matrix<Rows, Columns, Field>::findWithoutZero(size_t column, size_t start) {
    for (size_t i = start; i < Rows; ++i) {
        if (matrix[i][column] != 0) {
            swap(matrix[start], matrix[i]);
            break;
        }
    }
}

template<size_t Rows, size_t Columns, typename Field>
std::pair<Matrix<Rows, Columns, Field>, size_t> Matrix<Rows, Columns, Field>::ToSimplified() const {
    Matrix<Rows, Columns, Field> result = *this;
    size_t column = 0, rank = Rows;
    for (size_t i = 0; i < Rows; ++i) {
        while (column < Columns && result.matrix[i][column] == 0) {
            result.findWithoutZero(column, i);
            if (result.matrix[i][column] != 0) break;
            column++;
        }
        for (size_t j = i + 1; j < Rows; ++j) {
            Field change = result.matrix[j][i] / result.matrix[i][i];
            for (size_t g = column; g < Columns; ++g) {
                result.matrix[j][g] -= change * result.matrix[i][g];
            }
        }
        if (column >= Columns - 1) {
            rank = i;
            if (column == Columns - 1) rank++;
            break;
        }
        column++;
    }
    return {result, rank};
}

template<size_t Rows, size_t Columns, typename Field>
Field Matrix<Rows, Columns, Field>::trace() const {
    static_assert(Rows == Columns);
    Field result;
    for (size_t i = 0; i < Rows; ++i) result += matrix[i][i];
    return result;
}

template<size_t Rows, size_t Columns, typename Field>
Field Matrix<Rows, Columns, Field>::det() const {
    static_assert(Rows == Columns);
    Matrix<Rows, Columns, Field> result = ToSimplified().first;
    Field determinant = 1;
    for (size_t i = 0; i < Rows; ++i) determinant *= result.matrix[i][i];
    return determinant;
}

template<size_t Rows, size_t Columns, typename Field>
size_t Matrix<Rows, Columns, Field>::rank() const {
    size_t ans = ToSimplified().second;
    return ans;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> &Matrix<Rows, Columns, Field>::operator*=(Field number) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            matrix[i][j] *= number;
        }
    }
    return *this;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Columns, Rows, Field> Matrix<Rows, Columns, Field>::transposed() const {
    Matrix<Columns, Rows, Field> result;
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

template<size_t Rows, size_t Columns, typename Field>
void Matrix<Rows, Columns, Field>::Identity() {
    for (int i = static_cast<int>(Rows) - 1; i >= 0; --i) {
        size_t pos = Columns;
        for (size_t j = 0; j < Columns; ++j) {
            if (matrix[i][j] != 0) {
                pos = j;
                break;
            }
        }
        for (int j = i - 1; j >= 0; --j) {
            Field elem;
            elem = matrix[j][pos] / matrix[i][pos];
            for (size_t g = pos; g < Columns; ++g) {
                matrix[j][g] -= matrix[i][g] * elem;
            }
        }
    }
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> &Matrix<Rows, Columns, Field>::invert() {
    static_assert(Rows == Columns);
    Matrix<Rows, 2 * Columns, Field> toInvert;
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < 2 * Columns; ++j) {
            if (j < Columns) toInvert[i][j] = matrix[i][j];
            else if (i == (j - Columns)) toInvert[i][j] = 1;
            else toInvert[i][j] = 0;
        }
    }
    std::pair<Matrix<Rows, 2 * Columns, Field>, size_t> result = toInvert.ToSimplified();
    result.first.Identity();
    for (size_t i = 0; i < Rows; ++i) {
        Field elem = result.first.getElem(i, i);
        for (size_t j = Columns; j < 2 * Columns; ++j) {
            matrix[i][j - Columns] = result.first.getElem(i, j) / elem;
        }
    }
    return *this;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> Matrix<Rows, Columns, Field>::inverted() const {
    Matrix<Rows, Columns, Field> result(*this);
    result.invert();
    return result;
}

template<size_t Rows, size_t Columns, typename Field>
bool operator==(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second) {
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Columns; ++j) {
            if (first[i][j] != second[i][j]) return false;
        }
    }
    return true;
}

template<size_t Rows, size_t Columns, typename Field>
bool operator!=(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second) {
    return !(first == second);
}

template<size_t Rows1, size_t Columns1, size_t Columns2, typename Field>
Matrix<Rows1, Columns2, Field>
operator*(const Matrix<Rows1, Columns1, Field>& first, const Matrix<Columns1, Columns2, Field>& second) {
    std::vector<std::vector<Field> > vec(Rows1, std::vector<Field>(Columns2));
    for (size_t i = 0; i < Rows1; ++i) {
        for (size_t j = 0; j < Columns2; ++j) {
            for (size_t g = 0; g < Columns1; ++g) {
                vec[i][j] += first.getElem(i, g) * second.getElem(g, j);
            }
        }
    }
    Matrix<Rows1, Columns2, Field> answer(vec);
    return answer;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> operator-(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second) {
    Matrix<Rows, Columns, Field> result = first;
    result -= second;
    return result;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> operator+(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second) {
    Matrix<Rows, Columns, Field> result = first;
    result += second;
    return result;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> operator*(Field number, Matrix<Rows, Columns, Field> result) {
    result *= number;
    return result;
}

template<size_t Rows, size_t Columns, typename Field>
Matrix<Rows, Columns, Field> operator*(Matrix<Rows, Columns, Field> result, Field number) {
    result *= number;
    return result;
}
