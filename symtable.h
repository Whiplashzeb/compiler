//
// Created by 赵恩博 on 16/5/1.
//

#ifndef COMPILE_SYMTABLE_H
#define COMPILE_SYMTABLE_H

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

extern int offset;

typedef struct sym {
    string name;
    string type;
    string conte;
    int size;
    int num;
} symbol;

extern vector<symbol> sym_table;

void enter(string ename, string etype, int esize, int num);

void enter(string ename, string etype, int esize, int num, string conten);

int lookup(string findn);

void print();


#endif //COMPILE_SYMTABLE_H
