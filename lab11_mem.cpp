#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;

int main() {
    unsigned char code[] = { 0xB8, 0x05, 0x00, 0x00, 0x00, 0xC3 };

    void* exec = VirtualAlloc(0, sizeof(code), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, code, sizeof(code));

    int (*func)() = (int(*)())exec;
    cout << "Result from RAM execution: " << func() << endl;

    return 0;
}
