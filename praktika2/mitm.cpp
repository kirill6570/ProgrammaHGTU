#include "mitm.h"
#include <iostream>
using namespace std;


int powMod(int base, int exp, int mod);
int inverseMod(int c, int m);

// атака посередине на шифр Хьюза
void mitmAttack(int p, int g, int a, int b, int ca, int cb, int message) {
    int k = 5;                      

    int A = powMod(g, a, p);       
    int B = powMod(g, b, p);       

    int Ca = powMod(g, ca, p);      
    int Cb = powMod(g, cb, p);      

    cout << "A = " << g << "^" << a << " mod " << p << " = " << A << endl;
    cout << "B = " << g << "^" << b << " mod " << p << " = " << B << endl;
    cout << "C_a = " << Ca << " (A думает, что это B)" << endl;
    cout << "C_b = " << Cb << " (B думает, что это A)" << endl;


    int r = powMod(g, k, p);                    // r = g^k mod p
    int s_a = powMod(Ca, k, p);                 // общий секрет A с C
    int e_a = (1LL * message * s_a) % p;      
    cout << "\nA отправляет: r=" << r << " e=" << e_a << endl;


    int s_c = powMod(r, ca, p);            
    int inv_c = inverseMod(s_c, p);            
    int m_c = (1LL * e_a * inv_c) % p;       
    cout << "C читает: " << m_c << endl;

    int s_cb = powMod(B, k, p);                 // общий секрет C с B
    int e_b = (1LL * m_c * s_cb) % p;        
    cout << "C отправляет B: r=" << r << " e=" << e_b << endl;


    int s_b = powMod(r, b, p);                  // общий секрет B с C
    int inv_b = inverseMod(s_b, p);             
    int m_b = (1LL * e_b * inv_b) % p;        
    cout << "B читает: " << m_b << endl;

    if (m_b == message)
        cout << "\nАтака успешна. B ничего не заметил." << endl;
}