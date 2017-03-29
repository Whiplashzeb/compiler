.686P
.MODEL flat, stdcall
.STACK 4096
option casemap:none

printf          PROTO C :dword,:vararg
ExitProcess	PROTO :DWORD

INCLUDELIB C:\Irvine\USER32.LIB
INCLUDELIB C:\Irvine\KERNEL32.LIB
INCLUDELIB C:\Irvine\MSVCRT.LIB

exit equ <INVOKE ExitProcess,0>

chr$ MACRO any_text:vararg
	LOCAL textname
.data
	textname db any_text,0
	ALIGN 4
.code
	EXITM<OFFSET textname>
ENDM

.data
a dword ?
printfof0 byte "haha\n",0

.code
main PROC
mov [a], 1
jmp L0
L1:
push offset printfof0
call printf

L0:
cmp [a], 1
je L1
exit
main ENDP
END main