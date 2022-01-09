//
// Created by khristoforova-dasha on 09.01.2022.
//

#include "BigInteger.h"

bool GreatestWithoutSign(const BigInteger& first, const BigInteger& second) {
    size_t ourSize = first.getSize(), otherSize = second.getSize();
    if (ourSize == otherSize) {
        if (ourSize == 0) return 0;
        for (int i = static_cast<int>(ourSize) - 1; i >= 0; --i) {
            int one = first.getElem(i);
            int two = second.getElem(i);
            if (one < two) return 1;
            if (two < one) return 0;
        }
        return 0;
    }
    return ourSize < otherSize;
}

int BigInteger::checkNull() const {
    int id = static_cast<int>(number.size()) - 1;
    while (id > -1 && number[id] == 0) id--;
    return id;
}

void BigInteger::checkNull() {
    int id = static_cast<int>(number.size()) - 1;
    while (id >= 1 && number[id] == 0) number.pop_back(), id--;
    if (id == 0 && number[0] == 0) sign = Positive;
}

void BigInteger::reverse(string& digit) {
    size_t sz = digit.size();
    for (size_t i = 0; i < sz / 2; ++i) swap(digit[i], digit[sz - i - 1]);
}

void BigInteger::changeSign() {
    if (sign == Positive) sign = Negative;
    else sign = Positive;
}

BigInteger::BigInteger(string& str) {
    size_t size = str.size(), index = 0;
    if (str[0] == '-') sign = Negative;
    if (str[0] == '-' || str[0] == '+') index = 1;
    string strReverse(size - index, ' ');
    for (size_t i = index; i < size; ++i) strReverse[i - index] = str[size + index - i - 1];
    for (size_t i = 0; i < strReverse.size(); i += BLOCK) {
        string digit = strReverse.substr(i, BLOCK);
        reverse(digit);
        number.push_back(std::stoi(digit));
    }
}

BigInteger::BigInteger(ll integer) {
    if (integer < 0) sign = Negative, integer *= -1;
    if (integer == 0) number.push_back(0);
    else while (integer) number.push_back(integer % BASE), integer /= BASE;
}

BigInteger::BigInteger() = default;

BigInteger::BigInteger(const BigInteger& copy) : number(copy.number), sign(copy.sign) {}

void swap(BigInteger& first, BigInteger& second) {
    using std::swap;
    if (&first != &second) {
        swap(first.sign, second.sign);
        swap(first.number, second.number);
    }
}

BigInteger& BigInteger::operator=(BigInteger other) {
    swap(*this, other);
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    if (other.getSign() != sign) {
        changeSign();
        *this += other;
        changeSign();
    } else {
        size_t otherSize = other.getSize(), thisSize = number.size();
        size_t id = 0;
        int last = 0;
        int mulSign = 1;
        if (GreatestWithoutSign(*this, other)) mulSign = -1;
        while (id < otherSize || id < thisSize) {
            int value =
                    mulSign * ((id < thisSize ? number[id] : 0) - (id < otherSize ? other.getElem(id) : 0)) - last;
            if (id != std::max(otherSize, thisSize) - 1 && value < 0) value += BASE, last = 1;
            else last = 0;
            if (id < thisSize) number[id] = value;
            else number.push_back(value);
            id++;
        }
        if (mulSign == -1) changeSign();
    }
    checkNull();
    return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    if (sign != other.getSign()) {
        changeSign();
        *this -= other;
        changeSign();
    } else {
        size_t otherSize = other.getSize(), thisSize = number.size();
        int remember = 0;
        for (size_t i = 0; i < std::max(otherSize, thisSize) || remember; ++i) {
            if (i == number.size()) number.push_back(0);
            number[i] += remember + (i < otherSize ? other.getElem(i) : 0);
            remember = number[i] >= BASE;
            if (remember) number[i] -= BASE;
        }
    }
    checkNull();
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    if (sign == other.getSign()) sign = Positive;
    else sign = Negative;
    size_t otherSize = other.getSize(), thisSize = number.size();
    if (otherSize == 1) {
        int remember = 0;
        for (size_t i = 0; i < number.size() || remember; ++i) {
            if (i == number.size()) number.push_back(0);
            ll cur = remember + number[i] * 1ll * other.number[0];
            number[i] = static_cast<int>(cur % BASE);
            remember = static_cast<int>(cur / BASE);
        }
    } else {
        vector<int> result(otherSize + thisSize);
        for (size_t i = 0; i < thisSize; ++i) {
            for (int j = 0, remember = 0; j < static_cast<int>(otherSize) || remember; ++j) {
                long long value =
                        result[i + j] + number[i] * 1ll * (j < static_cast<int> (otherSize) ? other.getElem(j) : 0) +
                        remember;
                result[i + j] = static_cast<int>(value % BASE);
                remember = static_cast<int>(value / BASE);
            }
        }
        number = result;
    }
    checkNull();
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    BigInteger current = *this;
    current /= other;
    current *= other;
    *this -= current;
    return *this;
}

BigInteger& BigInteger::operator/=(ll other) {
    int remember = 0;
    bool flag = (other > 0);
    if (sign == flag) sign = Positive;
    else sign = Negative;
    for (int i = static_cast<int>(number.size()) - 1; i >= 0; --i) {
        ll cur = number[i] + remember * 1ll * BASE;
        number[i] = static_cast<int>(cur / other);
        remember = static_cast<int>(cur % other);
    }
    checkNull();
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    if (GreatestWithoutSign(*this, other)) {
        *this = 0;
        abs();
        return *this;
    }
    if (sign != other.getSign()) sign = Negative;
    else sign = Positive;
    BigInteger current = 0, divider = other;
    divider.sign = Positive;
    vector<int> result;
    for (int i = static_cast<int>(number.size()) - 1; i >= 0; --i) {
        current *= BASE;
        current += number[i];
        if (current >= other) {
            int lhs = 0, rhs = BASE;
            while (rhs - lhs > 1) {
                int mid = (rhs + lhs) / 2;
                if (mid * divider <= current) lhs = mid;
                else rhs = mid;
            }
            current -= lhs * divider;
            result.push_back(lhs);
        } else result.push_back(0);
    }
    size_t resSize = result.size();
    for (size_t i = 0; i < resSize / 2; ++i) std::swap(result[i], result[resSize - i - 1]);
    number = result;
    checkNull();
    return *this;
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger result = *this;
    *this += 1;
    return result;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger result = *this;
    *this -= 1;
    return result;
}

BigInteger BigInteger::operator-() {
    BigInteger result = *this;
    result.changeSign();
    return result;
}

bool operator==(const BigInteger& first, const BigInteger& second) {
    if (first.getSign() != second.getSign()) return 0;
    size_t firstSize = first.getSize(), secondSize = second.getSize();
    if (firstSize == secondSize) {
        for (size_t i = 0; i < firstSize; ++i) {
            if (second.getElem(i) != first.getElem(i)) return 0;
        }
        return 1;
    }
    return 0;
}

bool operator!=(const BigInteger& first, const BigInteger& second) {
    return !(first == second);
}

bool operator<(const BigInteger& first, const BigInteger& second) {
    if (first.getSign() != second.getSign()) {
        if (first.getSign() == Negative) return 1;
        return 0;
    }
    bool flag = 1;
    if (first.getSign() == second.getSign() && first.getSign() == Negative) flag = 0;
    bool result = GreatestWithoutSign(first, second);
    return flag ? result : 1 - result;
}

bool operator>(const BigInteger& first, const BigInteger& second) {
    return !(first < second) && (first != second);
}

bool operator<=(const BigInteger& first, const BigInteger& second) {
    return !(first > second);
}

bool operator>=(const BigInteger& first, const BigInteger& second) {
    return !(first < second);
}

string BigInteger::toString() const {
    string result;
    int size = checkNull();
    if (size != -1 && sign == Negative) result += '-';
    bool flag = 0;
    for (int i = size; i >= 0; --i) {
        if (number[i] || flag) {
            string digit = std::to_string(number[i]);
            while (flag && digit.size() != 9) digit = '0' + digit;
            result += digit;
            flag = 1;
        }
    }
    if (!flag) result += '0';
    return result;
}

BigInteger operator/(BigInteger first, const BigInteger& second) {
    first /= second;
    return first;
}

BigInteger operator*(BigInteger first, const BigInteger& second) {
    first *= second;
    return first;
}

BigInteger operator-(BigInteger first, const BigInteger& second) {
    first -= second;
    return first;
}

BigInteger operator+(BigInteger first, const BigInteger& second) {
    first += second;
    return first;
}

BigInteger operator%(BigInteger first, const BigInteger& second) {
    first %= second;
    return first;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& object) {
    out << object.toString();
    return out;
}