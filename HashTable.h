#pragma once
#include "games.h"
#include <string>


/*
1) Конструктор (N, % заполнияемости)
2) Деструктор
3) Hash_f1 (key) -> addr
4) Hash_f2 (addr, n попытки) -> add
5) Add (record) -> int  (не добовлять одинаковые, не добовлять с одинаковым ключём)
6) Del (record) -> (если все поля совпали)
7) Search (record) -> (true/false)
8) Печать (перегрузка вывоа в поток <<)
 */
using namespace std;

class HashTable {
private:
    Game* table;
    int* is_use; // вектор состояний 0 - пустая, 1 - заполнена, 2 - удалена
    int max_size;
    unsigned int resize_occupancy; // в процентах от 0 до 100
    unsigned int occupancy; // процент заполненности от 0 до 100

// 3) Hash_f1 (key) -> addr
    int HashF1(size_t key) const;

// 4) Hash_f2 (hash, n попытки) -> add
    int HashF2(int h1, int n) const;

    int ReSize();

    int ReHash();

public:

//    1) Конструктор (N, % заполнияемости)
    HashTable(int max_size, unsigned int resize_occupancy);

//    2) Деструктор
    ~HashTable();

//    5) Add (record) -> int (1 ок, 0 плохо) (не добовлять одинаковые, не добовлять с одинаковым ключём)
    int AddHash(Game cell);

//    6) Del (record) ->
    int DelHash(Game cell);

//    7) Search (record) -> (true/false)
    bool SearchCell(Game cell);

//    8) Печать (перегрузка вывоа в поток <<)
	friend ostream& operator<<(ostream& out, const HashTable& ht);
};

