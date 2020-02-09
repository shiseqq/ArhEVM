#ifndef _SIMPLEPC_H_
#include <bits/stdc++.h>

using namespace std;

#define P 0 //переполнение при выполнении операции,
#define D 1 //ошибка деления на 0
#define M 2 //ошибка выхода за границы памяти
#define T 3 //игнорирование тактовых импульсов
#define E 4 //указана неверная команда

int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int*);
int sc_memorySave(string);
int sc_memoryLoad(string);
int sc_regInit();
int sc_regSet(int, int);
int sc_regGet(int, int*);
int sc_commandEncode(int, int, int*);
int sc_commandDecode(int, int*, int*);
#endif