#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include<stdio.h>

#define EMIT(a) __asm __emit (a)
#define X64_Start_with_CS(_cs) \
        { \
        EMIT(0x6A) EMIT(_cs)                         /*  push   _cs             */ \
        EMIT(0xE8) EMIT(0) EMIT(0) EMIT(0) EMIT(0)   /*  call   $+5             */ \
        EMIT(0x83) EMIT(4) EMIT(0x24) EMIT(5)        /*  add    dword [esp], 5  */ \
        EMIT(0xCB)                                   /*  retf                   */ \
        }
#define X64_End_with_CS(_cs) \
        { \
        EMIT(0xE8) EMIT(0) EMIT(0) EMIT(0) EMIT(0)                                 /*  call   $+5                   */ \
        EMIT(0xC7) EMIT(0x44) EMIT(0x24) EMIT(4) EMIT(_cs) EMIT(0) EMIT(0) EMIT(0) /*  mov    dword [rsp + 4], _cs  */ \
        EMIT(0x83) EMIT(4) EMIT(0x24) EMIT(0xD)                                    /*  add    dword [rsp], 0xD      */ \
        EMIT(0xCB)                                                                 /*  retf                         */ \
        }
#define X64_Start() X64_Start_with_CS(0x33)
#define X64_End() X64_End_with_CS(0x23)
//T{Z<Y
char pass[10];
int flag=0;
int threadF = 0;


void DebugSelf(char *argv)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	GetStartupInfo(&si);
    char cmd[100] = {};
    strcat(cmd, argv);
    strcat(cmd," 2");
    CreateProcess(NULL,cmd, NULL, NULL, FALSE,
		DEBUG_PROCESS, NULL, NULL, &si, &pi);
    
    DEBUG_EVENT de;
   
    while (1) {
        WaitForDebugEvent(&de, INFINITE);
        switch (de.dwDebugEventCode)
        {
            case EXIT_PROCESS_DEBUG_EVENT:
                return;
                break;
            default:
                ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
                break;
        }
    }
}

void GetPass()
{
    puts("Search correct PASS");
    puts("Enter PASS");
    scanf("%s", pass);
}

void Judge()
{
    Sleep(1000);
    if (flag) {
        puts("Correct");
    }
    else {
        puts("Wrong");
    }
}

void HeavensGate()
{
    __asm {
        pushad
        xor eax,eax
        xor ebx,ebx
        xor ecx,ecx
        xor edx,edx
        mov al,pass[0]
        mov bl,pass[1]
        mov cl,pass[2]
        mov dl,pass[3]
    }

    X64_Start();

    __asm {
        dec eax
        add eax, ebx
        dec eax
        cmp eax, 207
        jne mis
        dec eax
        sub eax, ebx
        dec eax
        add eax, eax
        dec eax
        sub eax, ebx
        dec eax
        cmp eax, 45
        jne mis
        dec eax
        sub ecx, edx
        dec eax
        cmp ecx, 30
        jne mis
        dec eax
        add ecx, edx
        dec eax
        add ecx, ecx
        dec eax
        add ecx, edx
        dec eax
        cmp ecx, 240
        jne mis
        dec eax
        xor eax,eax
        dec eax
        EMIT(0xFF) EMIT(0xC0)
        jmp ok
        mis:
        dec eax
        xor eax, eax
        ok:
    }
    X64_End();
    __asm {
        xor ebx,ebx
        mov bl,pass[5]
        cmp ebx,0
        je ok2
        xor eax,eax
        ok2:
        mov threadF,eax
        popad
    }
}

DWORD WINAPI threadFunc(LPVOID vdParam)
{
    while (!threadF) {
    }
    if (pass[4] == 'Y') {
        flag = 1;
    }
    return 0;
}

void startThread()
{
    DWORD dwID;
    HANDLE hThread = NULL;
    hThread = CreateThread(NULL, 0, threadFunc, NULL, 0, &dwID);
}

void Child()
{
    startThread();
    GetPass();
    HeavensGate();
    Judge();
    getchar();
    getchar();
}

int main(int argc,char **argv)
{
    if (argc == 2) {
        Child();
    }else{
        DebugSelf(argv[0]);
    }
	return 0;
}