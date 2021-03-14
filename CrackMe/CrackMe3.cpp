#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<windows.h>
#include <vector>

int main();
char input[10];
int flag = 0;

EXCEPTION_DISPOSITION excep_handler(
	EXCEPTION_RECORD *pExcepRec,
	void *pFrame,//EXCEPTION_REGISTRATION *pFrame,
	CONTEXT *pCtx,
	void *pValue)
{
	if (input[2] == 's')flag++;
	pCtx->Eip += 1;
	return ExceptionContinueExecution;
}


DWORD WINAPI threadFunc(LPVOID vdParam)
{
	LPVOID p = main;
	while (1) {
		if (*(LPBYTE)p == 0xCC) {
			DWORD dwOldProtect;
			VirtualProtect(p, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect);
			*(LPBYTE)p = 0x90;
		}
		p=(LPBYTE)p+1;
		Sleep(10);
	}

	return 0;
}

int main()
{
	puts("ENTER PASS");

	scanf("%s",input);

	if (input[0] == 'T')flag++;
	if (input[3] == 0)flag++;
	if (input[1] == 'L')flag++;


	__asm {
		
		push offset excep_handler
		push FS:[0]
		mov FS:[0],ESP
		
		__emit 0xCC

		add esp,8
	}
	if (flag == 4)puts("Correct");
	else puts("Wrong");
	getchar();
	getchar();
	return 0;
}


/* start of Adding TLS Callback */
__declspec(thread) std::vector<int>* vec_tls;
void __stdcall tls_callback(void*, DWORD dwReason, void*)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DWORD dwID;
		HANDLE hThread;
		hThread = CreateThread(NULL, 0, threadFunc, NULL, 0, &dwID);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		vec_tls = new std::vector<int>;
		break;
	case DLL_THREAD_DETACH:
		delete vec_tls;
		break;
	}
}
#pragma section(".CRT$XLB",long,read)
extern "C" __declspec(allocate(".CRT$XLB"))
PIMAGE_TLS_CALLBACK _xl_b = tls_callback;
/* end of Adding TLS Callback */