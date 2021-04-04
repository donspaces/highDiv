//
// Created by donsp on 4/1/2021.
//

#include "LargeInt.h"
#include <iostream>
#include <cstring>

LargeInt const Zero("0");
LargeInt const One("1");

void LargeInt::resize(int size)
{
    len = size;
}

LargeInt& LargeInt::operator=(LargeInt const &a)
{
    int length = (a.len > len) ? a.len : len;
    minus = a.minus;
    base = a.base;
    resize(a.len);
    memcpy(value, a.value, length * sizeof(signed char));
    return *this;
}

LargeInt operator+(LargeInt const &a, LargeInt const &b)
{
    bool sign = a.minus ^ b.minus;
    if(sign)
        return subt(a, b); //5 + (-7) = (-2) (-3) + 1 = (-2)
    else
        return agg(a, b); //5 + 7 = 12 (-3) + (-1) = (-4)
}

LargeInt operator-(LargeInt const &a, LargeInt const &b)
{
    bool sign = a.minus ^ b.minus;
    if(sign)
        return agg(a, b); //5 - (-7) = 12 (-3) - 1 = (-4)
    else
        return subt(a, b); //5 - 7 = (-2) (-5) - (-7) = 2
}

LargeInt operator*(LargeInt const &a, LargeInt const &b)
{
    bool sign = a.minus ^ b.minus;
    int length = a.len + b.len;
    LargeInt c(length + 1);
    short *buf =(short*) calloc(length * 2 + 1, sizeof(short));
    c.minus = sign;

    for(int i=0; i<length; i++)
    {
        for(int j=0; j<length; j++)
        {
            buf[i + j] += a.value[j] * b.value[i];
        }
    }
    for(int i=0; i<length + 1; i++)
    {
        buf[i+1] += buf[i] / 10;
        buf[i] %= 10;
        c.value[i] = buf[i];
    }

    ~c;
    free(buf);

    return c;
}

LargeInt operator/(LargeInt a, LargeInt b)
{
    if(b == Zero)
    {
        cerr<<"divisor can't be zero."<<endl;
        exit(-1);
    }

    bool sign = a.minus ^ b.minus;
    int pt = a.len-b.len;
    b >>= (a.len-b.len);
    LargeInt c(b.len);
    c.minus = sign;

    while(pt >= 0)
    {
        while(labs(a) >= labs(b))
        {
            a = subt(a, b);
            c.value[pt] += 1;
        }
        if(a.len < b.len)
        {
            pt -= (b.len-a.len);
            b <<= (b.len-a.len);
        }
        if(labs(a) < labs(b))
        {
            pt--;
            b<<=1;
        }
    }

    ~c;

    return c;
}

LargeInt operator|(LargeInt a, LargeInt b)
{
    if(b == Zero)
    {
        cerr<<"divisor can't be zero."<<endl;
        exit(-1);
    }

    int pt = a.len-b.len;
    b >>= (a.len-b.len);

    while(pt >= 0)
    {
        while(labs(a) >= labs(b))
        {
            a = subt(a, b);
        }
        if(a.len < b.len)
        {
            pt -= (b.len-a.len);
            b <<= (b.len-a.len);
        }
        if(labs(a) < labs(b))
        {
            pt--;
            b<<=1;
        }
    }

    ~a;
    return a;
}

bool operator<(LargeInt const &a, LargeInt const &b)
{
    //positivity
    if(a.minus != b.minus)
        return a.minus > b.minus;
    //negative comp
    if(a.minus && b.minus)
        return labs(a) > labs(b);
    //unequal length
    if(a.len != b.len)
        return a.len < b.len;
    else
        //bits comp
        for(int i=a.len-1; i>=0; i--)
        {
            if(a.value[i] < b.value[i]) return true;
            if(a.value[i] > b.value[i]) return false;
        }
    return false;
}

bool operator==(LargeInt const &a, LargeInt const &b)
{
    if(a.len == 0 && b.len == 0)
        return true;
    else if(a.minus != b.minus)
        return false;
    if(a.len != b.len)
        return false;
    else
        for(int i=a.len-1; i>=0; i--)
        {
            if(a.value[i] != b.value[i]) return false;
        }
    return true;
}

bool operator!=(LargeInt const &a, LargeInt const &b)
{
    return !(a==b);
}

bool operator>(LargeInt const &a, LargeInt const &b)
{
    //positivity
    if(a.minus != b.minus)
        return a.minus < b.minus;
    //negative comp
    if(a.minus && b.minus)
        return labs(a) < labs(b);
    //unequal length
    if(a.len != b.len)
        return a.len > b.len;
    else
        //bits comp
        for(int i=a.len-1; i>=0; i--)
        {
            if(a.value[i] > b.value[i]) return true;
            if(a.value[i] < b.value[i]) return false;
        }
    return false;
}

bool operator<=(LargeInt const &a, LargeInt const &b)
{
    return !(a>b);
}

bool operator>=(LargeInt const &a, LargeInt const &b)
{
    return !(a<b);
}

LargeInt LargeInt::operator>>(int d)
{
    if(d<0)
        return lcd(-d);
    return rcd(d);
}

LargeInt LargeInt::operator<<(int d)
{
    if(d<0)
        return rcd(-d);
    return lcd(d);
}

LargeInt LargeInt::operator-() {
    LargeInt c = *this;
    c.minus = !c.minus;

    return c;
}

LargeInt operator^(LargeInt const &a, int b)
{
    LargeInt x = One;
    int i;
    for(i=1; i<=b; i++)
    {
        x = x * a;
    }

    return x;
}

void LargeInt::print()
{
    if(*this == Zero)
        cout<<0;
    else if(minus)
        cout<<"-";
    for(int j=len-1; j>=0; j--) {
        cout << (int) value[j];
    }

    cout << endl;
}

void swap(LargeInt &a, LargeInt &b)
{
    LargeInt temp;
    temp = a;
    a = b;
    b = temp;
}

string LargeInt::toString()
{
    string a;
    if(*this == Zero)
        a+="0";
    else if(minus)
        a+="-";
    for(int j=len-1; j>=0; j--) {
        a += (char) (value[j] + '0');
    }
    return a;
}

void LargeInt::toCharArray(char* a)
{
    a = (char*) toString().c_str();
}

LargeInt& LargeInt::operator++() {
    *this+=One;

    return *this;
}

LargeInt& LargeInt::operator--() {
    *this-=One;

    return *this;
}

LargeInt LargeInt::operator++(int) {
    LargeInt temp = *this;
    *this+=One;

    return temp;
}

LargeInt LargeInt::operator--(int) {
    LargeInt temp = *this;
    *this-=One;

    return temp;
}



LargeInt& LargeInt::operator+=(LargeInt const &a) {
    *this = *this + a;

    return *this;
}

LargeInt& LargeInt::operator-=(LargeInt const &a) {
    *this = *this - a;

    return *this;
}

LargeInt& LargeInt::operator*=(LargeInt const &a) {
    *this = *this * a;

    return *this;
}

LargeInt& LargeInt::operator/=(LargeInt const &a) {
    *this = *this / a;

    return *this;
}

LargeInt &LargeInt::operator|=(const LargeInt &a) {
    *this = *this | a;

    return *this;
}

LargeInt &LargeInt::operator^=(int &a) {
    *this = *this ^ a;

    return *this;
}

LargeInt &LargeInt::operator>>=(int d) {
    *this = *this >> d;

    return *this;
}

LargeInt &LargeInt::operator<<=(int d) {
    *this = *this << d;

    return *this;
}

LargeInt& LargeInt::operator~()
{
    while(value[len-1] <= 0 && len > 0)
    {
        value[len - 1] = 0;
        len--;
    }

    return *this;
}

int LargeInt::length() const {
    return len;
}

LargeInt LargeInt::rcd(int d) {
    if(d<0) {
        cerr << "cannot bitshift with negative." << endl;
        exit(-1);
    }
    if(d==0)
    {
        return (*this);
    }
    LargeInt x(len + d);
    x.minus = minus;
    int i;
    for(i=len+d-1; i>=d; i--)
    {
        x.value[i] = value[i-d];
    }

    return x;
}

LargeInt LargeInt::lcd(int d) {
    if(d<0) {
        cerr << "cannot bitshift with negative." << endl;
        exit(-1);
    }
    if(d==0)
    {
        return (*this);
    }
    if(d>len)
        return Zero;
    LargeInt x(len - d);
    x.minus = minus;
    int i;
    for(i=len-d-1; i>=0; i--)
    {
        x.value[i] = value[i+d];
    }

    return x;
}

bool LargeInt::negate() {
    minus = !minus;

    return minus;
}

LargeInt agg(LargeInt const &a, LargeInt const &b) {
    int length = (a.len > b.len) ? a.len : b.len;
    LargeInt c(length + 1);
    c.minus = a.minus;

    for(int i=0; i<length + 1; i++)
    {
        c.value[i] += a.value[i] + b.value[i];
        c.value[i + 1] += c.value[i] / 10;
        c.value[i] = c.value[i] % 10;
    }

    ~c;

    return c;
}

LargeInt subt(LargeInt a, LargeInt b) {
    int length = (a.len > b.len) ? a.len : b.len;
    LargeInt c(length);
    bool spec = false;
    c.minus = a.minus;

    if(labs(a) < labs(b))
    {
        c.minus = !a.minus;
        swap(a, b);
        spec = true;
    }

    for(int i=0; i<length; i++)
    {
        c.value[i] += a.value[i] - b.value[i];
        if(c.value[i-1] < 0 && i != 0)
        {
            c.value[i]--;
            c.value[i-1] += 10;
        }
    }

    ~c;

    return c;
}

LargeInt labs(LargeInt const &a)
{
    LargeInt c = a;
    c.minus = false;

    return c;
}

LargeInt &LargeInt::operator=(const string &a) {
    (*this) = LargeInt(a);

    return *this;
}

LargeInt &LargeInt::operator=(char *const &a) {
    (*this) = LargeInt(a);

    return *this;
}






