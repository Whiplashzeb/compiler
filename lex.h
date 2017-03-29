//
// Created by 赵恩博 on 16/5/1.
//

#ifndef LEX_H
#define LEX_H

#define MAIN 0        // main
#define INT 1         // int
#define IF 2          // if
#define ELSE 3        // else
#define WHILE 4       // while
#define FOR 5         // for
#define PLUS 6        // +
#define MINUS 7       // -
#define MULTI 8       // *
#define DIV 9         // /
#define EQ 10         // =
#define LT 11         // <
#define RT 12         // >
#define LQ 13         // <=
#define RQ 14         // >=
#define EQEQ 15       // ==
#define LR_BRAC 16    // (
#define RR_BRAC 17    // )
#define LS_BRAC 18    // [
#define RS_BRAC 19    // ]
#define LB_BRAC 20    // {
#define RB_BRAC 21    // }
#define PLUSPLUS 22   // ++
#define MINUSMINUS 23 // --
#define SEMIC 24      // ;
#define COMMA 25      // ,
#define DQ_MARKS 26   // "
#define NEQ 27        // !=
#define PRINT 28     // printf
#define DIG 29        // 数字
#define ID 30         // 标识符
#define STR 31        // 字符串
#define AND 32        // 与
#define OR 33         // 或
#define $ 34

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

typedef struct token {
    vector<char> kind;
    int value;
} token;

vector<token> *lex();

#endif


