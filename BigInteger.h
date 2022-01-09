//
// Created by khristoforova-dasha on 09.01.2022.
//

#ifndef MATRIX_BIGINTEGER_H
#define MATRIX_BIGINTEGER_H


#include <initializer_list>
#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::min;
using std::swap;
using ll = long long;

class BigInteger;

bool operator!=(const BigInteger& first, const BigInteger& second);

enum Sign {
    Negative,
    Positive
};

class BigInteger {
private:
    static const int BLOCK = 9;
    static const int BASE = 1e9;
    std::vector<int> number;

    void reverse(string& digit);

    void checkNull();

    int checkNull() const;

    bool sign = Positive;
public:
    void changeSign();

    void abs() { sign = Positive; }

    void noAbs() { sign = Negative; }

    explicit BigInteger(string& str);

    BigInteger(ll integer);

    BigInteger();

    BigInteger(const BigInteger& copy);

    friend void swap(BigInteger& first, BigInteger& second);

    BigInteger& operator-=(const BigInteger& other);

    BigInteger& operator+=(const BigInteger& other);

    BigInteger& operator*=(const BigInteger& other);

    BigInteger& operator%=(const BigInteger& other);

    BigInteger& operator/=(const BigInteger& other);

    BigInteger& operator=(BigInteger other);

    BigInteger& operator++();

    BigInteger& operator/=(ll other);

    BigInteger operator++(int);

    BigInteger& operator--();

    BigInteger operator--(int);

    BigInteger operator-();

    string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const BigInteger& object);

    friend std::istream& operator>>(std::istream& in, BigInteger& object);

    size_t getSize() const { return number.size(); };

    int getElem(size_t index) const { return number[index]; };

    char getSign() const { return sign; }

    explicit operator bool() const { return (*this != 0); }

    bool isHonest() const {
        if (!number.size()) return true;
        return !(number[0] % 2);
    }
};

BigInteger operator*(BigInteger first, const BigInteger& second);

BigInteger operator/(BigInteger first, const BigInteger& second);

BigInteger operator+(BigInteger first, const BigInteger& second);

BigInteger operator-(BigInteger first, const BigInteger& second);

BigInteger operator%(BigInteger first, const BigInteger& second);

bool operator==(const BigInteger& first, const BigInteger& second);

bool operator<(const BigInteger& first, const BigInteger& second);

bool operator>(const BigInteger& first, const BigInteger& second);

bool operator>=(const BigInteger& first, const BigInteger& second);

bool operator<=(const BigInteger& first, const BigInteger& second);

bool GreatestWithoutSign(const BigInteger& first, const BigInteger& second);

BigInteger gcd(BigInteger first, BigInteger second);

#endif //MATRIX_BIGINTEGER_H
