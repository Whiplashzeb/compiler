//
// Created by 赵恩博 on 16/5/1.
//

#include "lex.h"

vector<token> *lex() {
    vector<token> *lextable = new vector<token>;
    token tmp;
    string line;
    ifstream infile("/Users/jinyiyexing/Documents/c++/compile/test.txt", ios::in);
    while (getline(infile, line)) {
        int first = 0, last = 0;
        while (last < line.length()) {
            tmp.kind.clear();
            while (isspace(line[first]))
                first++;
            last = first;
            //判断标识符和关键字
            if (isalpha(line[last]) || line[last] == '$') {
                while (isalnum(line[last]) || line[last] == '_')
                    last++;
                for (int i = first; i < last; i++)
                    tmp.kind.push_back(line[i]);
                string sample;
                sample.assign(tmp.kind.begin(), tmp.kind.end());
                if (sample == "and")
                    tmp.value = AND;
                else if (sample == "or")
                    tmp.value = OR;
                else if (sample == "while")
                    tmp.value = WHILE;
                else if (sample == "for")
                    tmp.value = FOR;
                else if (sample == "if")
                    tmp.value = IF;
                else if (sample == "else")
                    tmp.value = ELSE;
                else if (sample == "printf")
                    tmp.value = PRINT;
                else if (sample == "int")
                    tmp.value = INT;
                else if (sample == "main")
                    tmp.value = MAIN;
                else
                    tmp.value = ID;
            }
                //判断数字
            else if (isdigit(line[last])) {
                while (isdigit(line[last]))
                    last++;
                for (int i = first; i < last; i++)
                    tmp.kind.push_back(line[i]);
                tmp.value = DIG;
            }
                //运算符
            else if (line[last] == '+') {
                tmp.kind.push_back('+');
                last++;
                if (line[last] == '+') {
                    tmp.kind.push_back('+');
                    tmp.value = PLUSPLUS;
                    last++;
                }
                tmp.value = PLUS;
            }
            else if (line[last] == '-') {
                tmp.kind.push_back('-');
                last++;
                if (line[last] == '-') {
                    tmp.kind.push_back('-');
                    tmp.value = MINUSMINUS;
                    last++;
                }
                else
                    tmp.value = MINUS;
            }
            else if (line[last] == '*') {
                tmp.kind.push_back('*');
                last++;
                tmp.value = MULTI;
            }
            else if (line[last] == '/') {
                tmp.kind.push_back('/');
                last++;
                tmp.value = DIV;
            }
            else if (line[last] == '<') {
                tmp.kind.push_back('<');
                last++;
                if (line[last] == '=') {
                    tmp.kind.push_back('=');
                    tmp.value = LQ;
                    last++;
                }
                else
                    tmp.value = LT;
            }
            else if (line[last] == '>') {
                tmp.kind.push_back('>');
                last++;
                if (line[last] == '=') {
                    tmp.kind.push_back('=');
                    tmp.value = RQ;
                    last++;
                }
                else
                    tmp.value = RT;
            }
            else if (line[last] == '=') {
                tmp.kind.push_back('=');
                last++;
                if (line[last] == '=') {
                    tmp.kind.push_back('=');
                    tmp.value = EQEQ;
                    last++;
                }
                else
                    tmp.value = EQ;
            }
            else if (line[last] == '(') {
                tmp.kind.push_back('(');
                tmp.value = LR_BRAC;
                last++;
            }
            else if (line[last] == ')') {
                tmp.kind.push_back(')');
                tmp.value = RR_BRAC;
                last++;
            }
            else if (line[last] == '[') {
                tmp.kind.push_back('[');
                tmp.value = LS_BRAC;
                last++;
            }
            else if (line[last] == ']') {
                tmp.kind.push_back(']');
                tmp.value = RS_BRAC;
                last++;
            }
            else if (line[last] == '{') {
                tmp.kind.push_back('{');
                tmp.value = LB_BRAC;
                last++;
            }
            else if (line[last] == '}') {
                tmp.kind.push_back('}');
                tmp.value = RB_BRAC;
                last++;
            }
            else if (line[last] == '"') {
                tmp.kind.push_back('"');
                tmp.value = DQ_MARKS;
                lextable->push_back(tmp);
                tmp.kind.clear();
                last++;
                while (line[last] != '"') {
                    tmp.kind.push_back(line[last]);
                    last++;
                }
                tmp.value = STR;
                lextable->push_back(tmp);
                tmp.kind.clear();
                tmp.kind.push_back('"');
                tmp.value = DQ_MARKS;
                last++;
            }
            else if (line[last] == ';') {
                tmp.kind.push_back(';');
                tmp.value = SEMIC;
                last++;
            }
            else if (line[last] == ',') {
                tmp.kind.push_back(',');
                tmp.value = COMMA;
                last++;
            }
            else if (line[last] == '!') {
                tmp.kind.push_back('!');
                last++;
                if (line[last] == '=') {
                    tmp.kind.push_back('=');
                    tmp.value = NEQ;
                    last++;
                }
            }
            lextable->push_back(tmp);
            first = last;
        }
    }
    infile.close();
    fstream outfile("/Users/jinyiyexing/Documents/c++/compile/token.txt", ios::out);
    tmp.kind.clear();
    tmp.kind.push_back('$');
    tmp.value = $;
    lextable->push_back(tmp);
    for (auto it = lextable->begin(); it != lextable->end(); it++) {
        string out;
        out.assign(it->kind.begin(), it->kind.end());
        outfile << out << "\t" << it->value << endl;
    }
    outfile.close();
    return lextable;
}

