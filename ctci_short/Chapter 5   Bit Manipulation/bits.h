
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void swap_bits(int &a, int &b) {
    a ^= b ^= a ^= b;
}

int getBin(int n, int i) {
    return n & (1 << i);
}

int setBin(int n, int i) {
    return n | (1 << i);
}

int clearBit(int n, int i) {
    int mask = ~(1 << i);
    return n & mask;
}

int clearBits1(int n, int i) {
    int mask = (1 << i) - 1;
    return n & mask;
}

int clearBits2(int n, int i) {
    int mask = ~((1 << i) - 1);
    return n & mask;
}

string toString(int num) {
    string res;
    while (num != 0) {
        res.push_back('0' + (num & 1));
        num >>= 1;
    }
    std::reverse(res.begin(), res.end());
    return res;
}


int toInt(string str) {
    if(str.size() > sizeof(int) * 8) return 0;
    int res = 0;
    int size = str.size() - 1;
    for(int i = size; i >= 0; --i) {
        res |= ( (str[i] - '0') << (size - i) );
    }
    return res;
}
