#include <string>
#include <cstdint>
using namespace std;
extern "C" string rc4Crypt(const string &text, const string &key) {
    int S[256]; for(int i=0;i<256;i++) S[i]=i; int j=0;
    for(int i=0;i<256;i++){ j=(j+S[i]+key[i%key.size()])%256; swap(S[i],S[j]); }
    string res=text; int i=0;j=0;
    for(size_t k=0;k<text.size();k++){ i=(i+1)%256; j=(j+S[i])%256; swap(S[i],S[j]);
        res[k]=text[k]^S[(S[i]+S[j])%256]; }
    return res; }
