#ifndef HUGEINT_H
#define HUGEINT_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class HugeInt {
    friend ostream & operator <<(ostream &out, const HugeInt &);
    friend istream & operator >>(istream &in, HugeInt &);
    public:
        HugeInt();
        HugeInt(const int &y);
        HugeInt(const string &z);
        const HugeInt & operator =(const HugeInt &right);
        HugeInt operator +(HugeInt &right);
        HugeInt operator -(HugeInt &right);
        vector<char> reverse;
};
#endif
