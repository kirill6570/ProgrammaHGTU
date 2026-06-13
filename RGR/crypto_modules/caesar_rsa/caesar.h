#ifndef CAESAR_H
#define CAESAR_H

#include <string>

std::string caesarEncrypt(const std::string &text, int shift);
std::string caesarDecrypt(const std::string &text, int shift);
void caesarEncryptFile(const std::string &inFile, const std::string &outFile, int shift);
void caesarDecryptFile(const std::string &inFile, const std::string &outFile, int shift);

#endif
