//
// Created by khristoforova-dasha on 09.01.2022.
//
#include "BigInteger.h"
#ifndef MATRIX_RATIONAL_H
#define MATRIX_RATIONAL_H


class Rational {
private:
    BigInteger numerator, denominator = 1;
public:
    Rational(BigInteger big);

    Rational(BigInteger numerator_, BigInteger denominator_);

    Rational();

    Rational(const Rational& copy);

    Rational(ll integer);

    string toString();

    string asDecimal(size_t count = 0);

    friend void swap(Rational& first, Rational& second);

    Rational& operator+=(const Rational& other);

    Rational& operator-=(const Rational& other);

    Rational& operator*=(const Rational& other);

    Rational& operator/=(const Rational& other);

    Rational& operator=(Rational other);

    Rational& operator++();

    Rational operator++(int);

    Rational& operator--();

    Rational operator--(int);

    Rational operator-();

    char getSign() const { return numerator.getSign(); }

    void checkSign();

    void changeSign() { numerator.changeSign(); }

    const BigInteger& getNumerator() const { return numerator; };

    const BigInteger& getDenominator() const { return denominator; };

    explicit operator double() {
        return std::strtod(asDecimal(30).c_str(), nullptr);
    }

    friend void swap(BigInteger& first, BigInteger& second);

    friend std::istream& operator>>(std::istream& in, Rational& object);
};


Rational operator+(Rational first, const Rational& second);

Rational operator-(Rational first, const Rational& second);

Rational operator*(Rational first, const Rational& second);

Rational operator/(Rational first, const Rational& second);

bool operator==(const Rational& first, const Rational& second);

bool operator!=(const Rational& first, const Rational& second);

bool operator<(const Rational& first, const Rational& second);

bool operator>(const Rational& first, const Rational& second);

bool operator<=(const Rational& first, const Rational& second);

bool operator>=(const Rational& first, const Rational& second);




#endif //MATRIX_RATIONAL_H
