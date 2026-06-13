#include <gmpxx.h>
#include <iostream>
#include "math_utils.h"
#include "euclid.h"
#include "inverse_utils.h"
#include "hughes.h"
#include "mitm.h"
using namespace std;

enum class Menu {
    EXIT = 0,
    POW = 1,
    EUCLID = 2,
    INVERSE = 3,
    HUGHES = 4,
    MITM = 5
};

int main() {
    int choice;

    while (true) {
        cout << "  ПРАКТИЧЕСКАЯ РАБОТА №2" << endl;
        cout << "1 - a^x mod p" << endl;
        cout << "2 - НОД, u, v" << endl;
        cout << "3 - c^-1 mod m" << endl;
        cout << "4 - Шифр Хьюза" << endl;
        cout << "5 - Атака посередине" << endl;
        cout << "0 - Выход" << endl;
        cout << ">> ";
        cin >> choice;

        Menu m = static_cast<Menu>(choice);

        switch (m) {
            case Menu::EXIT:
                return 0;

            case Menu::POW: {
                int a, x, p;
                cout << "a, x, p: ";
                cin >> a >> x >> p;
                cout << "Бинарно: " << binaryPow(a, x, p) << endl;
                int res = fermatPow(a, x, p);
                if (res != -1) cout << "Ферма: " << res << endl;
                break;
            }

            case Menu::EUCLID: {
                int c, m, u, v;
                cout << "c, m: ";
                cin >> c >> m;
                Euclid(c, m, u, v);
                break;
            }

            case Menu::INVERSE: {
                int c, m;
                cout << "c, m: ";
                cin >> c >> m;
                int d = findModularInverse(c, m);
                if (d != -1) cout << "d = " << d << endl;
                break;
            }

            case Menu::HUGHES: {
                mpz_class p("1234567891011121314151617181920"), g = 5, b = 13;
                hughesEncryptFile("plain.txt", "cipher.txt", p, g, b);
                hughesDecryptFile("cipher.txt", "decrypted.txt", p, g, b);
                break;
            }

            case Menu::MITM: {
                int p, g, a, b, ca, cb, message;
                cout << "p, g: ";
                cin >> p >> g;
                cout << "a, b: ";
                cin >> a >> b;
                cout << "ca, cb: ";
                cin >> ca >> cb;
                cout << "message: ";
                cin >> message;
                mitmAttack(p, g, a, b, ca, cb, message);
                break;
            }
        }
    }
}