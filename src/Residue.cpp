//
// Created by khristoforova-dasha on 09.01.2022.
//

#include "../include/Residue.h"

template<size_t Num>
Residue<Num> Residue<Num>::BinaryExponentiation(int exp) const {
    if (exp == 0) return 1;
    if (exp % 2) return (number * BinaryExponentiation(exp - 1)) % Num;
    Residue tmp = BinaryExponentiation(exp / 2);
    return (tmp * tmp) % Num;
}

template<size_t Num>
Residue<Num>::Residue(int elem) {
    number = (elem + (abs(elem) / Num + 1) * Num) % Num;
}

template<size_t Num>
Residue<Num> &Residue<Num>::operator=(const Residue<Num> &other) {
    number = other.number;
    return *this;
}

template<size_t Num>
Residue<Num> &Residue<Num>::operator*=(const Residue<Num> &other) {
    number *= other.number;
    number %= Num;
    return *this;
}

template<size_t Num>
Residue<Num> &Residue<Num>::operator+=(const Residue<Num> &other) {
    number += other.number;
    number %= Num;
    return *this;
}

template<size_t Num>
Residue<Num> &Residue<Num>::operator-=(const Residue<Num> &other) {
    number = number - other.number + Num;
    number %= Num;
    return *this;
}

template<size_t Num>
Residue<Num> &Residue<Num>::operator/=(const Residue<Num> &other) {
    static_assert(flag);
    number *= other.BinaryExponentiation(Num - 2);
    return *this;
}

template<size_t Num>
bool operator==(const Residue<Num>& first, const Residue<Num>& second) {
    return first.getResidue() == second.getResidue();
}

template<size_t Num>
bool operator!=(const Residue<Num>& first, const Residue<Num>& second) {
    return !(first == second);
}

template<size_t Num>
std::ostream& operator<<(std::ostream& out, const Residue<Num>& object) {
    out << object.getResidue();
    return out;
}

template<size_t Num>
Residue<Num> operator*(Residue<Num> first, const Residue<Num>& second) {
    first *= second;
    return first;
}

template<size_t Num>
Residue<Num> operator+(Residue<Num> first, const Residue<Num>& second) {
    first += second;
    return first;
}

template<size_t Num>
Residue<Num> operator-(Residue<Num> first, const Residue<Num>& second) {
    first -= second;
    return first;
}

template<size_t Num>
Residue<Num> operator/(Residue<Num> first, const Residue<Num>& second) {
    first /= second;
    return first;
}
