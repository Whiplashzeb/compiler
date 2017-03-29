//
// Created by 赵恩博 on 16/5/1.
//

#ifndef COMPILE_SEMANTIC_H
#define COMPILE_SEMANTIC_H
#define NODEF -999999

#include <iostream>
#include <stdlib.h>
#include <stack>
#include <vector>

using namespace std;

typedef struct no {
    string code;
    string result;
    bool isreg;
    bool isdig;
    bool isID;
    bool isregID;
} node;

extern bool eaxused;
extern vector<string> priority;
extern int arraysize;
extern int area;
extern int printf_size;
extern stack<node> nodelist;

void sem_anly(int index, string name);

#endif

