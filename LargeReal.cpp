//
// Created by donsp on 4/3/2021.
//

#include "LargeReal.h"
#include "LargeReal.h"
#include <iostream>

using namespace std;

LargeReal const fZero("0");
LargeReal const fOne("1");
LargeReal const PI("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679");
LargeReal const Exp("2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274");
LargeReal const Hv = LargeReal("6.626070040") << 34;

LargeReal LargeReal::rm(int d) {
    LargeReal x(len + d);
    if(d < 0)
        return lm(-d);
    else if(d == 0){
        return (*this);
    }
    else {
        x = LargeReal(LargeInt::rcd(d));
        x.dot_p = dot_p + d;
    }

    return x;
}

LargeReal LargeReal::lm(int d) {
    LargeReal x(len + d);
    if(d < 0)
        return rm(-d);
    else if(d == 0){
        return (*this);
    }
    else if(dot_p - d >= 0){
        x = LargeReal(LargeInt::lcd(d));
        x.dot_p = dot_p - d;
    }
    else{
        x = LargeReal(LargeInt::lcd(dot_p));
        dot_p = 0;
    }

    return x;
}

void LargeReal::print() {
    if(*this == Zero)
        cout<<0;
    else if(minus)
        cout<<"-";
    for(int j=len-1; j>=0; j--) {
        cout << (int) value[j];
        if(j==dot_p)cout<<".";
    }
    cout<<endl;
}

string LargeReal::toString() const
{
    string a;
    if(*this == Zero)
        a+="0";
    else if(minus)
        a+="-";
    for(int j=len-1; j>=0; j--) {
        a += (char) (value[j] + '0');
        if(j==dot_p)a+=".";
    }
    return a;
}

void LargeReal::toCharArray(char* a) const
{
    a = (char*) toString().c_str();
}

LargeReal &LargeReal::operator=(LargeReal const &a) {
    int length = (a.len > len) ? a.len : len;
    minus = a.minus;
    // base = a.base;
    resize(a.len);
    memcpy(value, a.value, length * sizeof(signed char));
    dot_p = a.dot_p;

    return (*this);
}

LargeReal &LargeReal::operator~() {
    while(value[len-1] < 0 && len > 0)
    {
        value[len - 1] = 0;
        len--;
    }
    while(value[len-1] == 0 && len > dot_p + 1)
    {
        len--;
    }
    if(dot_p >= len)
    {
        len += (dot_p - len + 1);
    }

    (*this) = lm(countzero_below_dotp());

    return (*this);
}

LargeReal operator+(LargeReal a, LargeReal b) {
    align(a, b);
    LargeInt c = a, d = b;
    LargeReal e = LargeReal(c + d);
    e.dot_p = a.dot_p;

    ~e;

    return e;

}

LargeReal operator-(LargeReal a, LargeReal b) {
    align(a, b);
    LargeInt c = a, d = b;
    LargeReal e = LargeReal(c - d);
    e.dot_p = a.dot_p;

    ~e;

    return e;
}

LargeReal operator*(LargeReal a, LargeReal b) {
    int deci = a.dot_p + b.dot_p;
    LargeInt c = a, d = b;
    LargeReal e = LargeReal(c * d);
    e.dot_p = deci;

    ~e;

    return e;
}

LargeReal operator/(LargeReal a, LargeReal b) {
    return fdiv(a, b, 20);
}

LargeReal LargeReal::operator%(int d) {
    LargeReal x;
    x = lm(dot_p - d);

    return x;
}

LargeReal &LargeReal::operator%=(int d) {
    (*this) = (*this) % d;

    return (*this);
}

void align(LargeReal &a, LargeReal &b) {
    if(a.dot_p > b.dot_p)
        b %= a.dot_p;
    if(b.dot_p > a.dot_p)
        a %= b.dot_p;
}

int LargeReal::countzero() {
    int i = 0;
    while(value[i++] == 0);

    return i - 1;
}

int LargeReal::countzero_below_dotp() {
    int i = 0;
    while(value[i++] == 0 && i<=dot_p);

    return i - 1;
}

LargeReal LargeReal::frcd(int d) {
    if(d < 0) {
        cerr << "cannot digit-shift with negative." << endl;
        exit(-1);
    }
    if(d == 0)
        return (*this);

    LargeReal x = (*this);
    if(dot_p > d)
        x.dot_p = dot_p - d;
    else{
        x = LargeReal(rcd(d - dot_p));
        x.dot_p = 0;
    }

    ~x;

    return x;
}

LargeReal LargeReal::flcd(int d) {
    if(d < 0) {
        cerr << "cannot digit-shift with negative." << endl;
        exit(-1);
    }
    if(d == 0)
        return (*this);

    LargeReal x = (*this);
    int count_zero_int = countzero() - countzero_below_dotp();
    if(count_zero_int > d)
        x = LargeReal(lcd(d));
    else{
        x = LargeReal(lcd(count_zero_int));
        x.dot_p = dot_p + (d - count_zero_int);
    }

    ~x;

    return x;
}

LargeReal LargeReal::operator>>(int d) {
    if(d < 0)
        return flcd(-d);

    return frcd(d);
}

LargeReal LargeReal::operator<<(int d) {
    if(d < 0)
        return frcd(-d);

    return flcd(d);
}

bool operator<(LargeReal const &a, LargeReal const &b){
    LargeReal x = a, y = b;
    align(x, y);

    return LargeInt(x) < LargeInt(y);
}

bool operator>(LargeReal const &a, LargeReal const &b){
    LargeReal x = a, y = b;
    align(x, y);

    return LargeInt(x) > LargeInt(y);
}

bool operator==(LargeReal const &a, LargeReal const &b){
    LargeReal x = a, y = b;
    align(x, y);

    return LargeInt(x) == LargeInt(y);
}

bool operator!=(LargeReal const &a, LargeReal const &b){
    return !(a == b);
}

bool operator<=(LargeReal const &a, LargeReal const &b){
    return !(a > b);
}

bool operator>=(LargeReal const &a, LargeReal const &b){
    return !(a < b);
}

LargeReal fabs(const LargeReal &a) {
    LargeReal x = a;
    x.minus = false;

    return x;
}

LargeReal LargeReal::Floor(int d) {
    return (*this) % d;
}

LargeReal LargeReal::Ceil(int d) {
    LargeReal x = (*this) % d;
    x += (LargeReal) fOne << d;

    return x;
}

LargeReal LargeReal::round(int d) {
    LargeReal x = (*this) % (d+1);
    if(x.value[0] <= 4)
        return Floor(d);

    return Ceil(d);
}

LargeInt Int(LargeReal &a) {
    return LargeInt(a % 0);
}



void norm(LargeReal &a, LargeReal &b) {
    int deci = (a.dot_p > b.dot_p) ? a.dot_p : b.dot_p;
    a >>= deci;
    b >>= deci;
}

LargeReal& LargeReal::operator++() {
    *this+=fOne;

    return *this;
}

LargeReal& LargeReal::operator--() {
    *this-=fOne;

    return *this;
}

LargeReal LargeReal::operator++(int) {
    LargeReal temp = *this;
    *this+=fOne;

    return temp;
}

LargeReal LargeReal::operator--(int) {
    LargeReal temp = *this;
    *this-=fOne;

    return temp;
}



LargeReal& LargeReal::operator+=(LargeReal const &a) {
    *this = *this + a;

    return *this;
}

LargeReal& LargeReal::operator-=(LargeReal const &a) {
    *this = *this - a;

    return *this;
}

LargeReal& LargeReal::operator*=(LargeReal const &a) {
    *this = *this * a;

    return *this;
}

LargeReal& LargeReal::operator/=(LargeReal const &a) {
    *this = *this / a;

    return *this;
}

LargeReal &LargeReal::operator^=(int &a) {
   // *this = *this ^ a;

    return *this;
}

LargeReal &LargeReal::operator>>=(int d) {
    *this = *this >> d;

    return *this;
}

LargeReal &LargeReal::operator<<=(int d) {
    *this = *this << d;

    return *this;
}

void swap(LargeReal &a, LargeReal &b) {
    LargeReal temp;
    temp = a;
    a = b;
    b = temp;
}

int LargeReal::int_digits() {
    return len - dot_p;
}

int LargeReal::deci_digits() {
    return dot_p;
}

LargeReal fadd(LargeReal a, LargeReal b) {
    align(a, b);
    LargeReal x;
    x = LargeReal(agg(a, b));
    x.dot_p = a.dot_p;

    return x;
}

LargeReal fsubt(LargeReal a, LargeReal b) {
    align(a, b);
    LargeReal x;
    x = LargeReal(subt(a, b));
    x.dot_p = a.dot_p;

    return x;
}

LargeReal fdiv(LargeReal a, LargeReal b, int digits) {
    norm(a, b);
    LargeInt c = a, d = b;
    LargeReal ans = LargeReal(c/d), rem = LargeReal(c|d);

    ans >>= digits;
    ans.dot_p += digits;
    int p = digits;

    while(p >= 0)
    {
        while(fabs(rem) >= fabs(b))
        {
            rem = fsubt(rem, b);
            ans.value[p] ++;
        }
        if(rem.int_digits() < b.int_digits()){
            p -= b.int_digits() - rem.int_digits();
            rem >>= b.int_digits() - rem.int_digits();
        }
        else if(fabs(rem) < fabs(b)){
            p -= 1;
            rem >>= 1;
        }
    }

    ~(ans);

    return ans;

}

LargeReal operator^(const LargeReal &a, int d) {
    LargeReal res = fOne;
    if(d > 0) {
        for (int i = 1; i <= d; i++) {
            res *= a;
        }
    }
    else{
        for (int i = -1; i >= d; i--) {
            res /= a;
        }
    }

    return res;
}

LargeReal &LargeReal::operator=(const string &a) {
    (*this) = LargeReal(a);

    return *this;
}

LargeReal &LargeReal::operator=(char *const &a) {
    (*this) = LargeReal(a);

    return *this;
}

ostream &operator<<(ostream &os, const LargeReal &a) {
    os << a.toString();

    return os;
}

istream &operator>>(istream &is, LargeReal &a) {
    string num;
    is >> num;
    a = LargeReal(num);

    return is;
}

LargeReal LargeReal::operator-() {
    LargeReal x = (*this);
    x.minus = !x.minus;

    return x;
}






