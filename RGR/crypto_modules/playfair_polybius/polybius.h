#ifndef POLYBIUS_H
#define POLYBIUS_H

#include <string>

std::string polybiusEncrypt(const std::string& text, const std::string& key);
std::string polybiusDecrypt(const std::string& text, const std::string& key);
void polybiusEncryptFile(const std::string& inFile, const std::string& outFile, const std::string& key);
void polybiusDecryptFile(const std::string& inFile, const std::string& outFile, const std::string& key);

#endif
