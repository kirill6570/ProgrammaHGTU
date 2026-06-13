#ifndef MATH_UTILS_H
#define MATH_UTILS_H

bool isPrime(int n);

// алгоритм быстрого (бинарного) возведения в степень
int binaryPow(int a, int x, int p);

// возведение в степень с испол. теоремы Ферма
int fermatPow(int a, int x, int p);

#endif
