#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

using namespace std;

enum class Menu { EXIT = 0, CAESAR = 1, RSA = 2, PLAYFAIR = 3, POLYBIUS = 4,
                  HILL = 5, TRANSPOS = 6, RC4 = 7, TEA = 8, GENKEY = 9 };

#ifdef _WIN32
    #define LOAD_LIB(path)    LoadLibrary(path)
    #define GET_FUNC(h, name) GetProcAddress((HMODULE)h, name)
    #define CLOSE_LIB(h)      FreeLibrary((HMODULE)h)
    #define LIB_EXT           ".dll"
#else
    #define LOAD_LIB(path)    dlopen(path, RTLD_LAZY)
    #define GET_FUNC(h, name) dlsym(h, name)
    #define CLOSE_LIB(h)      dlclose(h)
    #define LIB_EXT           ".so"
#endif

void showMenu() {
    cout << "\n         RGR - kriptaKruto" << endl;
    cout << " 1 - Шифр Цезаря" << endl;
    cout << " 2 - RSA" << endl;
    cout << " 3 - Плейфер" << endl;
    cout << " 4 - Полибий" << endl;
    cout << " 5 - Хилл" << endl;
    cout << " 6 - Двойная перестановка" << endl;
    cout << " 7 - RC4" << endl;
    cout << " 8 - TEA" << endl;
    cout << " 9 - Генератор ключей" << endl;
    cout << " 0 - Выход" << endl;
    cout << ">> ";
}

void generateKeys() {
    int ch;
    cout << "\n=== ГЕНЕРАТОР КЛЮЧЕЙ ===" << endl;
    showMenu();  
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (ch) {
    case 1: { int s = rand() % 25 + 1; cout << "Сдвиг: " << s << endl; break; }
    case 2: {
        long long p, q; cout << "p, q: "; cin >> p >> q;
        long long N = p * q, phi = (p-1)*(q-1);
        long long d = 2; while (d < phi) { long long a=d,b=phi; while(b){long long t=a%b;a=b;b=t;} if(a==1)break; d++; }
        long long c = 1; while ((d*c)%phi != 1) c++;
        cout << "N=" << N << "\n(d,N)=(" << d << "," << N << ")\n(c,N)=(" << c << "," << N << ")" << endl;
        break;
    }
    case 3: { string k[]={"KEY","SECRET","CRYPTO","CIPHER","MATRIX"}; cout << "Ключ: " << k[rand()%5] << endl; break; }
    case 4: { cout << "Без ключа." << endl; break; }
    case 5: { char a='a'+rand()%26,b='a'+rand()%26,c='a'+rand()%26,d='a'+rand()%26; cout << "Ключ: "<<a<<b<<c<<d<<endl; break; }
    case 6: { cout << "Ключ: " << rand()%9000+1000 << endl; break; }
    case 7: { string s="abcdefghijklmnopqrstuvwxyz0123456789",k; for(int i=0;i<8;i++)k+=s[rand()%s.size()]; cout<<"Ключ: "<<k<<endl; break; }
    case 8: { string s="abcdefghijklmnopqrstuvwxyz0123456789",k; for(int i=0;i<16;i++)k+=s[rand()%s.size()]; cout<<"Ключ: "<<k<<endl; break; }
    }
}

int main() {
    srand(time(0));
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 0) { cout << "До свидания!" << endl; return 0; }

        if (choice == 9) { generateKeys(); continue; }

        Menu m = static_cast<Menu>(choice);

        cout << "\nРежим: 1 - Текст | 2 - Файл: ";
        int mode; cin >> mode;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string text, key, lib, encName, decName;

        switch (m) {
            case Menu::CAESAR:   lib="./modules/libcaesar" LIB_EXT; encName="caesarEncrypt"; decName="caesarDecrypt"; break;
            case Menu::RSA:      lib="./modules/librsa" LIB_EXT; encName="rsaEncrypt"; decName="rsaDecrypt"; break;
            case Menu::PLAYFAIR: lib="./modules/libplayfair" LIB_EXT; encName="playfairEncrypt"; decName="playfairDecrypt"; break;
            case Menu::POLYBIUS: lib="./modules/libpolybius" LIB_EXT; encName="polybiusEncrypt"; decName="polybiusDecrypt"; break;
            case Menu::HILL:     lib="./modules/libhill" LIB_EXT; encName="hillEncrypt"; decName="hillDecrypt"; break;
            case Menu::TRANSPOS: lib="./modules/libtranspos" LIB_EXT; encName="transposEncrypt"; decName="transposDecrypt"; break;
            case Menu::RC4:      lib="./modules/librc4" LIB_EXT; encName="rc4Crypt"; decName="rc4Crypt"; break;
            case Menu::TEA:      lib="./modules/libtea" LIB_EXT; encName="teaEncrypt"; decName="teaDecrypt"; break;
            default: continue;
        }

        void* handle = LOAD_LIB(lib.c_str());
        if (!handle) { cout << "Ошибка загрузки " << lib << endl; continue; }

        if (mode == 1) { cout << "Текст: "; getline(cin, text); }
        else { cout << "Входной файл: "; getline(cin, text); cout << "Выходной файл: "; getline(cin, key); }

        cout << "Операция: 1 - Шифровать | 2 - Расшифровать: ";
        int op; cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (m == Menu::CAESAR) {
            typedef string (*F)(const string&, int);
            F enc = (F)GET_FUNC(handle, encName.c_str());
            F dec = (F)GET_FUNC(handle, decName.c_str());
            int shift; cout << "Сдвиг: "; cin >> shift;

            if (mode == 1) {
                cout << (op == 1 ? enc(text, shift) : dec(text, shift)) << endl;
            } else {
                ifstream in(text, ios::binary); ofstream out(key, ios::binary);
                string c; char ch; while (in.get(ch)) c += ch;
                string r = (op == 1) ? enc(c, shift) : dec(c, shift);
                for (size_t i = 0; i < r.size(); i++) out.put(r[i]);
                cout << "Готово: " << key << endl;
            }
        }
        else if (m == Menu::RSA) {
            typedef string (*F)(const string&, long long, long long);
            F enc = (F)GET_FUNC(handle, encName.c_str());
            F dec = (F)GET_FUNC(handle, decName.c_str());

            if (mode == 1) {
                if (op == 1) { long long d, N; cout << "d, N: "; cin >> d >> N; cout << enc(text, d, N) << endl; }
                else { long long c, N; cout << "c, N: "; cin >> c >> N; cout << dec(text, c, N) << endl; }
            } else {
                ifstream in(text, ios::binary); ofstream out(key, ios::binary);
                string ct; char ch; while (in.get(ch)) ct += ch;
                if (op == 1) { long long d, N; cout << "d, N: "; cin >> d >> N; out << enc(ct, d, N); }
                else { long long c, N; cout << "c, N: "; cin >> c >> N; out << dec(ct, c, N); }
                cout << "Готово: " << key << endl;
            }
        }
        else if (m == Menu::PLAYFAIR || m == Menu::HILL || m == Menu::TRANSPOS) {
            typedef string (*F)(const string&, const string&);
            F enc = (F)GET_FUNC(handle, encName.c_str());
            F dec = (F)GET_FUNC(handle, decName.c_str());
            string k; cout << "Ключ: "; getline(cin, k);

            if (mode == 1) {
                cout << (op == 1 ? enc(text, k) : dec(text, k)) << endl;
            } else {
                ifstream in(text, ios::binary); ofstream out(key, ios::binary);
                string ct; char ch; while (in.get(ch)) ct += ch;
                string r = (op == 1) ? enc(ct, k) : dec(ct, k);
                for (size_t i = 0; i < r.size(); i++) out.put(r[i]);
                cout << "Готово: " << key << endl;
            }
        }
        else if (m == Menu::POLYBIUS) {
            typedef string (*F)(const string&);
            F enc = (F)GET_FUNC(handle, encName.c_str());
            F dec = (F)GET_FUNC(handle, decName.c_str());

            if (mode == 1) {
                cout << (op == 1 ? enc(text) : dec(text)) << endl;
            } else {
                ifstream in(text, ios::binary); ofstream out(key, ios::binary);
                string ct; char ch; while (in.get(ch)) ct += ch;
                string r = (op == 1) ? enc(ct) : dec(ct);
                for (size_t i = 0; i < r.size(); i++) out.put(r[i]);
                cout << "Готово: " << key << endl;
            }
        }
        else if (m == Menu::RC4) {
            typedef string (*F)(const string&, const string&);
            F enc = (F)GET_FUNC(handle, encName.c_str());
            string k; cout << "Ключ: "; getline(cin, k);

            if (mode == 1) {
                string r = enc(text, k);
                if (op == 1) { cout << "hex: "; for (size_t i = 0; i < r.size(); i++) cout << hex << (int)(unsigned char)r[i] << " "; cout << dec << endl; }
                else cout << r << endl;
            } else {
                ifstream in(text, ios::binary); ofstream out(key, ios::binary);
                string ct; char ch; while (in.get(ch)) ct += ch;
                string r = enc(ct, k);
                for (size_t i = 0; i < r.size(); i++) out.put(r[i]);
                cout << "Готово: " << key << endl;
            }
        }
        else if (m == Menu::TEA) {
            typedef string (*F)(const string&, const string&);
            F enc = (F)GET_FUNC(handle, encName.c_str());
            F dec = (F)GET_FUNC(handle, decName.c_str());
            string k; cout << "Ключ: "; getline(cin, k);

            if (mode == 1) {
                if (op == 1) { string r = enc(text, k); cout << "hex: "; for (size_t i = 0; i < r.size(); i++) cout << hex << (int)(unsigned char)r[i] << " "; cout << dec << endl; }
                else cout << dec(text, k) << endl;
            } else {
                ifstream in(text, ios::binary); ofstream out(key, ios::binary);
                string ct; char ch; while (in.get(ch)) ct += ch;
                string r = (op == 1) ? enc(ct, k) : dec(ct, k);
                for (size_t i = 0; i < r.size(); i++) out.put(r[i]);
                cout << "Готово: " << key << endl;
            }
        }

        CLOSE_LIB(handle);
    }
}