//
// Created by khristoforova-dasha on 09.01.2022.
//
#include "Rational.h"
#ifndef MATRIX_RESIDUE_H
#define MATRIX_RESIDUE_H


template<size_t Num>
class Residue {
public:
    Residue() = default;

    Residue BinaryExponentiation(int exp) const;

    Residue(int elem);

    Residue<Num>& operator=(const Residue<Num>& other);

    Residue<Num>& operator*=(const Residue<Num>& other);

    Residue<Num>& operator+=(const Residue<Num>& other);

    Residue<Num>& operator-=(const Residue<Num>& other);

    Residue<Num>& operator/=(const Residue<Num>& other);

    int getResidue() const { return number; }

    operator int() { return number; }

    bool prime() { return flag; };
private:
    template<int Number, int Div, bool isGreater>
    class isPrime {
    public:
        static const bool flag = Number % Div != 0 && isPrime<Number, Div + 1, (Div * Div > Number)>::flag;
    };

    template<int Number, int Div>
    class isPrime<Number, Div, true> {
    public:
        static const bool flag = true;
    };

    static const bool flag = isPrime<Num, 2, false>::flag;
    int number = 0;
};
template<size_t Num>
Residue<Num> operator/(Residue<Num> first, const Residue<Num>& second);

template<size_t Num>
Residue<Num> operator-(Residue<Num> first, const Residue<Num>& second);

template<size_t Num>
Residue<Num> operator+(Residue<Num> first, const Residue<Num>& second);

template<size_t Num>
Residue<Num> operator*(Residue<Num> first, const Residue<Num>& second);

template<size_t Num>
std::ostream& operator<<(std::ostream& out, const Residue<Num>& object);

template<size_t Num>
bool operator!=(const Residue<Num>& first, const Residue<Num>& second);

template<size_t Num>
bool operator==(const Residue<Num>& first, const Residue<Num>& second);

#endif //MATRIX_RESIDUE_H
