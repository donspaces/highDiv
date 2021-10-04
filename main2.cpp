//
// Created by donsp on 4/3/2021.
//
#include <iostream>
#include "LargeReal.h"
#include <complex>
#include <ctime>
#include <cmath>

using namespace std;

clock_t start_t, end_t;

LargeReal sumpi(int digits)
{
    LargeReal denom = fZero, n = fZero;
    LargeReal denom_nom, denom_denom;
    LargeReal temp = fOne;
    while(fabs(denom - temp) >= (fOne << digits))
    {
        temp = denom;
        denom_nom = factorial(LargeReal("6")*n)*(LargeReal("13591409")
                + LargeReal("545140134") * n);
        denom_denom = factorial(LargeReal("3") * n) * (factorial(n)^3)
                * (LargeReal("-640320")^(LargeReal("3") * n));

        denom += fdiv(denom_nom, denom_denom, digits);
        n ++;
    }

    return fdiv(LargeReal("426880") * fsqrt(LargeReal("10005"), digits), denom, digits);
}

LargeReal sumExp(int digits)
{
    LargeReal n = fOne, i = fOne;
    LargeReal temp = fZero;
    while(fabs(n - temp) >= (fOne << digits))
    {
        temp = n;
        n += fdiv(fOne, factorial(i), digits);
        i ++;
    }

    return n;
}


int main()
{
    LargeReal a("280.142"), b("2.56");
    LargeReal c("-14256370.06");
    (a+b).print();
    (b-a).print();
    (a*b).print();
    (-c).print();
    (c>>-1).print();
    cout<<"a>|c|:" << (a>fabs(c)) <<endl;
    (Int(c)-One).print();
    c.round(1).print();
    (a/b).print();
    LargeReal d("1"), e("191");
    fdiv(d, e, 100).print();
    ((e^(-2))%10).print();
    ((d/e*e).round(10)).print();

    //LargeReal m, n;
    //cin >> m >> n;
    //cout << "m*n = " << m * n << endl;
    e="361.23";
    cout << e << endl;
    cout << fdiv(d, e, 500) << endl;

    //cout << fsqrt(LargeReal("1") << 50, 1000) << endl;
    cout << "-----------------" << endl;

    complex<LargeReal> lcomp1(LargeReal("1"), LargeReal("0"));
    complex<LargeReal> lcomp2(LargeReal("12.6"), LargeReal("33.1"));

    cout << lcomp1 / lcomp2 << endl;
	
    cout << factorial(LargeReal("100")) << endl;

    cout << "pi(100 digits) =  " << PI << endl;
    start_t = clock();
    cout << "pi(1000 digits) = " << sumpi(1000) << endl;
    end_t = clock();
    cout << "total running time:" << (end_t - start_t) / CLOCKS_PER_SEC << " s" << endl;

    cout << "e(100 digits) =  " << Exp << endl;
    start_t = clock();
    cout << "e(1000 digits) = " << sumExp(1000) << endl;
    end_t = clock();
    cout << "total running time:" << (end_t - start_t) / CLOCKS_PER_SEC << " s" << endl;

    return 0;
}
