#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <string>

std::string playfairEncrypt(const std::string& text, const std::string& key);
std::string playfairDecrypt(const std::string& text, const std::string& key);
void playfairEncryptFile(const std::string& inFile, const std::string& outFile, const std::string& key);
void playfairDecryptFile(const std::string& inFile, const std::string& outFile, const std::string& key);

#endif
