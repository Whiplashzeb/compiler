//
// Created by 赵恩博 on 16/5/1.
//

#include "symtable.h"
#include <fstream>

vector<symbol> sym_table;
vector<string> string_list;

void enter(string ename, string etype, int esize, int num) {
    symbol tp;
    tp.name = ename;
    tp.type = etype;
    tp.size = esize;
    tp.num = num;
    sym_table.push_back(tp);
}

void enter(string ename, string etype, int esize, int num, string conten) {
    symbol tp;
    tp.name = ename;
    tp.type = etype;
    tp.size = esize;
    tp.num = num;
    tp.conte = conten;
    sym_table.push_back(tp);
}

int lookup(string findn) {
    for (int k = 0; k < sym_table.size(); k++) {
        if (findn == sym_table[k].name)
            return k;
    }
    return -1;
}

void print() {
    fstream out("/Users/jinyiyexing/Documents/c++/compile/symble.txt", ios::out);
    for (int i = 0; i < sym_table.size(); i++) {
        out << sym_table[i].name << ' ' << sym_table[i].type << ' ' << sym_table[i].conte << ' ' << sym_table[i].size <<
        ' ' << sym_table[i].num << endl;
    }
}
