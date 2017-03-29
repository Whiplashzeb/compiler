//
// Created by 赵恩博 on 16/5/1.
//

#include "semantic.h"
#include "symtable.h"
#include <sstream>
#include <stdio.h>

bool eaxused = false;
vector<string> priority;
int arraysize = 0;
int area = 0;
int printf_size = 0;
extern vector<string> string_list;
stack<node> nodelist;

void sem_anly(int index, string name) {
    FILE *fp;
    if ((fp = fopen("/Users/jinyiyexing/Documents/c++/compile/test.asm", "w")) == NULL) {
        cout << "can't open file" << endl;
        exit(1);
    }
    stringstream ss;
    string stp1, stp2, stp, content;
    int k, kt, symindex;
    node nodetmp;
    node nodetmp1, nodetmp2, nodetmp3, nodetmp4;
    switch (index) {
        case 0:///start => MAIN LR_BRAC RR_BRAC compound_statement
            print();
            if (nodelist.size()) {
                cout << nodelist.top().code << endl;
                content = content + ".686P\n";
                content = content + ".MODEL flat, stdcall\n";
                content = content + ".STACK 4096\n";
                content = content + "option casemap:none\n";
                content = content + "\n";
                content = content + "printf          PROTO C :dword,:vararg\n";
                content = content + "ExitProcess	PROTO :DWORD\n";
                content = content + "\n";
                content = content + "INCLUDELIB C:\\Irvine\\USER32.LIB\n";
                content = content + "INCLUDELIB C:\\Irvine\\KERNEL32.LIB\n";
                content = content + "INCLUDELIB C:\\Irvine\\MSVCRT.LIB\n";
                content = content + "\n";
                content = content + "exit equ <INVOKE ExitProcess,0>\n";
                content = content + "\n";
                content = content + "chr$ MACRO any_text:vararg\n";
                content = content + "	LOCAL textname\n";
                content = content + ".data\n";
                content = content + "	textname db any_text,0\n";
                content = content + "	ALIGN 4\n";
                content = content + ".code\n";
                content = content + "	EXITM<OFFSET textname>\n";
                content = content + "ENDM\n";
                content = content + "\n";
                content = content + ".data\n";
                for (int j = 0; j < sym_table.size(); j++) {
                    if (sym_table[j].type == "int") {
                        content = content + sym_table[j].name + " dword ?\n";
                    }
                    else if (sym_table[j].type == "array") {
                        ss << sym_table[j].size * sym_table[j].num;
                        ss >> stp1;
                        ss.clear();
                        content = content + sym_table[j].name + " dword " + stp1 + " dup(?)\n";
                    }
                    else if (sym_table[j].type == "string") {
                        content = content + sym_table[j].name + " byte \"" + sym_table[j].conte + "\",0\n";
                    }
                }
                content = content + "\n.code\nmain PROC" + nodelist.top().code + "\nexit\nmain ENDP\nEND main";
                fputs((content.c_str()), fp);
            }
            else
                cout << "no this situation!" << endl;
            break;
        case 1:///statement => compound_statement
            break;
        case 2:///statement => expression SEMIC
            break;
        case 3:///statement => if_statement
            break;
        case 4:///statement => while_statement
            break;
        case 5:///statement => for_statement
            break;
        case 6:///statement => declaration
            break;
        case 7:///statement => out_statement
            break;
        case 8:///while_statement => WHILE LR_BRAC expression RR_BRAC statement
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            ss << area;
            ss >> stp;
            ss.clear();
            ss << area - 1;
            ss >> stp1;
            ss.clear();
            nodetmp.code = "jmp L" + stp1 + "\nL" + stp + ":\n" + nodetmp1.code + "\n" + nodetmp2.code;
            area++;
            nodelist.push(nodetmp);
            break;
        case 9:///for_statement => FOR LR_BRAC expression SEMIC expression SEMIC expression RR_BRAC statement
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp3 = nodelist.top();
            nodelist.pop();
            nodetmp4 = nodelist.top();
            nodelist.pop();
            ss << area;
            ss >> stp;
            ss.clear();
            ss << area - 1;
            ss >> stp1;
            ss.clear();
            nodetmp.code = nodetmp4.code + "\njmp L" + stp1 + "\n" + "\nL" + stp + ":";
            area++;
            nodetmp.code = nodetmp.code + "\n" + nodetmp1.code + "\n" + nodetmp2.code + "\n" + nodetmp3.code;
            nodelist.push(nodetmp);
            break;
        case 10:///if_statement => IF LR_BRAC expression RR_BRAC  statement
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            ss << area;
            ss >> stp;
            ss.clear();
            ss << area - 1;
            ss >> stp1;
            ss.clear();
            ss << area + 1;
            ss >> stp2;
            ss.clear();
            nodetmp.code = "jmp L" + stp1 + "\nL" + stp + ":\n" + nodetmp1.code + "\n" + "jmp L" + stp2 + "\n" +
                           nodetmp2.code + "\nL" + stp2 + ":";
            area += 2;
            nodelist.push(nodetmp);
            break;
        case 11:///if_statement => IF LR_BRAC expression RR_BRAC  statement ELSE statement
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp3 = nodelist.top();
            nodelist.pop();
            ss << area;
            ss >> stp;
            ss.clear();
            ss << area - 1;
            ss >> stp1;
            ss.clear();
            ss << area + 1;
            ss >> stp2;
            ss.clear();
            nodetmp.code = "jmp L" + stp1 + "\nL" + stp + ":\n" + nodetmp2.code + "\n" + "jmp L" + stp2 + "\n" +
                           nodetmp3.code + "\n" + nodetmp1.code + "\nL" + stp2 + ":";
            area += 2;
            nodelist.push(nodetmp);
            break;
        case 12:///compound_statement => LB_BRAC block_item_list RB_BRAC
            break;
        case 13:///block_item_list => statement
            break;
        case 14:///block_item_list => block_item_list statement
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + "\n" + nodetmp1.code;
            nodetmp.isID = false;
            nodetmp.isdig = false;
            nodetmp.isreg = false;
            nodelist.push(nodetmp);
            break;
        case 15:///primary_expression => ID
            symindex = lookup(name);
            if (symindex != -1) {
                nodetmp.code = "";
                nodetmp.result = name;
                nodetmp.isID = true;
                nodetmp.isdig = false;
                nodetmp.isreg = false;
                nodetmp.isregID = false;
                nodelist.push(nodetmp);
            }
            else {
                cout << "no definition of '" << name << "'" << endl;
                exit(1);
            }
            break;
        case 16:///primary_expression => ID LS_BRAC expression RS_BRAC???????????????????????????????????????
            nodetmp1 = nodelist.top();
            nodelist.pop();
            k = string_list.size();
            symindex = lookup(string_list[k - 1]);
            if (symindex == -1) {
                cout << "no definition of array of '" << string_list[k - 1] << "'" << endl;
                exit(1);
            }
            ss << atoi((nodetmp1.result).c_str()) * 4;
            ss >> stp1;
            ss.clear();
            ss << nodetmp1.result;
            ss >> stp2;
            ss.clear();
            if (nodetmp1.isdig) {
                nodetmp.result = string_list[k - 1] + "+" + stp1;
                nodetmp.isID = true;
                nodetmp.isdig = false;
                nodetmp.isreg = false;
                nodetmp.isregID = false;
            }
            else if (nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\nmov eax, [" + nodetmp1.result + "]";
                nodetmp.code = nodetmp.code + "\nmov ecx, 4";
                nodetmp.code = nodetmp.code + "\nmul ecx";
                nodetmp.code = nodetmp.code + "\nadd eax, offset " + string_list[k - 1];
                nodetmp.isID = false;
                nodetmp.isdig = false;
                nodetmp.isreg = false;
                nodetmp.isregID = true;
            }
            else if (nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\nmov ecx, 4";
                nodetmp.code = nodetmp.code + "\nmul ecx";
                nodetmp.code = nodetmp.code + "\nadd eax, offset " + string_list[k - 1];
                nodetmp.isID = false;
                nodetmp.isdig = false;
                nodetmp.isreg = false;
                nodetmp.isregID = true;
            }
            nodetmp.code = nodetmp1.code + nodetmp.code;
            nodelist.push(nodetmp);
            break;
        case 19:///postfix_expression => DIG
            nodetmp.code = "";
            nodetmp.result = name;
            nodetmp.isID = false;
            nodetmp.isdig = true;
            nodetmp.isreg = false;
            nodetmp.isregID = false;
            nodelist.push(nodetmp);
            break;
        case 20:///postfix_expression => primary_expression PLUSPLUS
            nodetmp1 = nodelist.top();
            if (nodetmp1.isdig) {
                cout << "dig can't put left of MINUSMINUS" << endl;
                exit(1);
            }
            else if (nodetmp1.isID) {
                stp2 = stp2 + "add [" + nodetmp1.result + "], 1";
                priority.push_back(stp2);
            }
            else if (nodetmp1.isreg) {
                cout << "reg can't put left of MINUSMINUS" << endl;
                exit(1);
            }
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp = nodetmp2;
            if (priority.size()) {
                for (int j = 0; j < priority.size(); j++) {
                    nodetmp.code = nodetmp.code + "\n" + priority[j];
                }
            }
            priority.clear();
            nodelist.push(nodetmp);
            break;
        case 21:///postfix_expression => primary_expression MINUSMINUS
            nodetmp1 = nodelist.top();
            if (nodetmp1.isdig) {
                cout << "dig can't put left of MINUSMINUS" << endl;
                exit(1);
            }
            else if (nodetmp1.isID) {
                stp2 = stp2 + "sub [" + nodetmp1.result + "], 1";
                priority.push_back(stp2);
            }
            else if (nodetmp1.isreg) {
                cout << "reg can't put left of MINUSMINUS" << endl;
                exit(1);
            }
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp = nodetmp2;
            if (priority.size()) {
                for (int j = 0; j < priority.size(); j++) {
                    nodetmp.code = nodetmp.code + "\n" + priority[j];
                }
            }
            priority.clear();
            nodelist.push(nodetmp);
            break;
        case 22:///multiplication_expression => postfix_expression
            break;
        case 23:///multiplication_expression => multiplication_expression MULTI postfix_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            if (nodetmp2.isdig && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = nodetmp.code + "push eax\n";
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "mul ecx";
            }
            else if (nodetmp2.isdig && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "mul [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isdig && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "mul ecx";
            }
            else if (nodetmp2.isdig && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "mul ecx";
            }
            else if (nodetmp2.isID && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "mul ecx";
            }
            else if (nodetmp2.isID && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "mul [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mul [" + nodetmp2.result + "]";
            }
            else if (nodetmp2.isID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "mul [" + nodetmp2.result + "]";
            }
            else if (nodetmp2.isreg && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "mul ecx";
            }
            else if (nodetmp2.isreg && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "mul [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isreg && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "mul ebx";
            }
            else if (nodetmp2.isreg && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "mul ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "mul ecx";
            }
            else if (nodetmp2.isregID && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "mul [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isregID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "mul ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "mul ebx";
            }
            nodetmp.isID = false;
            nodetmp.isdig = false;
            nodetmp.isreg = true;
            nodetmp.isregID = false;
            nodelist.push(nodetmp);
            break;
        case 24:///multiplication_expression => multiplication_expression DIV postfix_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            if (nodetmp2.isdig && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "div ecx";
            }
            else if (nodetmp2.isdig && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "div [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isdig && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            else if (nodetmp2.isdig && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            else if (nodetmp2.isID && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "div ecx";
            }
            else if (nodetmp2.isID && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "div [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            else if (nodetmp2.isID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            else if (nodetmp2.isreg && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "div ecx";
            }
            else if (nodetmp2.isreg && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "div [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isreg && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            else if (nodetmp2.isreg && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ecx, " + nodetmp1.result;
                nodetmp.code = nodetmp.code + "\n" + "div ecx";
            }
            else if (nodetmp2.isregID && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "div [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isregID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "pop ebx";
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "pop ebx";
                nodetmp.code = nodetmp.code + "\n" + "div ebx";
            }
            nodetmp.isID = false;
            nodetmp.isdig = false;
            nodetmp.isreg = true;
            nodetmp.isregID = false;
            nodelist.push(nodetmp);
            break;
        case 25:///additive_expression => multiplication_expression
            break;
        case 26:///additive_expression => additive_expression PLUS multiplication_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            if (nodetmp2.isdig && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "add eax, " + nodetmp1.result;
            }
            else if (nodetmp2.isdig && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "add eax, [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isdig && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "add eax, " + nodetmp2.result;
            }
            else if (nodetmp2.isdig && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "add eax, " + nodetmp2.result;
            }
            else if (nodetmp2.isID && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "add eax, " + nodetmp1.result;
            }
            else if (nodetmp2.isID && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eax" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "add eax, [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "add eax, [" + nodetmp2.result + "]";
            }
            else if (nodetmp2.isID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "add eax, [" + nodetmp2.result + "]";
            }
            else if (nodetmp2.isreg && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "add eax, " + nodetmp1.result;
            }
            else if (nodetmp2.isreg && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "add eax, [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isreg && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "add eax, ebx";
            }
            else if (nodetmp2.isreg && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "add eax, ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "add " + nodetmp1.result;
            }
            else if (nodetmp2.isregID && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "add [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isregID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "add ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "add ebx";
            }
            nodetmp.isID = false;
            nodetmp.isdig = false;
            nodetmp.isreg = true;
            nodetmp.isregID = false;
            nodelist.push(nodetmp);
            break;
        case 27:///additive_expression => additive_expression MINUS multiplication_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            if (nodetmp2.isdig && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = "\npush eaxsub" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "sub eax, " + nodetmp1.result;
            }
            else if (nodetmp2.isdig && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eaxsub" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "sub eax, [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isdig && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            else if (nodetmp2.isdig && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, " + nodetmp2.result;
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            else if (nodetmp2.isID && nodetmp1.isdig) {
                if (eaxused)
                    nodetmp.code = "\npush eaxsub" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, " + nodetmp1.result;
            }
            else if (nodetmp2.isID && nodetmp1.isID) {
                if (eaxused)
                    nodetmp.code = "\npush eaxsub" + nodetmp.code;
                eaxused = true;
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            else if (nodetmp2.isID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp2.result + "]";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            else if (nodetmp2.isreg && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "sub eax, " + nodetmp1.result;
            }
            else if (nodetmp2.isreg && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "sub eax, [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isreg && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            else if (nodetmp2.isreg && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isdig) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, " + nodetmp1.result;
            }
            else if (nodetmp2.isregID && nodetmp1.isID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, [ebx]";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, [" + nodetmp1.result + "]";
            }
            else if (nodetmp2.isregID && nodetmp1.isreg) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "pop ebx";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            else if (nodetmp2.isregID && nodetmp1.isregID) {
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "pop eax";
                nodetmp.code = nodetmp.code + "\n" + "push ebx";
                nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                nodetmp.code = nodetmp.code + "\n" + "pop ebx";
                nodetmp.code = nodetmp.code + "\n" + "sub eax, ebx";
            }
            nodetmp.isID = false;
            nodetmp.isdig = false;
            nodetmp.isreg = true;
            nodetmp.isregID = false;
            nodelist.push(nodetmp);
            break;
        case 28:///relational_expression => additive_expression
            break;
        case 29:///relational_expression => relational_expression LT additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            ss << area;
            ss >> stp;
            ss.clear();
            if (nodetmp2.isID) {
                if (nodetmp1.isdig) {
                    nodetmp.code = nodetmp.code + "L" + stp + ":";
                    area++;
                    nodetmp.code = nodetmp.code + "\n" + "cmp [" + nodetmp2.result + "], " + nodetmp1.result;
                    ss << area;
                    ss >> stp;
                    ss.clear();
                    nodetmp.code = nodetmp.code + "\n" + "jl L" + stp;
                }
            }
            nodelist.push(nodetmp);
            break;
        case 30:///relational_expression => relational_expression RT additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            ss << area;
            ss >> stp;
            ss.clear();
            if (nodetmp2.isID) {
                if (nodetmp1.isdig) {
                    nodetmp.code = nodetmp.code + "L" + stp + ":";
                    area++;
                    nodetmp.code = nodetmp.code + "\n" + "cmp [" + nodetmp2.result + "], " + nodetmp1.result;
                    ss << area;
                    ss >> stp;
                    ss.clear();
                    nodetmp.code = nodetmp.code + "\n" + "jg L" + stp;
                }
            }
            nodelist.push(nodetmp);
            break;
        case 31:///relational_expression => relational_expression LQ additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            ss << area;
            ss >> stp;
            ss.clear();
            if (nodetmp2.isID) {
                if (nodetmp1.isdig) {
                    nodetmp.code = nodetmp.code + "L" + stp + ":";
                    area++;
                    nodetmp.code = nodetmp.code + "\n" + "cmp [" + nodetmp2.result + "], " + nodetmp1.result;
                    ss << area;
                    ss >> stp;
                    ss.clear();
                    nodetmp.code = nodetmp.code + "\n" + "jng L" + stp;
                }
            }
            nodelist.push(nodetmp);
            break;
        case 32:///relational_expression => relational_expression RQ additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            ss << area;
            ss >> stp;
            ss.clear();
            if (nodetmp2.isID) {
                if (nodetmp1.isdig) {
                    nodetmp.code = nodetmp.code + "L" + stp + ":";
                    area++;
                    nodetmp.code = nodetmp.code + "\n" + "cmp [" + nodetmp2.result + "], " + nodetmp1.result;
                    ss << area;
                    ss >> stp;
                    ss.clear();
                    nodetmp.code = nodetmp.code + "\n" + "jnl L" + stp;
                }
            }
            nodelist.push(nodetmp);
            break;
        case 33:///relational_expression => relational_expression EQEQ additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            /*ss << nodetmp1.result;
            ss >> stp1;
            ss.clear();
            ss << nodetmp2.result;
            ss >> stp2;
            ss.clear();*/
            ss << area;
            ss >> stp;
            ss.clear();
            if (nodetmp2.isID) {
                if (nodetmp1.isdig) {
                    nodetmp.code = nodetmp.code + "L" + stp + ":";
                    area++;
                    nodetmp.code = nodetmp.code + "\n" + "cmp [" + nodetmp2.result + "], " + nodetmp1.result;
                    ss << area;
                    ss >> stp;
                    ss.clear();
                    nodetmp.code = nodetmp.code + "\n" + "je L" + stp;
                }
            }
            nodelist.push(nodetmp);
            break;
        case 34:///relational_expression => relational_expression NEQ additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            ss << area;
            ss >> stp;
            ss.clear();
            if (nodetmp2.isID) {
                if (nodetmp1.isdig) {
                    nodetmp.code = nodetmp.code + "L" + stp + ":";
                    area++;
                    nodetmp.code = nodetmp.code + "\n" + "cmp [" + nodetmp2.result + "], " + nodetmp1.result;
                    ss << area;
                    ss >> stp;
                    ss.clear();
                    nodetmp.code = nodetmp.code + "\n" + "jne L" + stp;
                }
            }
            nodelist.push(nodetmp);
            break;
        case 35:///logical_AND_expression => relational_expression
            break;
        case 37:///logical_OR_expression => logical_AND_expression
            break;
        case 41:///assignment_expression => primary_expression EQ assignment_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp2.code + nodetmp1.code;
            /*ss << nodetmp1.result;
            ss >> stp1;
            ss.clear();
            ss << nodetmp2.result;
            ss >> stp2;
            ss.clear();*/
            if (nodetmp2.isID) {
                if (nodetmp1.isdig)
                    nodetmp.code = nodetmp.code + "\n" + "mov [" + nodetmp2.result + "], " + nodetmp1.result;
                else if (nodetmp1.isID) {
                    nodetmp.code = nodetmp.code + "\n" + "mov eax, [" + nodetmp1.result + "]";
                    nodetmp.code = nodetmp.code + "\n" + "mov [" + nodetmp2.result + "], eax";
                }
                else if (nodetmp1.isreg) {
                    nodetmp.code = nodetmp.code + "\n" + "mov [" + nodetmp2.result + "], eax";
                }
                else if (nodetmp1.isregID) {
                    nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                    nodetmp.code = nodetmp.code + "\n" + "mov eax, ebx";
                    nodetmp.code = nodetmp.code + "\n" + "mov [" + nodetmp2.result + "], eax";
                }
            }
            else if (nodetmp2.isreg) {
                cout << "reg can't put left of eq" << endl;
                exit(1);
            }
            else if (nodetmp2.isregID) {
                if (nodetmp1.isdig)
                    nodetmp.code = nodetmp.code + "\n" + "mov [eax], " + nodetmp1.result;
                else if (nodetmp1.isID) {

                    nodetmp.code = nodetmp.code + "\n" + "mov ebx, [" + nodetmp1.result + "]";
                    nodetmp.code = nodetmp.code + "\n" + "mov [eax], ebx";
                }
                else if (nodetmp1.isreg) {
                    nodetmp.code = nodetmp.code + "\n" + "mov ebx, eax";
                    nodetmp.code = nodetmp.code + "\n" + "pop eax";
                    nodetmp.code = nodetmp.code + "\n" + "mov [eax], ebx";
                }
                else if (nodetmp1.isregID) {
                    nodetmp.code = nodetmp.code + "\n" + "mov ebx, [eax]";
                    nodetmp.code = nodetmp.code + "\n" + "pop eax";
                    nodetmp.code = nodetmp.code + "\n" + "mov [eax], ebx";
                }
            }
            else if (nodetmp2.isdig) {
                cout << "dight can't put left of eq" << endl;
                exit(1);
            }
            nodetmp.code = nodetmp.code + "\n";
            nodetmp.isID = false;
            nodetmp.isdig = false;
            nodetmp.isreg = false;
            nodetmp.isregID = false;
            eaxused = false;
            nodelist.push(nodetmp);
            break;
        case 42:///assignment_expression => logical_OR_expression
            break;
        case 43://string_literal => DQ_MARKS STR DQ_MARKS
            k = string_list.size();
            ss << printf_size;
            ss >> stp1;
            stp1 = "printfof" + stp1;
            nodetmp.result = stp1;
            enter(stp1, "string", 8, 1, string_list[k - 2]);
            printf_size++;
            nodelist.push(nodetmp);
            break;
        case 44://out_statement => PRINT LR_BRAC string_literal out_paralist RR_BRAC SEMIC
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp1.code + "push offset " + nodetmp2.result + "\n";
            nodetmp.code = nodetmp.code + "call printf\n";
            nodelist.push(nodetmp);
            break;
        case 45://out_statement => PRINT LR_BRAC string_literal RR_BRAC SEMIC
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp.code = nodetmp.code + "push offset " + nodetmp1.result + "\n";
            nodetmp.code = nodetmp.code + "call printf\n";
            nodelist.push(nodetmp);
            break;
        case 46://out_paralist => COMMA additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            if (nodetmp1.isdig) {
                nodetmp.code = "mov ecx, " + nodetmp1.result + "\n";
                nodetmp.code = nodetmp.code + "push ecx\n";
            }
            else if (nodetmp1.isID) {
                nodetmp.code = "push [" + nodetmp1.result + "]\n";
            }
            else if (nodetmp1.isreg) {
                nodetmp.code = "push eax\n";
            }
            else if (nodetmp1.isregID) {
                nodetmp.code = "push [eax]\n";
            }
            nodetmp.code = nodetmp1.code + "\n" + nodetmp.code;
            nodelist.push(nodetmp);
            break;
        case 47://out_paralist => out_paralist COMMA additive_expression
            nodetmp1 = nodelist.top();
            nodelist.pop();
            nodetmp2 = nodelist.top();
            nodelist.pop();
            if (nodetmp1.isdig) {
                nodetmp.code = "mov ecx, " + nodetmp1.result + "\n";
                nodetmp.code = nodetmp.code + "push ecx\n";
            }
            else if (nodetmp1.isID) {
                nodetmp.code = "push [" + nodetmp1.result + "]\n";
            }
            else if (nodetmp1.isreg) {
                nodetmp.code = "push eax\n";
            }
            else if (nodetmp1.isregID) {
                nodetmp.code = "push [eax]\n";
            }
            nodetmp.code = nodetmp2.code + "\n" + nodetmp1.code + "\n" + nodetmp.code;
            break;
        case 48:///declaration => INT init_declarator_list SEMIC
            break;
        case 49:///init_declarator => ID;
            if (lookup(name) == -1)
                enter(name, "int", 4, 1);
            else {
                cout << "multiple definition of '" << name << "'" << endl;
                exit(1);
            }
            nodetmp.code = "";
            nodelist.push(nodetmp);
            break;
        case 50:///init_declarator => ID EQ DIG?
            k = string_list.size();
            symindex = lookup(string_list[k - 1]);
            if (symindex != -1) {
                cout << "multiple definition of '" << string_list[k - 1] << "'" << endl;
                exit(1);
            }
            enter(string_list[k - 1], "int", 4, 1);
            nodetmp.code = "";
            nodetmp.code = nodetmp.code + "\n" + "mov [" + string_list[k - 1] + "], " + string_list[k - 3];
            nodetmp.result = string_list[k - 1];
            nodetmp.isID = true;
            nodetmp.isdig = false;
            nodetmp.isreg = false;
            nodetmp.isregID = false;
            nodelist.push(nodetmp);
            break;
        case 51:///init_declarator => ID LS_BRAC DIG RS_BRAC EQ array_initializer
            k = string_list.size();
            symindex = lookup(string_list[k - 1]);
            if (symindex != -1) {
                cout << "multiple definition of '" << string_list[k - 1] << "'" << endl;
                exit(1);
            }
            if (atoi(string_list[k - 3].c_str()) < arraysize) {
                cout << "there is no enough data in array" << endl;
                exit(1);
            }
            enter(string_list[k - 1], "array", 4, atoi(string_list[k - 3].c_str()));
            kt = sym_table.size();
            for (int j = 0; j < arraysize; j++) {
                ss << (4 * (arraysize - j - 1));
                ss >> stp1;
                ss.clear();
                nodetmp.code =
                        "\nmov [" + string_list[k - 1] + "+" + stp1 + "], " + nodelist.top().result + nodetmp.code;
                nodelist.pop();
            }
            nodetmp.isID = true;
            nodetmp.isdig = false;
            nodetmp.isreg = false;
            nodelist.push(nodetmp);
            arraysize = 0;
            break;
        case 52:///init_declarator_list => init_declarator
            break;
        case 53:///init_declarator_list => init_declarator_list COMMA init_declarator
            stp1 = nodelist.top().code;
            nodelist.pop();
            stp2 = nodelist.top().code;
            nodelist.pop();
            nodetmp.code = stp2 + stp1;
            nodelist.push(nodetmp);
            break;
        case 54:///array_initializer => LB_BRAC initializer_list RB_BRAC
            break;
        case 55:///initializer_list => DIG
            arraysize++;
            nodetmp.code = "";
            nodetmp.result = name;
            nodetmp.isID = false;
            nodetmp.isdig = true;
            nodetmp.isreg = false;
            nodelist.push(nodetmp);
            break;
        case 56:///initializer_list => initializer_list COMMA DIG
            arraysize++;
            nodetmp.code = "";
            nodetmp.result = name;
            nodetmp.isID = false;
            nodetmp.isdig = true;
            nodetmp.isreg = false;
            nodelist.push(nodetmp);
            break;
        default:
            break;
    }
}
