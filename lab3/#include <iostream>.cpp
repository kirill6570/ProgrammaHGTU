исключения
#include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
 
int reting(int x, int y) {
    if (x == 0 && y == 0) {
        throw "negodai";

    }
    return (x+y) /2;
}

int main() 
{
 int x = 0; // cеместр
 int y = 0; // экзамен
 cout << reting(x,y) << endl;
    return 0;
}


НОВАЯ ПРОБЛЕМА

#include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
 
int reting(int x, int y) {
    if (x == 0 && y == 0) {
        throw "negodai";

    }
    return (x+y) /2;
}

int main() 
{
 int x = 0; // cеместр
 int y = 0; // экзамен
 try {
 cout << reting(x,y) << endl;
 } catch(const char* str) {
    cerr << str << endl;
 }
    return 0;
}

Исключение- это реакция на нештатную ситуацию для управления исключением доступны три компоненты 1. генерация исключения 2. перехват исключения разработчиком 3.использование блока try
программа переватывает исключения с помощью обработчика исключения, расположенного в том месте программы где исключения необходимы обработать.
 ключевое слово catch  обозначает перехват исключения.в скобках ууказывается обьявление типа, которая соответсвует нашему исключению. 
 ключевое слово catch играет роль метки определяющую точку в программе, куда должно быть переданно управление при возникновении исключения
 Правила исключения 
 на автомате прокидывает 
 #include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
 
int reting(int x, int y) {
    if (x == 0 && y == 0) {
        throw "negodai";

    }
    return (x+y) /2;
}

int main() 
{
 int x = 0; // cеместр
 int y = 0; // экзамен
 try {
    new int [500000000000];

 } catch(...) {
    cerr << "Catch" << endl;
 }
    return 0;
}

 #include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
 

vector <int> v;
 try {
    v[500000000000] = 1;
 } catch(...) {
    cerr << "Catch" << endl;
 }
    return 0;
}
Исключения С++  они идут на этапе Runtime (на этапе сборки)
seqw сигментейшн фол. 
 #include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
 

int x;
cin >> x;
 try {
    cout << 5555555 / x;
 } catch(...) {
    cerr << "Catch" << endl;
 }
    return 0;

#include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
void div (int x, int y) {
    if (y == 0) {
        throw "xero";
    }
}
int main () {
    try{
    div(1,0);
    } catch(legic_error& str) {
        cerr << str.what() << endl;
    }
    }
    return 0;
 
}
логические ошибки но та которая 
#include <iostream>
#include <exception>
#include <cstdint>

using namespace std;
struct Time {
    int h;
    int m;


};
void Check(stringstream& sstr) {
    if (sstr.peek() ! = ":"){
        stringstream ee;
        ee<< "we expected : , but hane " << char(sstr.peak());
        throw runtime  
    }
}

Time Get (const string& str) {
    TIme t;
    stringstream s(str);
    s >> t.h;
    Check(s);
    s >> t.m;

}
int main () {
    string time = "15:27";
    Time t = Get(time);
    cout << t.h << " " << t.m

    return t;
int main () {
    string time = "15:27"
    try {
        Time t = Get(time);
        cout << t.h << t.m << endl 
    } catch (exception& ex) {
        cerr << ex.what() << endl;;
    }
    return 0;
    }
}