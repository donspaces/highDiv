//
// Created by donsp on 4/3/2021.
//

#ifndef HIGHDIV_LARGEREAL_H
#define HIGHDIV_LARGEREAL_H

#include "LargeInt.h"

class LargeReal : public LargeInt {
protected:
    int dot_p = 0;
    LargeReal(int l):LargeInt(l){}
    LargeReal(int l, int dp):dot_p(dp),LargeInt(l){}

public:
    LargeReal():dot_p(0),LargeInt(){}
    
    explicit LargeReal(string str)
    {
        int i, mode = 1;
        len = str.length();
        if(str[0] == '-') {
            minus = true;
        }
        for(i=0; i<len; i++)
        {
            if(str[len - i - mode] == '.') {
                dot_p = i;
                mode++;
            }
            value[i] = str[len - i - mode] - '0';
        }

        // base = 10;

        ~(*this);
    }

    explicit LargeReal(char* str)
    {
        int i, mode = 1;
        len = strlen(str);
        if(str[0] == '-') {
            minus = true;
        }
        for(i=0; i<len; i++)
        {
            if(str[len - i - mode] == '.') {
                dot_p = i;
                mode++;
            }
            value[i] = str[len - i - mode] - '0';
        }

        // base = 10;

        ~(*this);
    }

    explicit LargeReal(LargeInt const &a):LargeInt(a)
    {
        dot_p = 0;
    }

    LargeReal(LargeReal const &a):LargeInt(a)
    {
        dot_p = a.dot_p;
    }

    friend LargeReal operator+(LargeReal a, LargeReal b);
    friend LargeReal operator-(LargeReal a, LargeReal b);
    friend LargeReal operator*(LargeReal a, LargeReal b);
    friend LargeReal operator/(LargeReal a, LargeReal b);
    friend LargeReal operator^(LargeReal const &a, int d);
    LargeReal& operator=(LargeReal const &a);
    LargeReal& operator=(string const &a);
    LargeReal& operator=(char* const &a);
    friend bool operator<(LargeReal const &a, LargeReal const &b);
    friend bool operator==(LargeReal const &a, LargeReal const &b);
    friend bool operator!=(LargeReal const &a, LargeReal const &b);
    friend bool operator>(LargeReal const &a, LargeReal const &b);
    friend bool operator<=(LargeReal const &a, LargeReal const &b);
    friend bool operator>=(LargeReal const &a, LargeReal const &b);

    LargeReal operator>>(int d);
    LargeReal operator<<(int d);

    LargeReal operator-();

    LargeReal & operator++();
    LargeReal & operator--();

    LargeReal operator++(int);
    LargeReal operator--(int);

    LargeReal & operator+=(LargeReal const &a);
    LargeReal & operator-=(LargeReal const &a);
    LargeReal & operator*=(LargeReal const &a);
    LargeReal & operator/=(LargeReal const &a);
    LargeReal & operator^=(int &a);

    LargeReal & operator>>=(int d);
    LargeReal & operator<<=(int d);

    LargeReal & operator~() override; //reformat

    LargeReal operator%(int d);

    LargeReal & operator%=(int d);

    friend ostream& operator<<(ostream& os, LargeReal const &a);
    friend istream& operator>>(istream& is, LargeReal &a);

    friend void swap(LargeReal &a, LargeReal &b);


    LargeReal rm(int d); //right shift decimal
    LargeReal lm(int d); //left shift decimal

    friend void align(LargeReal &a, LargeReal &b);
    friend void norm(LargeReal &a, LargeReal &b);

    int countzero();
    int countzero_below_dotp();
    int int_digits();
    int deci_digits();

    //mathematics
    LargeReal frcd(int d);
    LargeReal flcd(int d);
    LargeReal Floor(int d);
    LargeReal Ceil(int d);
    LargeReal round(int d);
    friend LargeInt Int(LargeReal &a);
    friend LargeReal fabs(LargeReal const &a);
    friend LargeReal fdiv(LargeReal a, LargeReal b, int digits);

    friend LargeReal fadd(LargeReal a, LargeReal b);
    friend LargeReal fsubt(LargeReal a, LargeReal b);

    //output
    void print() override;
    string toString() const override;
    void toCharArray(char* a) const override;
    
};

extern LargeReal const fZero;
extern LargeReal const fOne;
extern LargeReal const PI;
extern LargeReal const Exp;
extern LargeReal const Hv;

#endif //HIGHDIV_LARGEREAL_H
