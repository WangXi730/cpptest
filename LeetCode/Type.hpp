#include <iostream>
#include <sstream>

class Integer {
private:
    std::string value;
    bool isNegative = false;

public:
    Integer();
    Integer(const std::string& str);
    Integer(long long i);

    bool operator>=(const Integer& other) const;
    bool operator<=(const Integer& other) const;
    bool operator>(const Integer& other) const;
    bool operator<(const Integer& other) const;
    bool operator==(const Integer& other) const;
    bool operator!=(const Integer& other) const;

    Integer operator+(const Integer& other) const;
    Integer operator-(const Integer& other) const;
    Integer operator*(const Integer& other) const;
    Integer& operator*=(const Integer& other);
    Integer operator/(const Integer& other) const;
    Integer& operator/=(const Integer& other);
    Integer operator%(const Integer& other) const;
    //Integer operator<<(int shift) const;
    //Integer operator>>(int shift) const;
    Integer& operator++();
    Integer operator++(int);
    Integer& operator--();
    Integer operator--(int);
    Integer& operator+=(const Integer& other);
    Integer& operator-=(const Integer& other);

    friend std::ostream& operator<<(std::ostream& os, const Integer& integer);
    friend std::istream& operator>>(std::istream& is, Integer& integer);

private:
    static std::string usigned_add(const std::string& a, const std::string& b);
    static std::string usigned_dec(const std::string& a, const std::string& b);
    static bool unsigned_unlower(const std::string& a, const std::string& b);
};

// 构造函数的定义
Integer::Integer() :value("0")
{}
Integer::Integer(const std::string& str) : value(str) {
    if (!str.empty() && str[0] == '-') {
        isNegative = true;
        value = str.substr(1);
    }
    value.erase(0, std::min(value.find_first_not_of('0'), value.size() - 1));
}
Integer::Integer(long long i) {
    std::stringstream str;
    str << i;
    str >> (*this);
}

// >= 操作符的定义
bool Integer::operator>=(const Integer& other) const {
    bool res = true;
    if (this->isNegative && !other.isNegative) {
        return false;
    }
    else if (!this->isNegative && other.isNegative) {
        return true;
    }
    else if (this->isNegative && other.isNegative) {
        res = false;
    }
    if (res) {
        return unsigned_unlower(value, other.value);
    }
    else {
        return !unsigned_unlower(value, other.value);
    }
}

// 小于等于操作
bool Integer::operator<=(const Integer& other) const {
    return (*this) == other || (*this) < other;
}

// 大于操作
bool Integer::operator>(const Integer& other) const {
    return !(*this <= other);
}

// 小于操作
bool Integer::operator<(const Integer& other) const {
    return !(*this >= other);
}

// 等于操作
bool Integer::operator==(const Integer& other) const {
    return value == other.value && isNegative == other.isNegative;
}

// 不等于操作
bool Integer::operator!=(const Integer& other) const {
    return !(*this == other);
}

// + 操作符的定义
Integer Integer::operator+(const Integer& other) const {
    if (this->isNegative == other.isNegative) {
        Integer result = usigned_add(value, other.value);
        result.isNegative = this->isNegative;
        return result;
    }
    else {
        std::string a, b;
        bool sig;
        if (unsigned_unlower(value, other.value)) {
            a = value;
            b = other.value;
            sig = isNegative;
        }
        else {
            a = other.value;
            b = value;
            sig - other.isNegative;
        }
        Integer result = usigned_dec(a, b);
        result.isNegative = sig;
        return result;
    }
}

// - 操作符的定义
Integer Integer::operator-(const Integer& other) const {
    Integer result;
    if (this->isNegative != other.isNegative) {
        result.isNegative = this->isNegative;
        result.value = usigned_add(this->value, other.value);
    }
    else {
        if (unsigned_unlower(value, other.value)) {
            result.isNegative = isNegative;
            result.value = usigned_dec(value, other.value);
        }
        else {
            result.isNegative = other.isNegative;
            result.value = usigned_dec(other.value, value);
        }
    }
    return result;
}

// * 操作符的定义
Integer Integer::operator*(const Integer& other) const {
    std::string result(value.length() + other.value.length(), '0');

    for (int i = value.length() - 1; i >= 0; i--) {
        int carry = 0;
        int x = value[i] - '0';

        for (int j = other.value.length() - 1; j >= 0; j--) {
            int y = other.value[j] - '0';
            int product = x * y + carry + (result[i + j + 1] - '0');

            result[i + j + 1] = product % 10 + '0';
            carry = product / 10;
        }

        result[i] += carry;
    }

    result.erase(0, std::min(result.find_first_not_of('0'), result.size() - 1));
    Integer res = result;
    if (isNegative == other.isNegative) {
        res.isNegative = false;
    }
    else {
        res.isNegative = true;
    }
    return res;
}

Integer& Integer::operator*=(const Integer& other) {
    *this = *this * other;
    return *this;
}

// / 操作符的定义
Integer Integer::operator/(const Integer& other) const {
    if (other.value == "0") {
        throw std::invalid_argument("Division by zero");
    }

    std::string quotient("0");
    std::string remainder(this->value);

    while (unsigned_unlower(remainder, other.value)) {
        int shift = 0;

        while (unsigned_unlower(remainder, (other.value + std::string(shift, '0')))) {
            shift++;
        }

        if (shift > 0) {
            quotient = usigned_add(quotient, ("1" + std::string(shift - 1, '0')));
            remainder = usigned_dec(remainder, (other.value + std::string(shift - 1, '0')));
        }
        else {
            break;
        }
    }
    Integer res(quotient);
    if (isNegative == other.isNegative) {
        res.isNegative = false;
    }
    else {
        res.isNegative = true;
    }
    return res;
}

Integer& Integer::operator/=(const Integer& other) {
    *this = (*this) / other;
    return *this;
}


// % 操作符的定义
Integer Integer::operator%(const Integer& other) const {
    if (other.value == "0") {
        throw std::invalid_argument("Modulo by zero");
    }

    Integer quotient = *this / other;

    return *this - (quotient * other);
}
//
////重载左移操作
//Integer Integer::operator<<(int shift) const {
//    return Integer(value + std::string(shift, '0'));
//}
//
//// 位运算：逻辑右移
//Integer Integer::operator>>(int shift) const {
//    if (shift >= value.length()) {
//        return Integer("0");
//    }
//    else {
//        return Integer(value.substr(0, value.length() - shift));
//    }
//}
//
// << 操作符的定义
std::ostream& operator<<(std::ostream& os, const Integer& integer) {
    if (integer.isNegative && integer.value != "0") {
        os << "-";
    }
    os << integer.value;
    return os;
}

// >> 操作符的定义
std::istream& operator>>(std::istream& is, Integer& integer) {
    std::string s;
    is >> s;
    integer = s;
    return is;
}


// 自增操作
Integer& Integer::operator++() {
    *this = *this + Integer("1");
    return *this;
}

// 自增操作（后缀形式）
Integer Integer::operator++(int) {
    Integer temp = *this;
    ++(*this);
    return temp;
}

// 自减操作
Integer& Integer::operator--() {
    *this = *this - Integer("1");
    return *this;
}

// 自减操作（后缀形式）
Integer Integer::operator--(int) {
    Integer temp = *this;
    --(*this);
    return temp;
}

Integer& Integer::operator+=(const Integer& other) {
    *this = *this + other;
    return *this;
}

Integer& Integer::operator-=(const Integer& other) {
    *this = *this - other;
    return *this;
}


std::string Integer::usigned_add(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0;

    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int x = (i >= 0) ? a[i] - '0' : 0;
        int y = (j >= 0) ? b[j] - '0' : 0;

        int sum = x + y + carry;
        carry = sum / 10;
        sum %= 10;

        result.insert(result.begin(), sum + '0');

        i--;
        j--;
    }

    return result;

}
std::string Integer::usigned_dec(const std::string& a, const std::string& b) {
    std::string result;
    int borrow = 0;

    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0) {
        int x = (i >= 0) ? a[i] - '0' : 0;
        int y = (j >= 0) ? b[j] - '0' : 0;

        int diff = x - y - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        result.insert(result.begin(), diff + '0');

        i--;
        j--;
    }

    result.erase(0, std::min(result.find_first_not_of('0'), result.size() - 1));
    return result;
}

bool Integer::unsigned_unlower(const std::string& a, const std::string& b) {
    if (a.length() > b.length()) {
        return true;
    }
    else if (a.length() < b.length()) {
        return false;
    }
    else {
        return a >= b;
    }
}


template <typename _Ty = Integer>
class Fraction {
public:
    // 使用 value_type 别名
    using value_type = _Ty;

    // 构造函数
    Fraction(_Ty num = _Ty(0), _Ty den = _Ty(1));

    // 加法运算符重载
    Fraction<_Ty> operator+(const Fraction<_Ty>& other) const;

    // 减法运算符重载
    Fraction<_Ty> operator-(const Fraction<_Ty>& other) const;

    // 乘法运算符重载
    Fraction<_Ty> operator*(const Fraction<_Ty>& other) const;

    // 除法运算符重载
    Fraction<_Ty> operator/(const Fraction<_Ty>& other) const;

    // 输出运算符重载    
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        if (frac.numerator == _Ty(0) || frac.denominator == _Ty(1)) {
            os << frac.numerator;
        }
        else {
            os << frac.numerator << '/' << frac.denominator;
        }
        return os;
    }

private:
    _Ty numerator;
    _Ty denominator;

    // 辅助函数，计算最大公约数
    _Ty gcd(_Ty a, _Ty b);

    // 辅助函数，简化分数
    void simplify();
};

using Figure = Fraction<>;

// 构造函数定义
template <typename _Ty>
Fraction<_Ty>::Fraction(_Ty num, _Ty den) : numerator(num), denominator(den) {
    simplify();
}

// 加法运算符重载定义
template <typename _Ty>
Fraction<_Ty> Fraction<_Ty>::operator+(const Fraction& other) const {
    return Fraction(numerator * other.denominator + other.numerator * denominator,
        denominator * other.denominator);
}

// 减法运算符重载定义
template <typename _Ty>
Fraction<_Ty> Fraction<_Ty>::operator-(const Fraction& other) const {
    return Fraction(numerator * other.denominator - other.numerator * denominator,
        denominator * other.denominator);
}

// 乘法运算符重载定义
template <typename _Ty>
Fraction<_Ty> Fraction<_Ty>::operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

// 除法运算符重载定义
template <typename _Ty>
Fraction<_Ty> Fraction<_Ty>::operator/(const Fraction& other) const {
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

// 辅助函数，计算最大公约数
template <typename _Ty>
_Ty Fraction<_Ty>::gcd(_Ty a, _Ty b) {
    while (b != 0) {
        _Ty temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 辅助函数，简化分数
template <typename _Ty>
void Fraction<_Ty>::simplify() {
    _Ty commonDivisor = gcd(numerator, denominator);
    numerator /= commonDivisor;
    denominator /= commonDivisor;
}
