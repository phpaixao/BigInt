#include <iostream>
#include "bigint.h"
#include <cmath>
#include <string>
using namespace std;

BigInt::BigInt():
    neg(false), nDig(1), d(nullptr){
    d = new int8_t[nDig];
    d[0] = 0;
}

BigInt::BigInt(const BigInt& Valor):
    neg(Valor.neg), nDig(Valor.nDig), d(nullptr){
    if (nDig > 0){
        this->d = new int8_t[this->nDig];
        for (int i=0; i<this->nDig; i++){
            this->d[i] = Valor.d[i];
        }
    }
}

BigInt& BigInt::operator=(const BigInt& Valor){
    if (this != &Valor){
        delete[] this->d;
        this->nDig = Valor.nDig;
        this->neg = Valor.neg;
        if (this->nDig > 0){
            this->d = new int8_t[this->nDig];
            for (int i=0; i<this->nDig; i++){
                this->d[i] = Valor.d[i];
            }
        }
    }
    return *this;
}

BigInt::BigInt(BigInt&& Valor) noexcept :
    neg(Valor.neg), nDig(Valor.nDig), d(Valor.d) {
    Valor.nDig = 0;
    Valor.neg = false;
    Valor.d = nullptr;
}

BigInt& BigInt::operator=(BigInt&& Valor) noexcept {
    delete[] this->d;
    this->nDig = Valor.nDig;
    this->neg = Valor.neg;
    this->d = Valor.d;
    Valor.nDig = 0;
    Valor.neg = false;
    Valor.d = nullptr;
    return *this;
}

BigInt::BigInt(long long int X):BigInt() {
    if (X == 0){
        return;
    }
    this->neg = (X<0);
    this->nDig = 1 + int(log10(abs(double(X))));
    delete[] this->d;
    this->d = new int8_t[this->nDig];
    for (int i=0; i<this->nDig; i++){
        this->d[i] = abs(X%10);
        X /= 10;
    }
}

BigInt::BigInt(const string& Num):BigInt() {
    int ini = 0;
    char C;
    if (Num.size() == 0){
        cerr << "Erro!" << endl;
        return;
    }
    this->neg = false;
    if (Num[0] == '+' || Num[0] == '-'){
        if (Num.size() == 1){
            cerr << "Erro!" << endl;
            return;
        }
        ini = 1;
        if (Num[0] == '-'){neg = true;}
    }
    this->nDig = Num.size() - ini;
    delete[] this->d;
    this->d = new int8_t[this->nDig];
    for (int i=0; i<nDig; i++){
        C = Num[Num.size()-1-i];
        if (!isdigit(C)){
            cerr << "Erro! caractere invalido" << endl;
            return;
        }
        this->d[i] = (int8_t)(C-'0');
    }
}

int BigInt::operator[](int i) const {
    if (i > (this->nDig - 1) || i < 0){
        return 0;
    }
    return (int)this->d[i];
}

long long int BigInt::toInt() const {
    long long int C = 0;
    for (int i=(this->nDig-1); i >= 0; i--){
        C *= 10;
        C += d[i];
        if (C < 0){
            cerr << "Erro" << endl;
            C = 0;
            return 0;
        }
    }
    if (this->neg) C = -C;
    return C;
}

void BigInt::correct(){
    if (this->nDig <= 0 || this->d == nullptr){
        *this = BigInt();
        return;
    }

    int newNDig = this->nDig;
    int8_t* newD = nullptr;

    while (newNDig > 1 && this->d[newNDig - 1] == 0){
        newNDig -= 1;
    }
    if (newNDig != this->nDig){
        newD = new int8_t[newNDig];
        for (int i=0; i<newNDig; i++){
            newD[i] = this->d[i];
        }
        delete[] this->d;
        this->nDig = newNDig;
        this->d = newD;
    }
    if (this->nDig == 1 && this->d[0] == 0) this->neg = false;
}

ostream& operator<<(ostream& X,const BigInt& B){
    if (B.neg) X << "-";
    for (int i=B.nDig - 1; i>=0; i--){
        X << B[i];
    }
    return X;
}

istream& operator>>(istream& I, BigInt& B){
    int C;
    B.clear();
    B.neg = false;
    I >> ws;

    do{
        C = I.peek();
        if (isdigit(C) || (B.nDig == 0 && (C == '-' || C == '+'))){
            C = I.get();
            if (C == '-') B.neg = true;
            if (isdigit(C)){
                int8_t* newD = new int8_t[B.nDig + 1];
                for (int i=0; i<B.nDig; i++){
                    newD[i+1] = B.d[i];
                }
                newD[0] = (int8_t)(C-'0');
                delete[] B.d;
                B.d = newD;
                B.nDig++;
            }
        }
    } while(isdigit(C) || (B.nDig == 0 && (C == '-' || C == '+')));
    B.correct();
    return I;
}

void BigInt::increment(){
    int k = 0;
    this->d[k] += 1;
    while (k < this->nDig-1 && this->d[k] > 9){
        this->d[k] = 0;
        k += 1;
        this->d[k] += 1;
    }
    if (k == this->nDig-1 && this->d[k] > 9){
        int8_t* newD = new int8_t[this->nDig+1];
        for (int i=0; i<this->nDig-1; i++){
            newD[i] = this->d[i];
        }
        newD[this->nDig-1] = 0;
        newD[this->nDig] = 1;
        delete[] this->d;
        this->d = newD;
        this->nDig += 1;
    }
}

void BigInt::decrement(){
    int k = 0;
    this->d[k] -= 1;
    while (k < this->nDig-1 && this->d[k] < 0){
        this->d[k] = 9;
        k += 1;
        this->d[k] -= 1;
    }
    if (k == this->nDig-1 && this->d[k] <= 0){
        if (this->nDig > 1){
            int8_t* newD = new int8_t[this->nDig-1];
            for (int i=0; i<this->nDig-1; i++){
                newD[i] = this->d[i];
            }
            delete[] this->d;
            this->d = newD;
            this->nDig -= 1;
        } else {
            if (this->neg) this->neg = false;
            else if(this->d[0] < 0){
                this->d[0] *= -1;
                this->neg = true;
            }
        }
    }
}

BigInt& BigInt::operator++(){
    if (!(this->neg)) this -> increment();
    else this -> decrement();
    return *this;
}

BigInt BigInt::operator++(int){
    BigInt X = *this;
    ++(*this);
    return X;
}

BigInt& BigInt::operator--(){
    if (this->neg) this -> increment();
    else this -> decrement();
    return *this;
}

BigInt BigInt::operator--(int){
    BigInt X = *this;
    --(*this);
    return X;
}

BigInt BigInt::operator<<(int N){
    if (N <= 0 || this->isZero()) return *this;
    BigInt C;
    C.neg = this->neg;
    C.nDig = this->nDig + N;
    delete[] C.d;
    C.d = new int8_t[C.nDig];
    for (int i=0; i<C.nDig; i++){
        if (i<N) C.d[i] = 0;
        else C.d[i] = this->d[i-N];
    }
    return C;
}

BigInt BigInt::operator>>(int N){
    if (N <= 0 || this->isZero()) return *this;
    if (N >= this->nDig) return 0;
    BigInt C;
    C.neg = this->neg;
    C.nDig = this->nDig - N;
    delete[] C.d;
    C.d = new int8_t[C.nDig];
    for (int i=0; i<C.nDig; i++){
        C.d[i] = this->d[i+N];
    }
    return C;
}

bool BigInt::operator==(const BigInt& B) const{
    if (this->nDig != B.nDig || this->neg != B.neg || this->isZero() != B.isZero()) return false;
    for (int i=0; i<this->nDig; i++){
        if (this->d[i] != B.d[i]) return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt& B) const{
    return !(*this == B);
}

bool BigInt::operator<(const BigInt& B) const{
    BigInt A = *this;
    if (this->neg && !B.neg) return true;
    if (!this->neg && B.neg) return false;
    if (this->neg && B.neg) return (abs(B) < abs(*this));
    if (this->nDig < B.nDig) return true;
    if (this->nDig > B.nDig) return false;
    for (int i=this->nDig-1; i>=0; i--){
        if (this->d[i] < B.d[i]) return true;
        if (this->d[i] > B.d[i]) return false;
    }
    return false;
}

bool BigInt::operator<=(const BigInt& B) const{
    return (*this < B || *this == B);
}

bool BigInt::operator>(const BigInt& B) const{
    return (B<*this);
}

bool BigInt::operator>=(const BigInt& B) const{
    return !(*this<B);
}

BigInt BigInt::operator-() const{
    BigInt A = *this;
    if (A.isZero()){
        A.neg = false;
        return A;
    }
    A.neg = !A.neg;
    return A;
}

BigInt BigInt::operator+(const BigInt& B) const{
    BigInt C;
    int carry = 0;
    if (!(this->neg) && !B.neg){
        C.nDig = 1 + max(this->nDig, B.nDig);
        delete[] C.d;
        C.d = new int8_t[C.nDig];
        carry = 0;
        for (int i=0; i<C.nDig; i++){
            C.d[i] = (*this)[i] + B[i] + carry;
            if (C.d[i] > 9){
                C.d[i] = C.d[i] - 10;
                carry = 1;
            } else {
                carry = 0;
            }
        }
        C.correct();
    } else if (this->neg && B.neg){
        C = -(abs(*this)+abs(B));
    } else if (!neg && B.neg){
        if (abs(*this) >= abs(B)){
            delete[] C.d;
            C.nDig = this->nDig;
            C.d = new int8_t[C.nDig];
            carry = 0;
            for (int i=0; i<C.nDig; i++){
                C.d[i] = (*this)[i] - B[i] - carry;
                if (C.d[i] < 0){
                    C.d[i] += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
            }
            C.correct();
        } else {
            C = -(abs(B) + (-(*this)));
        }
    } else {
        if (abs(*this) >= abs(B)) C = -(abs(*this) + (-B));
        else C = B + *this;
    }
    return C;
}

BigInt BigInt::operator-(const BigInt& B) const{
    BigInt C = *this + (-B);
    return C;
}

BigInt BigInt::operator*(const BigInt& B) const{
    if (this->isZero() || B.isZero()) return 0;
    int k = 0, carry = 0;
    BigInt C;
    C.neg = (this->neg != B.neg);
    C.nDig = this->nDig + B.nDig;
    delete[] C.d;
    C.d = new int8_t[C.nDig]{0};
    for (int i=0; i<this->nDig; i++){
        for (int j=0; j<B.nDig; j++){
            k = i + j;
            C.d[k] += this->d[i] * B.d[j];
            while (C.d[k] > 9){
                carry = (C.d[k]/10);
                C.d[k] = (C.d[k]%10);
                k += 1;
                C.d[k] += carry;
            }
        }
    }
    C.correct();
    return C;
}

BigInt abs(BigInt X){
    if (!X.neg) return X;
    X.neg = false;
    return X;
}

bool BigInt::isZero() const{
    return (this->nDig == 1 && this->d[0] == 0);
}

void BigInt::division(const BigInt& D, BigInt& Q, BigInt& R) const{
    if (this->isZero() || D.isZero()){
        if (D.isZero()) cerr << "Erro de divisao por zero. ";
        Q = 0;
        R = 0;
        return;
    }
    if (abs(*this) < abs(D)){
        Q = 0;
        R = *this;
        return;
    }
    Q = 0;
    int nComp = D.nDig;
    R = (abs(*this) >> (this->nDig - nComp));
    if (R < abs(D)){
        nComp += 1;
        R = (abs(*this) >> (this->nDig - nComp));
    }
    int div = 0;
    while (R >= abs(D)){
        R = R - abs(D);
        div += 1;
    }
    Q.d[0] = div;
    while (nComp < this->nDig){
        nComp += 1;
        R = R << 1;
        R.d[0] = this->d[this->nDig - nComp];
        div = 0;
        while (R >= abs(D)){
            R = R - abs(D);
            div += 1;
        }
        Q = Q<<1;
        Q.d[0] = div;
    }
    Q.neg = (this->neg != D.neg);
    if (!(R.isZero())) R.neg = this->neg;
    //Q.correct();
    //R.correct();
}

BigInt BigInt::operator/(const BigInt& D) const{
    BigInt Q, R;
    division(D, Q, R);
    //Q.correct();
    return Q;
}

BigInt BigInt::operator%(const BigInt& D) const{
    BigInt Q, R;
    division(D, Q, R);
    return R;
}

BigInt BigInt::operator!() const{
    BigInt N = *this;
    if (this->neg){
        cerr << "Impossivel calcular fatorial de negativos: ";
        return 0;
    }
    if (this->isZero() || *this == 1) return 1;
    return N * !(N-1);
}

void BigInt::clear(){
    delete[] d;
    nDig = 0;
    d = nullptr;
    //cout << "Destrutor foi chamado" << endl;
}
