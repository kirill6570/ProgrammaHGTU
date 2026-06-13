#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <dlfcn.h>
#include <random>
#include <cstring>

using namespace std;
namespace fs = filesystem;

struct Buf { const unsigned char* d; size_t s; };
struct MBuf { unsigned char* d; size_t s; };
struct Info { const char* n; size_t ks; };

// enum class для выбора алгоритмов
enum class Algo {
    EXIT = 0,
    CAESAR = 1,
    RSA = 2,
    RC4 = 3,
    TEA = 4
};

// Глобальные указатели для библиотек
static void* lib_handle = nullptr;
static const Info* (*lib_get_info)() = nullptr;
static size_t (*lib_out_size)(size_t, int) = nullptr;
static int (*lib_enc)(Buf, Buf, MBuf*) = nullptr;
static int (*lib_dec)(Buf, Buf, MBuf*) = nullptr;

// Поиск всех алгоритмов в crypto_modules/
vector<string> find_algorithms() {
    vector<string> algos;
    string path = "crypto_modules";
    if (!fs::exists(path)) return algos;
    
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            string name = entry.path().filename().string();
            string so_file = path + "/" + name + "/" + name + ".so";
            if (fs::exists(so_file)) {
                algos.push_back(name);
            }
        }
    }
    return algos;
}

// Загрузка библиотеки
bool load_algorithm(const string& algo) {
    if (lib_handle) dlclose(lib_handle);
    lib_handle = nullptr;
    
    string lib_path = "crypto_modules/" + algo + "/" + algo + ".so";
    lib_handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!lib_handle) return false;
    
    lib_get_info = (const Info*(*)())dlsym(lib_handle, "get_info");
    lib_out_size = (size_t(*)(size_t,int))dlsym(lib_handle, "out_size");
    lib_enc = (int(*)(Buf,Buf,MBuf*))dlsym(lib_handle, "enc");
    lib_dec = (int(*)(Buf,Buf,MBuf*))dlsym(lib_handle, "dec");
    
    if (!lib_get_info || !lib_out_size || !lib_enc || !lib_dec) {
        dlclose(lib_handle);
        lib_handle = nullptr;
        return false;
    }
    return true;
}

// Шифр Цезаря (встроенный)
string caesar_crypt(string text, int shift, int mode) {
    string res = "";
    if (mode == 2) shift = -shift;
    for (char c : text) {
        if (c >= 'a' && c <= 'z')
            res += char(((c - 'a' + shift) % 26 + 26) % 26 + 'a');
        else if (c >= 'A' && c <= 'Z')
            res += char(((c - 'A' + shift) % 26 + 26) % 26 + 'A');
        else
            res += c;
    }
    return res;
}

// Общая функция для библиотечных алгоритмов
string process_lib(const string& text, const string& key_file, int mode, const string& algo) {
    if (!load_algorithm(algo)) {
        return "Ошибка: библиотека " + algo + " не загружена";
    }
    
    vector<unsigned char> key;
    if (!key_file.empty()) {
        ifstream f(key_file, ios::binary);
        if (f) key = vector<unsigned char>((istreambuf_iterator<char>(f)), {});
    }
    
    vector<unsigned char> input(text.begin(), text.end());
    size_t out_sz = lib_out_size(input.size(), mode == 1 ? 0 : 1);
    vector<unsigned char> output(out_sz);
    
    Buf k = {key.data(), key.size()};
    Buf in = {input.data(), input.size()};
    MBuf out = {output.data(), output.size()};
    
    int ret;
    if (mode == 1) ret = lib_enc(k, in, &out);
    else ret = lib_dec(k, in, &out);
    
    if (ret != 0) return "Ошибка операции";
    
    return string(output.begin(), output.end());
}

void print_algo_menu() {
    cout << "\nВыберите алгоритм:\n";
    cout << "1. Цезарь\n";
    cout << "2. RSA\n";
    cout << "3. RC4\n";
    cout << "4. TEA\n";
    cout << "0. Назад\n";
    cout << "> ";
}

int main() {
    int choice, op, algo_choice;
    string text, key, infile, outfile;
    
    while (true) {
        cout << "\n===== CRIPTAKRUTO =====\n";
        cout << "1. Шифрование/дешифрование текста\n";
        cout << "2. Шифрование/дешифрование файла\n";
        cout << "0. Выход\n";
        cout << "=======================\n";
        cout << "> ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 0) break;
        
        if (choice != 1 && choice != 2) {
            cout << "Неверный выбор\n";
            continue;
        }
        
        print_algo_menu();
        cin >> algo_choice;
        cin.ignore();
        
        Algo a = static_cast<Algo>(algo_choice);
        
        if (a == Algo::EXIT) continue;
        if (algo_choice < 1 || algo_choice > 4) {
            cout << "Неверный выбор\n";
            continue;
        }
        
        // Получаем строковое имя алгоритма
        string algo_name;
        switch (a) {
            case Algo::CAESAR: algo_name = "caesar"; break;
            case Algo::RSA:    algo_name = "rsa"; break;
            case Algo::RC4:    algo_name = "rc4"; break;
            case Algo::TEA:    algo_name = "tea"; break;
            default: break;
        }
        
        if (choice == 1) {
            // Текст
            cout << "Введите текст: ";
            getline(cin, text);
            cout << "Введите ключ (файл): ";
            getline(cin, key);
            cout << "1 - Шифровать, 2 - Дешифровать: ";
            cin >> op;
            cin.ignore();
            
            string result;
            if (a == Algo::CAESAR) {
                int shift = 3;
                if (!key.empty()) shift = stoi(key);
                result = caesar_crypt(text, shift, op);
            } else {
                result = process_lib(text, key, op, algo_name);
            }
            cout << "Результат: " << result << "\n";
        }
        else if (choice == 2) {
            // Файл
            cout << "Входной файл: ";
            getline(cin, infile);
            cout << "Выходной файл: ";
            getline(cin, outfile);
            cout << "Введите ключ (файл): ";
            getline(cin, key);
            cout << "1 - Шифровать, 2 - Дешифровать: ";
            cin >> op;
            cin.ignore();
            
            ifstream f(infile, ios::binary);
            if (!f) {
                cout << "Ошибка открытия файла\n";
                continue;
            }
            string content((istreambuf_iterator<char>(f)), {});
            f.close();
            
            string result;
            if (a == Algo::CAESAR) {
                int shift = 3;
                if (!key.empty()) shift = stoi(key);
                result = caesar_crypt(content, shift, op);
            } else {
                result = process_lib(content, key, op, algo_name);
            }
            
            ofstream fout(outfile, ios::binary);
            fout << result;
            fout.close();
            cout << "Готово! Результат в " << outfile << "\n";
        }
    }
    
    if (lib_handle) dlclose(lib_handle);
    return 0;
}
