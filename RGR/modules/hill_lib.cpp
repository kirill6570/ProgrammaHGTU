#include <string>
#include <cstdint>
using namespace std;
int modInv(int a) { for (int i=1;i<256;i++) if ((a*i)%256==1) return i; return 1; }
extern "C" string hillEncrypt(const string &text, const string &key) {
    int a=key[0],b=key[1],c=key[2],d=key[3]; string data=text; if (data.size()%2) data+='\0'; string res;
    for(size_t i=0;i<data.size();i+=2){ unsigned char x=data[i],y=data[i+1];
        res+=(unsigned char)((a*x+b*y)%256); res+=(unsigned char)((c*x+d*y)%256); } return res; }
extern "C" string hillDecrypt(const string &text, const string &key) {
    int a=key[0],b=key[1],c=key[2],d=key[3]; int det=(a*d-b*c)%256; if(det<0)det+=256; int inv=modInv(det);
    int ia=(inv*d)%256,ib=(-inv*b)%256; if(ib<0)ib+=256; int ic=(-inv*c)%256; if(ic<0)ic+=256; int id=(inv*a)%256;
    string res; for(size_t i=0;i<text.size();i+=2){ unsigned char x=text[i],y=text[i+1];
        res+=(unsigned char)((ia*x+ib*y)%256); res+=(unsigned char)((ic*x+id*y)%256); } return res; }
