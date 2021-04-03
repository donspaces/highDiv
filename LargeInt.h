//
// Created by donsp on 4/1/2021.
//

#ifndef HIGHDIV_LARGEINT_H
#define HIGHDIV_LARGEINT_H

#include <iostream>
#include <cstring>

using namespace std;



class LargeInt {
private:
    bool minus = false;
    signed char value[10001]={0};
    int len=0;
    void resize(int size);
    LargeInt(int l):len(l){}

public:
    //member methods
    LargeInt():len(0){};

    LargeInt(string str)
    {
        int i;
        len = str.length();
        if(str[0]=='-') {
            len--;
            minus = true;
            for (i = 0; i < len; i++)
                value[i] = str[len - i] - '0';
        }
        else {
            for (i = 0; i < len; i++)
                value[i] = str[len - i - 1] - '0';
        }
        ~(*this);
    }

    LargeInt(char* str)
    {
        int i;
        len = strlen(str);
        if(str[0]=='-') {
            len--;
            minus = true;
            for (i = 0; i < len; i++)
                value[i] = str[len - i] - '0';
        }
        else {
            for (i = 0; i < len; i++)
                value[i] = str[len - i - 1] - '0';
        }
        ~(*this);
    }

    LargeInt(LargeInt const &a)
    {
        int length = (a.len > len) ? a.len : len;
        minus = a.minus;
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
    friend bool operator<(LargeInt const &a, LargeInt const &b);
    friend bool operator==(LargeInt const &a, LargeInt const &b);
    friend bool operator!=(LargeInt const &a, LargeInt const &b);
    friend bool operator>(LargeInt const &a, LargeInt const &b);
    friend bool operator<=(LargeInt const &a, LargeInt const &b);
    friend bool operator>=(LargeInt const &a, LargeInt const &b);

    LargeInt operator>>(int d);
    LargeInt operator<<(int d);

    LargeInt operator-();

    LargeInt& operator~(); //reformat

    friend LargeInt operator^(LargeInt const &a, int b); //power

    LargeInt & operator++();
    LargeInt & operator--();

    LargeInt operator++(int);
    LargeInt operator--(int);

    LargeInt & operator+=(LargeInt const &a);
    LargeInt & operator-=(LargeInt const &a);
    LargeInt & operator*=(LargeInt const &a);
    LargeInt & operator/=(LargeInt const &a);

    LargeInt & operator>>=(int d);
    LargeInt & operator<<=(int d);

    friend void swap(LargeInt &a, LargeInt &b);

    //mathematics
    LargeInt rcd(int d);
    LargeInt lcd(int d);
    friend LargeInt agg(LargeInt const &a, LargeInt const &b);
    friend LargeInt subt(LargeInt a, LargeInt b);
    friend LargeInt labs(LargeInt const &a);

    //output
    void print();
    string toString();
    void toCharArray(char* a);
    int length() const;
    bool negate();
};

extern LargeInt const Zero;
extern LargeInt const One;


#endif //HIGHDIV_LARGEINT_H
