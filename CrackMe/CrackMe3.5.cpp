#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<windows.h>

char moji[100];
char f[10]="CORRECT";

void no()
{
	strcpy(f,"WRONG");
}

LONG WINAPI anti(PEXCEPTION_POINTERS p)
{
	SetUnhandledExceptionFilter(NULL);
	if (~moji[2]!=0xffffffad) {
		no();
	}
	p->ContextRecord->Eip += 2;
	return EXCEPTION_CONTINUE_EXECUTION;
}

void ANTI1()
{
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
	//anti1
	__try {
		__asm {
			__emit 0xCC
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		if ((moji[1] ^ 1) != 'J') {
			no();
		}
	}
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
}

void ANTI2()
{
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
	//anti2
	SetUnhandledExceptionFilter(anti);
	__asm {
		xor eax, eax
		div eax
	}
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
}

int main()
{
	puts("ENTER PASS");

	scanf("%s",moji);
	
	if (moji[0] != 'H') {
		no();
	}
	if (moji[3] != 0) {
		no();
	}
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
	ANTI1();
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
	ANTI2();
	__asm {
		__emit 0x90
		__emit 0x90
		__emit 0x90
	}
	/*
	LPVOID p = main;
	*(LPBYTE)p = 0xC3;
	*/

	printf(f);
	getchar();
	getchar();
	return 0;
}