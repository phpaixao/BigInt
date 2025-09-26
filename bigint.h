#ifndef _BIGINT_H_
#define _BIGINT_H_
#include <string>
#include <cstdint>
#include <iostream>

class BigInt{
private:
    bool neg;
    int nDig;
    int8_t *d = nullptr;

    void correct();
    void increment();
    void decrement();
public:
    inline bool isNeg() const {return neg;}

    inline int size() const {return nDig;}

    BigInt();

    BigInt(const BigInt& Valor);

    BigInt& operator=(const BigInt& Valor);

    BigInt(BigInt&& Valor) noexcept;

    BigInt& operator=(BigInt&& Valor) noexcept;

    int operator[](int i) const;

    BigInt(long long int X);

    explicit BigInt(const std::string& Num);

    long long int toInt() const;

    BigInt& operator++();

    BigInt operator++(int);

    BigInt& operator--();

    BigInt operator--(int);

    BigInt operator<<(int N);

    BigInt operator>>(int N);

    bool operator==(const BigInt& B) const;

    bool operator!=(const BigInt& B) const;

    bool operator<(const BigInt& B) const;

    bool operator<=(const BigInt& B) const;

    bool operator>(const BigInt& B) const;

    bool operator>=(const BigInt& B) const;

    BigInt operator-() const;

    BigInt operator+(const BigInt& B) const;

    BigInt operator-(const BigInt& B) const;

    BigInt operator*(const BigInt& B) const;

    friend std::ostream& operator<<(std::ostream& X,const BigInt& B);

    friend std::istream& operator>>(std::istream& I, BigInt& B);

    friend BigInt abs(BigInt X);

    bool isZero() const;

    void division(const BigInt& D, BigInt& Q, BigInt& R) const;

    BigInt operator/(const BigInt& D) const;

    BigInt operator%(const BigInt& D) const;

    BigInt operator!() const;

    void clear();

    ~BigInt() {clear();}
};

#endif // _BIGINT_H_
