#include <windows.h>
#include<tchar.h>
#include<tlhelp32.h>
#include<stdio.h>
typedef struct injectionparam {
	TCHAR szTartExe[MAX_PATH];
} INJECTION_PARAM;

UINT InjectionThread(LPVOID pParam)
{
	INJECTION_PARAM* pInject = (INJECTION_PARAM*)pParam;
	BOOL bDetect = FALSE;

	while (1)
	{
		if (bDetect)
			break;

		HANDLE hProcessSnap = NULL;
		PROCESSENTRY32 pe32 = { 0, };

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hProcessSnap == INVALID_HANDLE_VALUE)
			return 0;

		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hProcessSnap, &pe32))
		{
			do
			{
				if (_strcmpi(pe32.szExeFile, pInject->szTartExe) == 0)
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
					if (hProcess)
					{
						MessageBox(NULL, TEXT("exe┌иa┌л▓l┌П┬Ь░■┌ф┌╣┌д≈^┌╕┌д│B\na=7<<2\n"), TEXT("┐q┐⌠┐g"), MB_OK);
						bDetect = TRUE;
					}
					CloseHandle(hProcess);
				}
			} while (Process32Next(hProcessSnap, &pe32));
		}

		CloseHandle(hProcessSnap);

		Sleep(500);
	}

	delete[] pInject;

	return 0;
}

void xorchar(char* str, int strnum, int key) {
	int i;
	for (i = 0; i < strnum; i++) {
		str[i] = (int)(str[i]) ^ key;
	}
}

int main(int argc,char *argv[])
{
	//
	char* fullPath = argv[0];
	char dir[1024] = { '\0' };
	char* dirEnd;
	dirEnd = strrchr(fullPath, '\\');
	for (int i = 0; i < (int)strlen(fullPath); i++) {
		dir[i] = fullPath[i];
		if (fullPath + i == dirEnd) {
			break;
		}
	}
	char deadpool[100];
	strcpy_s(deadpool,dirEnd+1);
	for (int i = 0; i <= strlen(deadpool); i++) {
		if (deadpool[i] >= 65 && deadpool[i ] <= 90)
			deadpool[i] = deadpool[i] + 32;
	}
	if (strcmp(deadpool, "deadpool.exe") != 0) {
		printf("I'm not %s!\nI'm superhero!\nI'm spiderman!!\n(It's a lie)",dirEnd+1);
		getchar();
		return 0;
	}
	//
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR target[1024];
	strcpy_s(target, dir);
	strcat_s(dir, _T("*.mp3"));
	hFind = FindFirstFile(dir, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
	else {
		puts("no music, no life");
		getchar();
		return 0;
	}
	
	//
	dirEnd = strrchr(target, '\\');
	*dirEnd = '\0';
	dirEnd = strrchr(target, '\\');
	if (strcmp(dirEnd + 1, "Hawaii") != 0) {
		puts("I wanna go to Hawaii");
		getchar();
		return 0;
	}

	//
	INJECTION_PARAM* pParam = new INJECTION_PARAM;
	TCHAR tarExe[] = TEXT("notepad.exe");
	if (argv[1] == NULL) {
		puts("└H└p└│└┘└┐└└└y└└└▌ └A└|└─└{└~└─└└");
		strcpy_s(pParam->szTartExe, tarExe);
		InjectionThread(pParam);
	}
	


	char flag[] = "GM@F^qsnbdrrллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл@[Ё▌├";// "FLAG_process";
	xorchar(flag, sizeof(flag), 1);
	if (argv[1] != NULL) {
		if (atoi(argv[1]) == 28) {
			MessageBox(NULL, TEXT(flag), TEXT("┐N┐┼┐A┌е┌╥│I"), MB_OK);
		}
		else {
			puts("not correct");
		}
	}
	return 0;
}

