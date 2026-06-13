#ifndef HILL_H
#define HILL_H

#include <string>

std::string hillEncrypt(const std::string &text, const std::string &key);
std::string hillDecrypt(const std::string &text, const std::string &key);
void hillEncryptFile(const std::string &inFile, const std::string &outFile, const std::string &key);
void hillDecryptFile(const std::string &inFile, const std::string &outFile, const std::string &key);

#endif
