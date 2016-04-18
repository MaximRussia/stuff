
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int hexToNum(char ch) {
    if(ch >= '0' && ch <= '9') return ch - '0';
    if(ch >= 'a' && ch <= 'f') return 10 + ch - 'a';
    if(ch >= 'A' && ch <= 'F') return 10 + ch - 'A';
    return -1;
}

int baseToDec(string &num, int base) {
    if(base != 2 && base != 16) return -1;
    int last = num.size() - 1;
    int res = 0;
    for(int i = 0; i <= last; ++i)
        res += hexToNum(num[i]) * pow(base, last - i);

    return res;
}

bool cmpBinHex(string &num1, int base1, string &num2, int base2) {
    return baseToDec(num1, base1) == baseToDec(num2, base2);
}

bool cmpBinHex(string num1, int base1, string num2, int base2) {
    return baseToDec(num1, base1) == baseToDec(num2, base2);
}

int main()
{
    cout << cmpBinHex("1010", 2, "a", 16) << endl;
    return 0;
}
