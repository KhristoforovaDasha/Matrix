//
// Created by khristoforova-dasha on 09.01.2022.
//
#include "Residue.h"
#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


template<size_t Rows, size_t Columns, typename Field = Rational>
class Matrix {
public:
    class Row;

    Matrix(std::initializer_list<vector<Field> > list);

    Matrix();

    Matrix(const vector<vector<Field> >& other);

    Matrix(const Matrix<Rows, Columns, Field>& other);

    Matrix<Rows, Columns, Field>& operator=(const Matrix<Rows, Columns, Field>& other);

    Matrix<Rows, Columns, Field>& operator+=(const Matrix<Rows, Columns, Field>& other);

    Matrix<Rows, Columns, Field>& operator-=(const Matrix<Rows, Columns, Field>& other);

    Matrix<Rows, Rows, Field>& operator*=(const Matrix<Rows, Rows, Field>& other);

    void findWithoutZero(size_t column, size_t start);

    std::pair<Matrix<Rows, Columns, Field>, size_t> ToSimplified() const;

    Field trace() const;

    Field det() const;

    size_t rank() const;

    Matrix<Rows, Columns, Field>& operator*=(Field number);

    Matrix<Columns, Rows, Field> transposed() const;

    Row getRow(size_t index) const {
        return matrix[index];
    }

    Row getColumn(size_t index) const {
        Row result(Columns);
        for (size_t i = 0; i < Columns; ++i) result[i] = matrix[i][index];
        return result;
    }

    Field getElem(size_t i, size_t j) const { return matrix[i][j]; };

    void Identity();

    Matrix<Rows, Columns, Field>& invert();

    Matrix<Rows, Columns, Field> inverted() const;

    class Row {
    public:
        Row() = default;

        Row(size_t num) { row.resize(num, 0); }

        Row(const vector<Field>& other) : row(other) {}

        Row& operator=(const vector<Field>& other) {
            row = other;
            return *this;
        }

        Field& operator[](size_t j) { return row[j]; }

        const Field& operator[](size_t j) const { return row[j]; }

    private:
        vector<Field> row;
    };

    Row& operator[](size_t index) {
        return matrix[index];
    }

    const Row& operator[](size_t index) const {
        return matrix[index];
    }

    template<size_t Rows1, size_t Columns1, typename Field1>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<Rows1, Columns1, Field1>& object);

private:
    vector<Row> matrix;
};

template<size_t Rows, size_t Columns, typename Field = Rational>
bool operator==(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second);

template<size_t Rows, size_t Columns, typename Field = Rational>
bool operator!=(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second);

template<size_t Rows1, size_t Columns1, size_t Columns2, typename Field>
Matrix<Rows1, Columns2, Field> operator*(const Matrix<Rows1, Columns1, Field>& first, const Matrix<Columns1, Columns2, Field>& second);

template<size_t Rows, size_t Columns, typename Field = Rational>
Matrix<Rows, Columns, Field> operator-(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second);

template<size_t Rows, size_t Columns, typename Field = Rational>
Matrix<Rows, Columns, Field> operator+(const Matrix<Rows, Columns, Field>& first, const Matrix<Rows, Columns, Field>& second);

template<size_t Rows, size_t Columns, typename Field = Rational>
Matrix<Rows, Columns, Field> operator*(Matrix<Rows, Columns, Field> result, Field number);

template<size_t Rows, size_t Columns, typename Field = Rational>
Matrix<Rows, Columns, Field> operator*(Field number, Matrix<Rows, Columns, Field> result);



#endif //MATRIX_MATRIX_H
