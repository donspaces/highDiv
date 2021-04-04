//
// Created by donsp on 4/3/2021.
//
#include <iostream>
#include "LargeInt.h"
#include "LargeReal.h"

using namespace std;

LargeReal fsqrt(LargeReal const &n, int digits)
{
    LargeReal x("2"), temp;
    while(fabs(temp - x) >= ((LargeReal) fOne << digits)) {
        temp = x;
        x = fdiv(x + fdiv(n, x, digits), LargeReal("2"), digits);
    }

    return x;
}
int main()
{
    LargeReal a("280.142"), b("2.56");
    LargeReal c("-14256370.06");
    (a+b).print();
    (b-a).print();
    (a*b).print();
    c.print();
    (c>>-1).print();
    cout<<"a>c:" << (a>fabs(c)) <<endl;
    (Int(c)-One).print();
    c.round(1).print();
    (a/b).print();
    LargeReal d("1"), e("191");
    fdiv(d, e, 100).print();
    ((e^(-2))%10).print();
    ((d/e*e).round(10)).print();
    e="361.23";
    e.print();
    fdiv(d, e, 500).print();

    fsqrt(LargeReal("2"), 1000).print();

    return 0;
}
