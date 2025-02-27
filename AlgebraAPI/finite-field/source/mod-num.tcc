namespace modular {
#ifndef TASK2_TCC
#define TASK2_TCC
#include <cassert>
#include <iostream>

#ifndef MOD_NUM
#define MOD_NUM

template <typename T>
class modNum {
   private:
    mutable T value, MOD;

    T add(T value1, T value2, T MOD) const;
    T subs(T value1, T value2, T MOD) const;
    T mult(T value1, T value2, T MOD) const;
    T gcdExtended(T a, T b, T *x, T *y) const;
    T inverseValue(T value1, T mod) const;
    T div(T value1, T value2, T mod) const;

   public:
    modNum(T value = 0, T MOD = 1) : value(value), MOD(MOD) {
        if (MOD <= 0) {
            throw std::invalid_argument("modulus should be positive");
        }
    }

    T getValue() const;
    T getMod() const { return MOD; };
    void setMod(T MOD);

    bool operator==(const modNum<T> &other) const {
        return value == other.value && MOD == other.MOD;
    }

    bool operator<(const modNum<T> &other) const { return value < other.value; }

    bool operator<=(const modNum<T> &other) const { return value <= other.value; }

    bool operator>(const modNum<T> &other) const { return value > other.value; }

    bool operator>=(const modNum<T> &other) const { return value >= other.value; }

    modNum<T> inv();

    modNum<T> operator+(const modNum<T> &other) const;
    modNum<T> operator-(const modNum<T> &other) const;
    modNum<T> operator*(const modNum<T> &other) const;
    modNum<T> operator/(const modNum<T> &other) const;
};
#endif

/**
 * @brief Adds two values modulo MOD.
 * @param  value1 the first value to add
 * @param  value2 The second value to add.
 * @param MOD  The modulo value
 * @return The sum of the two values modulo MOD
 * @throws std::invalid_argument if MOD is non - positive
 */
template <typename T>
T
modNum<T>::add(T value1, T value2, T MOD) const {
    if (MOD <= 0) {
        throw std::invalid_argument("modulus should be positive");
    }
    T result = value1 + value2;
    result %= MOD;
    if (result < 0) {
        result += MOD;
    }
    return result;
}
/**
 *  @brief Subtract two values modulo MOD.
 *  @param  value1 the first value to be subtracted.
 *  @param  value2 The second value to be subtracted.
 *  @param MOD The modulo value
 *  @return The result of the subtraction with modulo operation.
 *  @throws std::invalid_argument if MOD is non-positive
 */
template <typename T>
T
modNum<T>::subs(T value1, T value2, T MOD) const {
    if (MOD <= 0) {
        throw std::invalid_argument("modulus should be positive");
    }
    T result = value1 - value2;
    result %= MOD;
    if (result < 0) {
        result += MOD;
    }
    return result;
}
/**
 *  @brief Multiply two values modulo MOD.
 *  @param  value1 the first value to multiply.
 *  @param  value2 The second value to multiply.
 *  @param MOD The modulo value
 *  @return The result of the multipilcation with modulo operation.
 *  @throws std::invalid_argument if MOD is non-positive
 */
template <typename T>
T
modNum<T>::mult(T value1, T value2, T MOD) const {
    if (MOD <= 0) {
        throw std::invalid_argument("modulus should be positive");
    }
    value1 = (value1 % MOD + MOD) % MOD;
    value2 = (value2 % MOD + MOD) % MOD;
    T result = 0;
    while (value2) {
        if (value2 % 2 == 1) {
            result = (result + value1) % MOD;
        }
        value1 = (value1 * 2) % MOD;
        value2 >>= 1;
    }
    return result;
}
template <typename T>
T
modNum<T>::gcdExtended(T a, T b, T *x, T *y) const {
    // Base Case
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    T x1, y1;   // To store results of recursive call
    T gcd = gcdExtended(b % a, a, &x1, &y1);
    // Update x and y using results of
    // recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

/**
 *  @brief Inverses the given element in a modular field
 *  @param  value1 element to be inversed
 *  @param MOD  module
 *
 *  @return returns inversed element
 */
template <typename T>
T
modNum<T>::inverseValue(T value1, T mod) const {
    T x, y;

    T gcdResult = gcdExtended(value1, mod, &x, &y);
    if (gcdResult != 1) {
        std::string errormsg = "Inverse does not exist here.";
        throw std::invalid_argument(errormsg);
    } else {
        x = (x % mod + mod) % mod;
        return x;
    }
}

/**
 *  @brief divides value1 by value2 in a modular field
 *  @param  value1 Terator
 *  @param  value2 denominator
 *  @param MOD  module
 *
 *
 *  complexity O(log(n))
 *  @return returns result of division
 */
template <typename T>
T
modNum<T>::div(T value1, T value2, T mod) const {
    return value1 * inverseValue(value2, mod);
}

template <typename T>
T
modNum<T>::getValue() const {   // method to access private member value
    return value;
}
template <typename T>
void
modNum<T>::setMod(T MOD) {
    if (MOD <= 0) {
        throw std::invalid_argument("modulus should be positive");
    }
    this->MOD = MOD;
}

template <typename T>
modNum<T>
modNum<T>::inv() {
    return modNum<T>(inverseValue(value, MOD), MOD);
}
template <typename T>
modNum<T>
modNum<T>::operator+(const modNum<T> &other) const {
    return modNum<T>(add(value, other.value, MOD), MOD);
}
template <typename T>
modNum<T>
modNum<T>::operator-(const modNum<T> &other) const {
    return modNum<T>(subs(value, other.value, MOD), MOD);
}
template <typename T>
modNum<T>
modNum<T>::operator*(const modNum<T> &other) const {
    return modNum<T>(mult(value, other.value, MOD), MOD);
}

template <typename T>
modNum<T>
modNum<T>::operator/(const modNum<T> &other) const {
    return modNum<T>(div(value, other.value, MOD), MOD);
}

#endif   // TASK2_TCC
}   // namespace modular