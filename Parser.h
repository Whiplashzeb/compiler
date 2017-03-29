//
// Created by 赵恩博 on 16/5/1.
//

#ifndef COMPILE_PARSER_H
#define COMPILE_PARSER_H

#define STATENUM 122
#define ENDNUM 35
#define NONENDNUM 24

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stack>

using namespace std;

typedef struct act {
    char action;
    int state;
} actions;

typedef struct red {
    vector<string> tokenlist;
    int length;
} reduce;//产生式

class parse {
public:
    parse();

    void init();

    string ignorelabel(string str);

    void readlalr();

    void readproduction();

    int tranto(string source);

private:
    stack<string> anly;
    stack<int> state;
    vector<reduce> reducelist;//保存全部产生式
    actions action[STATENUM][ENDNUM];
    int go_to[STATENUM][NONENDNUM];
};

#endif

