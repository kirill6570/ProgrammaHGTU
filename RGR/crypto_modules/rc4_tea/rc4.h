#ifndef RC4_H
#define RC4_H

#include <string>

std::string rc4Encrypt(const std::string &text, const std::string &key);
std::string rc4Decrypt(const std::string &text, const std::string &key);
void rc4EncryptFile(const std::string &inFile, const std::string &outFile, const std::string &key);
void rc4DecryptFile(const std::string &inFile, const std::string &outFile, const std::string &key);

#endif
