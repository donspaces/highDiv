//
// Created by donsp on 4/1/2021.
//

#ifndef HIGHDIV_LARGEINT_H
#define HIGHDIV_LARGEINT_H

#include <iostream>
#include <cstring>

using namespace std;



class LargeInt {
protected:
    bool minus = false;
    signed char value[10001]={0};
    int len=0;
    // int base=10;
    void resize(int size);
    LargeInt(int l):len(l){}

public:
    //member methods
    LargeInt():len(0){};

    explicit LargeInt(string str)
    {
        int i;
        len = str.length();
        if(str[0]=='-')
            minus = true;

        for (i = 0; i < len; i++)
            value[i] = str[len - i - 1] - '0';

        // base = 10;

        ~(*this);
    }

    explicit LargeInt(char* str)
    {
        int i;
        len = strlen(str);
        if(str[0]=='-')
            minus = true;

        for (i = 0; i < len; i++)
            value[i] = str[len - i - 1] - '0';

        // base = 10;

        ~(*this);
    }

    LargeInt(LargeInt const &a)
    {
        int length = (a.len > len) ? a.len : len;
        minus = a.minus;
        // base = a.base;
        resize(a.len);
        memcpy(value, a.value, length * sizeof(signed char));
    }

    //operator functions
    friend LargeInt operator+(LargeInt const &a, LargeInt const &b);
    friend LargeInt operator-(LargeInt const &a, LargeInt const &b);
    friend LargeInt operator*(LargeInt const &a, LargeInt const &b);
    friend LargeInt operator/(LargeInt a, LargeInt b);
    friend LargeInt operator|(LargeInt a, LargeInt b); //mod
    LargeInt& operator=(LargeInt const &a);
    LargeInt& operator=(string const &a);
    LargeInt& operator=(char* const &a);
    friend bool operator<(LargeInt const &a, LargeInt const &b);
    friend bool operator==(LargeInt const &a, LargeInt const &b);
    friend bool operator!=(LargeInt const &a, LargeInt const &b);
    friend bool operator>(LargeInt const &a, LargeInt const &b);
    friend bool operator<=(LargeInt const &a, LargeInt const &b);
    friend bool operator>=(LargeInt const &a, LargeInt const &b);

    LargeInt operator>>(int d);

    LargeInt operator<<(int d);

    LargeInt operator-();

    virtual LargeInt& operator~(); //reformat

    friend LargeInt operator^(LargeInt const &a, int b); //power

    LargeInt & operator++();
    LargeInt & operator--();

    LargeInt operator++(int);
    LargeInt operator--(int);

    LargeInt & operator+=(LargeInt const &a);
    LargeInt & operator-=(LargeInt const &a);
    LargeInt & operator*=(LargeInt const &a);
    LargeInt & operator/=(LargeInt const &a);
    LargeInt & operator|=(LargeInt const &a);
    LargeInt & operator^=(int &a);

    LargeInt & operator>>=(int d);
    LargeInt & operator<<=(int d);

    friend ostream& operator<<(ostream& os, LargeInt const &a);
    friend istream& operator>>(istream& is, LargeInt &a);

    friend void swap(LargeInt &a, LargeInt &b);

    //mathematics
    LargeInt rcd(int d);
    LargeInt lcd(int d);
    friend LargeInt agg(LargeInt const &a, LargeInt const &b);
    friend LargeInt subt(LargeInt a, LargeInt b);
    friend LargeInt labs(LargeInt const &a);

    virtual //output
    void print();

    virtual string toString() const;

    virtual void toCharArray(char* a) const;
    int length() const;
    bool negate();
};

extern LargeInt const Zero;
extern LargeInt const One;


#endif //HIGHDIV_LARGEINT_H
