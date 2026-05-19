#include <iostream>
using namespace std;

int obf_add(int packed) {
    int a = (packed >> 16) & 0xFFFF;
    int b = packed & 0xFFFF;
    return a + b;
}

int main() {
    int a = 5, b = 3;
    int packed = (a << 16) | b; // 5 and 3 to 1 numberr
    cout << "Packed value: " << packed << endl;
    cout << "Decoded sum: " << obf_add(packed) << endl;
    return 0;
}
