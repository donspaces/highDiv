#include <iostream>
#include "LargeInt.h"
using namespace std;

int main() {
    LargeInt a("24720"), b("24"), c("13145026897624");
    LargeInt d;
    //swap(a, b);
    d = a - b + c;
    d.print();
    cout<<d.length()<<endl;
    cout<<(a>b)<<endl;
    (a>>100).print();
    (b>>(-1)).print();
    (a^100).print();
    cout<<(a<=b)<<endl;

    a/=b;
    a.print();
    (a++).print();
    (++a).print();

    LargeInt e("127"),f("35");
    (-e).print();
    (e+f).print();
    (-f).print();

    (e*f).print();
    cout<<"e/f = ";
    (e/f).print();
    cout<<"e|f = ";
    (e|f).print();

    cout<<(LargeInt("0") == Zero)<<endl;
    cout<<(LargeInt("-0") == Zero)<<endl;

    LargeInt sum = LargeInt("-100") + LargeInt("1");
    sum.print();

    char arr[10001];
    (e|f).toCharArray(arr);
    cout<<arr<<endl;

    LargeInt fac = factorial(LargeInt("1000"));
    fac.print();

    (fac|Zero).print();

    return 0;
}
