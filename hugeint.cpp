#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "hugeint.h"
HugeInt::HugeInt() {//ok
}
HugeInt::HugeInt(const int &y) {//ok
    int temp = y;
    int a;
    while(temp != 0) {
        a = temp % 10;
        reverse.push_back(a+'0');
        temp /= 10;
        if(temp == 0)
            break;
    }
}
HugeInt::HugeInt(const string &z) {//ok
    int length = z.size();
    for(int i = 0; i < length; ++i)
        reverse.push_back(z.at(length-1-i));
}
istream & operator >>(istream &in, HugeInt &a) {//ok
    int i = 0;
    string temp;
    in >> temp;
    int length = temp.size();
    for(int i = 0; i < length; ++i)
        a.reverse.push_back(temp.at(length-1-i));
    return in;
}
ostream & operator <<(ostream &out, const HugeInt &a) {//ok
    int begin;
    for(int i = a.reverse.size()-1; i >= 0; --i) {
        if(a.reverse.at(i) == '0')
            continue;
        else if(a.reverse.at(i) != '0') {
            begin = i;
            break;
        }
    }
    for(int i = begin; i >= 0; --i)
        out << a.reverse.at(i);
    return out;
}
const HugeInt & HugeInt::operator =(const HugeInt &right) {//ok
    reverse = right.reverse;
    return *this;
}
HugeInt HugeInt::operator +(HugeInt &right) {//ok
    int length;
    if(right.reverse.size() > reverse.size()) {
        length = right.reverse.size();
        for(int temp = reverse.size(); temp < length; ++temp) {
            reverse.push_back('0');
        }
    }
    else {
        length = reverse.size();
        for(int temp = right.reverse.size(); temp < length; ++temp) {
            right.reverse.push_back('0');
        }
    }

    vector<int> temp_reverse(length+1);
    vector<int> this_int(length);
    vector<int> right_int(length);
    
    for(int i = 0; i < length; ++i) {
        this_int.at(i) = (reverse.at(i)-'0');
        right_int.at(i) = (right.reverse.at(i)-'0');
    }
    for(int i = 0; i < length; ++i) {
        temp_reverse.at(i) += right_int.at(i) + this_int.at(i);
        if(temp_reverse.at(i) >= 10) {
            ++temp_reverse.at(i+1);
            temp_reverse.at(i) -= 10;
        }
    }
    
    int temp_length;
    if(temp_reverse.at(length) == 1)
        temp_length = length+1;
    else if(temp_reverse.at(length) == 0)
        temp_length = length;
    vector<char> result_reverse(temp_length);
    
    for(int i = 0; i < result_reverse.size(); ++i)
        result_reverse.at(i)= temp_reverse.at(i)+'0';
    HugeInt a;
    a.reverse = result_reverse;
    return a;
}
HugeInt HugeInt::operator -(HugeInt &right) {//ok
    int length;
    int this_bigger = 1;
    if(right.reverse.size() > reverse.size()) {
        length = right.reverse.size();
        for(int temp = reverse.size(); temp < length; ++temp) {
            reverse.push_back('0');
        }
        this_bigger = 0;
    }
    else {
        if(reverse.size() == right.reverse.size()) {
            length = reverse.size();
            for(int i = reverse.size()-1; i >= 0; --i) {
                if(reverse.at(i) == right.reverse.at(i))
                    continue;
                else if(reverse.at(i) > right.reverse.at(i))
                    break;
                else if(reverse.at(i) < right.reverse.at(i)) {
                    this_bigger = 0;
                    break;
                }
            }
        }
        else {
            length = reverse.size();
            for(int temp = right.reverse.size(); temp < length; ++temp) {
                right.reverse.push_back('0');
            }
        }
    }
    
    vector<int> temp_reverse(length);
    vector<int> this_int(length);
    vector<int> right_int(length);

    for(int i = 0; i < length; ++i) {
        this_int.at(i) = (reverse.at(i)-'0');
        right_int.at(i) = (right.reverse.at(i)-'0');
    }

    if(this_bigger == 1) {
        for(int i = 0; i < length; ++i) {
            temp_reverse.at(i) += this_int.at(i) - right_int.at(i);
            if(i != length - 1) {
                if(temp_reverse.at(i) < 0) {
                    temp_reverse.at(i) += 10;
                    --temp_reverse.at(i+1);
                }
            }
        }
    }
    else if(this_bigger == 0) {
        for(int i = 0; i < length; ++i) {
            temp_reverse.at(i) += right_int.at(i) - this_int.at(i);
            if(i != length - 1) {
                if(temp_reverse.at(i) < 0) {
                    temp_reverse.at(i) += 10;
                    --temp_reverse.at(i+1);
                }
            }
        }   
    }
    int temp_length;
    for(int i = length-1; i >= 0; ++i) {
        if(temp_reverse.at(i) == 0) {
            if(i == 0)
                temp_length = 1;
            continue;
        }
        else {
            temp_length = i+1;
            break;
        }
    }
    vector<char> result_reverse(temp_length);
    for(int i = 0; i < result_reverse.size(); ++i) {
        if(this_bigger == 0 && i == result_reverse.size()-1)
            result_reverse.at(i) = (temp_reverse.at(i)*(-1))+'0';
        else
            result_reverse.at(i) = (temp_reverse.at(i))+'0';
    }
    HugeInt a;
    a.reverse = result_reverse;
    return a;
}
