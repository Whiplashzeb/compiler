//
// Created by 赵恩博 on 16/5/1.
//

#include "Parser.h"
#include "lex.h"
#include "symtable.h"
#include "semantic.h"

extern vector<string> string_list;

void parse::init() {
    state.push(0);
    anly.push("#");
}

parse::parse() {
    fstream out("/Users/jinyiyexing/Documents/c++/compile/parse.txt",ios_base::out);
    string tmp, deft, beftmp;
    int i = 0, k, s, r, ts;
    readproduction();
    readlalr();
    init();
    //词法分析
    vector<token> *table;
    table = lex();
    vector<token>::iterator itr = table->begin();
    while (i < table->size()) {
        tmp.assign((itr + i)->kind.begin(), (itr + i)->kind.end());
        s = state.top();
        r = (itr + i)->value;
        if (action[s][r].action == 's') {
            state.push(action[s][r].state);
            anly.push(tmp);
            i++;
        }
        else if (action[s][r].action == 'r') {
            beftmp = anly.top();
            for (k = 0; k < reducelist[(action[s][r].state)].length; k++) {
                string_list.push_back(anly.top());
                state.pop();
                anly.pop();
            }
            deft = reducelist[(action[s][r].state)].tokenlist[0];
            anly.push(deft);
            int def = tranto(deft);
            ts = state.top();
            state.push((go_to[ts][def]));
            out << (action[s][r].state) << ":" << endl;
            out << reducelist[(action[s][r].state)].tokenlist[0] << " => ";
            int te;
            for (te = 1; te < reducelist[(action[s][r].state)].tokenlist.size() - 1; te++)
                out << reducelist[(action[s][r].state)].tokenlist[te] << " ";
            out << reducelist[(action[s][r].state)].tokenlist[te];
            out << endl;
            //out << "传进的参数：" << beftmp << endl;
            sem_anly(action[s][r].state, beftmp);
        }
        else if (action[s][r].action == 'a') {
            cout << "succeed!" << endl;
            break;
        }
        else {
            cout << "get parser error" << endl;
            exit(1);
        }
    }
}

//去除HTM标签
string parse::ignorelabel(string str) {
    int j;
    j = str.find(">");
    str = str.substr(j + 1, str.size() - j - 1);
    j = str.find("<");
    str = str.substr(0, j);
    return str;
}

//读htm文件，产生goto表和action表
void parse::readlalr() {
    ifstream fin;
    string str;
    fin.open("/Users/jinyiyexing/Documents/c++/compile/lalr.txt", ios_base::in);
    if (!fin.is_open()) {
        cout << "Open lalr.txt Faild" << endl;
        exit(1);
    }
    for (int i = 0; i < STATENUM; i++) {
        getline(fin, str);
        getline(fin, str);
        int temp;
        for (int j = 0; j < ENDNUM; j++) {
            getline(fin, str);
            str = ignorelabel(str);
            if (str[0] == 's') {
                action[i][j].action = 's';
                temp = str.find(';');
                action[i][j].state = atoi(str.substr(temp + 1, str.size() - temp - 1).c_str());
            }
            else if (str[0] == 'r') {
                int x, y;
                bool rightnull = false;
                string tempstr;
                vector<string> rightlist;
                rightlist.clear();
                action[i][j].action = 'r';
                temp = str.find(";");//去掉reduce
                x = temp + 1;
                y = x;
                while (isalpha(str[y]) || str[y] == '_')
                    y++;
                rightlist.push_back(str.substr(x, y - x));
                temp = str.find("->");
                if (!isalpha(str[temp + 8]))//空产生式
                {
                    rightnull = true;
                }
                else {
                    y = temp + 8;
                    x = y;
                    while (y < str.size()) {
                        while (str[y] != '&' && y < str.size())
                            y++;
                        tempstr = str.substr(x, y - x);
                        rightlist.push_back(tempstr);
                        while (str[y] != ';' && y < str.size())
                            y++;
                        y++;
                        x = y;
                    }
                }
                for (int k = 0; k < reducelist.size(); k++) {
                    if (rightlist[0].compare(reducelist[k].tokenlist[0]) == 0) {
                        if (rightnull == true && reducelist[k].tokenlist.size() == 1) {
                            action[i][j].state = k;
                            break;
                        }
                        else if (rightlist.size() == reducelist[k].tokenlist.size()) {
                            int l;
                            for (l = 1; l < rightlist.size(); l++) {
                                if (rightlist[l].compare(reducelist[k].tokenlist[l]) != 0)
                                    break;
                            }
                            if (l == rightlist.size()) {
                                action[i][j].state = k;
                                break;
                            }
                        }
                    }
                }
                rightlist.clear();
            }
            else if (str[0] == 'a') {
                action[i][j].state = -1;
                action[i][j].action = 'a';
            }
        }
        for (int j = 0; j < NONENDNUM; j++) {
            getline(fin, str);
            str = ignorelabel(str);
            if (str[0] == '&')
                go_to[i][j] = -1;
            else
                go_to[i][j] = atoi(str.c_str());
        }
        getline(fin, str);
    }
    fin.close();
}

/**读产生式*/
void parse::readproduction() {
    ifstream fin;
    string str;
    reduce r;
    fin.open("/Users/jinyiyexing/Documents/c++/compile/production.txt", ios_base::in);
    if (!fin.is_open()) {
        cout << "Open production.txt Faild" << endl;
        exit(1);
    }
    while (getline(fin, str)) {
        int len = str.length();
        int num = 0;
        int x = 0, y = 0;
        string tempstr;
        while (y < len && str[y] != ';') {
            while (isspace(str[y]) && y < len)
                y++;
            if (y == len) {
                return;
            }
            x = y;
            while (isalpha(str[y]) || str[y] == '_')
                y++;
            r.tokenlist.push_back(str.substr(x, y - x));//添加产生式头部
            while (isspace(str[y]) && y < len)
                y++;
            if (str[y] == '=' && str[y + 1] == '>')
                y += 2;
            while (isspace(str[y]) && y < len)
                y++;
            while (y < len && str[y] != ';') {
                x = y;
                while (isalpha(str[y]) || str[y] == '_')
                    y++;
                tempstr = str.substr(x, y - x);
                r.tokenlist.push_back(tempstr);
                num++;
                while (isspace(str[y]) && y < len)
                    y++;
            }
        }
        r.length = num;
        reducelist.push_back(r);
        r.tokenlist.clear();
    }
    fin.close();
}

int parse::tranto(string source) {
    if (source == "start")
        return 0;
    else if (source == "statement")
        return 1;
    else if (source == "while_statement")
        return 2;
    else if (source == "if_statement")
        return 3;
    else if (source == "for_statement")
        return 4;
    else if (source == "compound_statement")
        return 5;
    else if (source == "block_item_list")
        return 6;
    else if (source == "primary_expression")
        return 7;
    else if (source == "postfix_expression")
        return 8;
    else if (source == "multiplication_expression")
        return 9;
    else if (source == "additive_expression")
        return 10;
    else if (source == "relational_expression")
        return 11;
    else if (source == "expression")
        return 12;
    else if (source == "assignment_expression")
        return 13;
    else if (source == "string_literal")
        return 14;
    else if (source == "declaration")
        return 15;
    else if (source == "init_declarator")
        return 16;
    else if (source == "init_declarator_list")
        return 17;
    else if (source == "array_initializer")
        return 18;
    else if (source == "initializer_list")
        return 19;
    else if (source == "logical_AND_expression")
        return 20;
    else if (source == "logical_OR_expression")
        return 21;
    else if (source == "out_paralist")
        return 22;
    else if (source == "out_statement")
        return 23;

}
/*
#define start 34
#define statement 35
#define while_statement 36
#define if_statement 37
#define for_statement 38
#define compound_statement 39
#define block_item_list 40
#define primary_expression 41
#define postfix_expression 42
#define multiplication_expression 43
#define additive_expression 44
#define relational_expression 45
#define expression 46
#define assignment_expression 47
#define string_literal 48
#define declaration 49
#define init_declarator 50
#define init_declarator_list 51
#define array_initializer 52
#define initializer_list 53
#define logical_AND_expression 54
#define logical_OR_expression 55
#define out_paralist 56
#define out_statement 57
*/


