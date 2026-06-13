#include <string>
#include <cstdint>
using namespace std;

extern "C" string caesarEncrypt(const string &text, int shift) {
    string result;
    for (size_t i = 0; i < text.size(); i++) {
        unsigned char ch = text[i];
        result += (char)((int)ch + shift);
    }
    return result;
}

extern "C" string caesarDecrypt(const string &text, int shift) {
    return caesarEncrypt(text, -shift);
}
