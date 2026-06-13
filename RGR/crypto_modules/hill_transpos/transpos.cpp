include "transpos.h"
#include <vector>
#include <fstream>

string transposEncrypt(const string &text, string key) {
    int cols = key.size();
    if (cols == 0) return text;

    string data = text;
    int rows = (data.size() + cols - 1) / cols;
    while ((int)data.size() < rows * cols) data += '\0';

    vector<int> order(cols);
    for (int i = 0; i < cols; i++) order[i] = i;
    for (int i = 0; i < cols - 1; i++)
        for (int j = i + 1; j < cols; j++)
            if (key[i] > key[j]) {
                char t = key[i]; key[i] = key[j]; key[j] = t;
                int tt = order[i]; order[i] = order[j]; order[j] = tt;
            }

    string result;
    for (int i = 0; i < cols; i++) {
        int col = order[i];
        for (int r = 0; r < rows; r++)
            result += data[r * cols + col];
    }
    return result;
}

string transposDecrypt(const string &text, string key) {
    int cols = key.size();
    if (cols == 0) return text;

    int rows = text.size() / cols;

    vector<int> order(cols);
    for (int i = 0; i < cols; i++) order[i] = i;
    for (int i = 0; i < cols - 1; i++)
        for (int j = i + 1; j < cols; j++)
            if (key[i] > key[j]) {
                char t = key[i]; key[i] = key[j]; key[j] = t;
                int tt = order[i]; order[i] = order[j]; order[j] = tt;
            }

    string result(rows * cols, '\0');
    int pos = 0;
    for (int i = 0; i < cols; i++) {
        int col = order[i];
        for (int r = 0; r < rows; r++)
            result[r * cols + col] = text[pos++];
    }
    return result;
}

void transposEncryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = transposEncrypt(content, key);
    for (size_t i = 0; i < result.size(); i++) out.put(result[i]);
}

void transposDecryptFile(const string &inFile, const string &outFile, const string &key) {
    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    string content;
    char ch;
    while (in.get(ch)) content += ch;
    string result = transposDecrypt(content, key);
    for (size_t i = 0; i < result.size(); i++) out.put(result[i]);
}
