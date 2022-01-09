//
// Created by khristoforova-dasha on 09.01.2022.
//

#include "Rational.h"
std::ostream& operator<<(std::ostream& out, const Rational& object) {
    string result = object.getNumerator().toString() + '/' + object.getDenominator().toString();
    out << result;
    return out;
}

std::istream& operator>>(std::istream& in, Rational& object) {
    string result;
    in >> result;
    object = Rational(BigInteger(result));
    return in;
}

Rational::Rational(const Rational& copy) : numerator(copy.numerator), denominator(copy.denominator) {}

void swap(Rational& first, Rational& second) {
    swap(first.numerator, second.numerator);
    swap(first.denominator, second.denominator);
}

Rational::Rational() {}

Rational::Rational(BigInteger big) : numerator(big) {}

Rational::Rational(ll integer) {
    numerator = integer;
}

Rational::Rational(BigInteger numerator_, BigInteger denominator_) : numerator(numerator_), denominator(denominator_) {
    if (numerator_.getSign() == denominator_.getSign()) numerator.abs();
    else numerator.noAbs();
    denominator.abs();
    BigInteger result = gcd(numerator, denominator);
    numerator /= result;
    denominator /= result;
}

string Rational::toString() {
    string answer = numerator.toString();
    string str = denominator.toString();
    if (str != "1") {
        answer += '/';
        answer += str;
    }
    return answer;
}

BigInteger abs(BigInteger object) {
    BigInteger res(object);
    res.abs();
    return res;
}

string Rational::asDecimal(size_t count) {
    string cur(count, '0');
    cur = '1' + cur;
    BigInteger precision(cur);
    string result;
    if (numerator < 0) result += '-';
    BigInteger resultInt = abs(numerator) / denominator;
    BigInteger resultFrac = abs(numerator) % denominator;
    resultFrac *= precision;
    resultFrac /= denominator;
    result += resultInt.toString();
    string resultFracStr = resultFrac.toString();
    string null;
    size_t cnt = count - resultFracStr.size();
    while (cnt > 0) null += '0', cnt--;
    if (count) result += '.' + null + resultFrac.toString();
    return result;
}

Rational& Rational::operator+=(const Rational& other) {
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator *= other.denominator;
    BigInteger result = gcd(numerator, denominator);
    numerator /= result;
    denominator /= result;
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    numerator = numerator * other.denominator - other.numerator * denominator;
    denominator *= other.denominator;
    BigInteger result = gcd(numerator, denominator);
    numerator /= result;
    denominator /= result;
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    BigInteger big = gcd(numerator, denominator);
    numerator /= big;
    denominator /= big;
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    if (this == &other) {
        *this = 1;
        return *this;
    }
    numerator *= other.denominator;
    denominator *= other.numerator;
    if (other.numerator.getSign() == Negative) {
        numerator.changeSign();
        denominator.changeSign();
    }
    BigInteger big = gcd(numerator, denominator);
    numerator /= big;
    denominator /= big;
    return *this;
}

bool operator==(const Rational& first, const Rational& second) {
    return (first.getSign() == second.getSign() && first.getNumerator() == second.getNumerator()
            && first.getDenominator() == second.getDenominator());
}

bool operator!=(const Rational& first, const Rational& second) {
    return !(first == second);
}

bool operator<(const Rational& first, const Rational& second) {
    if (first.getSign() != second.getSign()) return first.getSign() == Negative;
    return first.getNumerator() * second.getDenominator() < second.getNumerator() * first.getDenominator();
}

bool operator>(const Rational& first, const Rational& second) {
    return !(first < second) && (first != second);
}

bool operator<=(const Rational& first, const Rational& second) {
    return !(first > second);
}

bool operator>=(const Rational& first, const Rational& second) {
    return !(first < second);
}

Rational& Rational::operator=(Rational other) {
    swap(*this, other);
    return *this;
}

Rational Rational::operator-() {
    Rational result = *this;
    result.changeSign();
    return result;
}

Rational Rational::operator--(int) {
    Rational result = *this;
    *this -= 1;
    return result;
}

Rational& Rational::operator--() {
    *this -= 1;
    return *this;
}

Rational Rational::operator++(int) {
    Rational result = *this;
    *this += 1;
    return result;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}

BigInteger gcd(BigInteger first, BigInteger second) {
    first.abs(), second.abs();
    BigInteger res = 1;
    while (second) {
        if (first < second) {
            swap(first, second);
        } else if (first.isHonest() && second.isHonest()) {
            first /= 2;
            second /= 2;
            res *= 2;
        } else if (first.isHonest()) {
            first /= 2;
        } else if (second.isHonest()) {
            second /= 2;
        } else {
            first -= second;
        }
    }
    return first * res;
}

Rational operator+(Rational first, const Rational& second) {
    first += second;
    return first;
}

Rational operator-(Rational first, const Rational& second) {
    first -= second;
    return first;
}

Rational operator*(Rational first, const Rational& second) {
    first *= second;
    return first;
}

Rational operator/(Rational first, const Rational& second) {
    first /= second;
    return first;
}
