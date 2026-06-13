#include <string>
#include <vector>
#include <algorithm>
using namespace std;
extern "C" string transposEncrypt(const string &text, const string &key) {
    int cols=key.size(); if(!cols) return text; string data=text;
    int rows=(data.size()+cols-1)/cols; while((int)data.size()<rows*cols) data+='\0';
    vector<int> ord(cols); for(int i=0;i<cols;i++) ord[i]=i;
    string k=key; for(int i=0;i<cols-1;i++) for(int j=i+1;j<cols;j++)
        if(k[i]>k[j]){ swap(k[i],k[j]); swap(ord[i],ord[j]); }
    string res; for(int i=0;i<cols;i++){ int col=ord[i]; for(int r=0;r<rows;r++) res+=data[r*cols+col]; }
    return res; }
extern "C" string transposDecrypt(const string &text, const string &key) {
    int cols=key.size(); if(!cols) return text; int rows=text.size()/cols;
    vector<int> ord(cols); for(int i=0;i<cols;i++) ord[i]=i;
    string k=key; for(int i=0;i<cols-1;i++) for(int j=i+1;j<cols;j++)
        if(k[i]>k[j]){ swap(k[i],k[j]); swap(ord[i],ord[j]); }
    string res(rows*cols,'\0'); int pos=0;
    for(int i=0;i<cols;i++){ int col=ord[i]; for(int r=0;r<rows;r++) res[r*cols+col]=text[pos++]; }
    return res; }
