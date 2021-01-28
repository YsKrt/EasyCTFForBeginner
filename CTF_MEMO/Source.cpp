#include<windows.h>
#include<stdio.h>
#include<tchar.h>
#include <locale.h>
#include"protectcode.h"
#include <imagehlp.h>
#include <time.h>
#pragma comment(lib, "Imagehlp.lib")

void putmsg(HWND hwnd, char* str, int size,int time);



void xorchar(char* str, int strnum, int key) {
	int i;
	for (i = 0; i < strnum; i++) {
		str[i] = (int)(str[i]) ^ key;
	}
}

void getflag(char* flag,int size,int key)
{
	if (strcmp("1+1", "2") == 0) {
		xorchar(flag,size,key);
	}
}

void clip()
{
	HGLOBAL hg;
	PTSTR	strMem;
	if (!OpenClipboard(NULL)) return;
	EmptyClipboard();

	hg = GlobalAlloc(GHND | GMEM_SHARE, 128);
	strMem = (PTSTR)GlobalLock(hg);
	
	//FLAG
	srand((unsigned int)time(NULL));
	int key = rand()%3+1;
	char flag[100] = "4,5-0YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY";
	xorchar(flag,sizeof(flag),key);
	for (int i = 0; i < 100; i+=7) {
		xorchar(flag,sizeof(flag),i);
	}
	getflag(flag, sizeof(flag), key);
	lstrcpy(strMem, TEXT(flag));
	GlobalUnlock(hg);

	SetClipboardData(CF_TEXT, hg);

	CloseClipboard();
}

DWORD WINAPI threadFunc2(LPVOID vdParam)
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION pi = {};
	char path[MAX_PATH];
	GetSystemDirectory(path,sizeof(path));
	strcat_s(path, "\\notepad.exe");
	CreateProcess(0,path,0,0,0, DETACHED_PROCESS,0,0,&si,&pi);
	Sleep(3000);
	
	CloseHandle(pi.hThread);
	HWND note = FindWindow(_T("Notepad"),NULL);
	HWND noteEdit = FindWindowEx(note,NULL,_T("Edit"), NULL);

	char temp[] = "フラグはとある場所に隠した！\n探せ！\nよく使うとこにあるからすぐわかっちゃうかも。\nみつけたら1～3のどれかでxorしといて！\n";
	putmsg(noteEdit,temp,sizeof(temp)+1,100);
	char temp2[] = "Lq%rjpia%g`%d%qwjpgi`)%vj%L%hda`%lq%|jp%fdk%b`q%qm`%cidb%cwjh%vqwfhu+_\n";
	xorchar(temp2,sizeof(temp2),5);
	putmsg(noteEdit, temp2,sizeof(temp2)+1, 30);
	char tempf[200] = {0};
	SendMessage(noteEdit, WM_SETTEXT, 0, (LPARAM)tempf);
	char temp3[] = "Sob'onis'nt'f'tohusdrs'lb~)ﾌﾌﾌﾌﾌﾌﾌﾌ";
	xorchar(temp3, sizeof(temp3), 7);
	SendMessage(noteEdit, WM_SETTEXT, 0, (LPARAM)temp3);
	Sleep(100);
	TerminateProcess(pi.hProcess,0);
	CloseHandle(pi.hProcess);
	clip();
	return 0;
}

void putmsg(HWND hwnd,char *str,int size,int time)
{
	char str2[1024] = {0};
	for (int i = 0; i < size; i += 2) {
		memcpy((char*)str2, str, i);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)str2);
		Sleep(time);
	}
}

void dbgint(int n)
{
	char temp[100];
	sprintf_s(temp, sizeof(temp), "%x\n", n);
	OutputDebugString(temp);
}

DWORD WINAPI threadFunc(LPVOID vdParam)
{

	PIMAGE_DOS_HEADER pSehIDH = (PIMAGE_DOS_HEADER)GetModuleHandle(NULL);
	PIMAGE_NT_HEADERS pSehINH = (PIMAGE_NT_HEADERS)((DWORD)pSehIDH + pSehIDH->e_lfanew);
	PIMAGE_FILE_HEADER pIFH = &pSehINH->FileHeader;
	PIMAGE_OPTIONAL_HEADER pIOH = (PIMAGE_OPTIONAL_HEADER)&pSehINH->OptionalHeader;
	PIMAGE_SECTION_HEADER pISH = (PIMAGE_SECTION_HEADER)((PBYTE)pIOH + sizeof(IMAGE_OPTIONAL_HEADER));

	DWORD EP = (DWORD)pSehIDH;
	//0は.textbssにかわった。
	//1が.textであった
	//2が.rdata
	//PEを含めるとファイルを移動させるだけで変化するらしいから.textだけにした。
	DWORD secnum = pIFH->NumberOfSections;
	secnum = 2;
	DWORD FinSecSize = pISH[secnum-1].Misc.VirtualSize;
	DWORD FinSecAddr = pISH[secnum - 1].VirtualAddress+EP;
	DWORD FinSecEndSize = FinSecSize;
	//書き換えのため
	DWORD pId = GetCurrentProcessId();
	HANDLE hProc= OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	
	OutputDebugString((LPCSTR)pISH[secnum - 1].Name);

	//.textのハッシュで確認
	protectcode((LPBYTE)FinSecAddr,FinSecEndSize,hProc);
	return 0;
}

void fake()
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION pi = {};
	char path[MAX_PATH];
	GetSystemDirectory(path, sizeof(path));
	strcat_s(path, "\\notepad.exe");
	CreateProcess(0, path, 0, 0, 0, DETACHED_PROCESS, 0, 0, &si, &pi);
	Sleep(3000);

	CloseHandle(pi.hThread);
	HWND note = FindWindow(_T("Notepad"), NULL);
	HWND noteEdit = FindWindowEx(note, NULL, _T("Edit"), NULL);

	char temp[] = "メッセージとかめちゃくちゃ大変だったんだけど。\n特に文字コードとか意味不明すぎる。\n難しすぎるしこれ作るのさえもめちゃ時間かかったわー。\n"
		"本当はもっとメモ帳をいじったCTFにしたかったんだけど俺には難しすぎたわ。\nメニューのところも全然わからぬ。"
		"\nほんとにこれ作るだけで1週間くらいかかったし、もともとの想定のようにうまくできなかったけど、頑張ったから楽しんでほしい！\n";
	putmsg(noteEdit, temp, sizeof(temp) + 1, 100);
	Sleep(1000);
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hProcess);
}

int antiiathook()
{
	TCHAR dllname[MAX_PATH];
	GetSystemDirectory(dllname, MAX_PATH);
	strcat_s(dllname, "\\ucrtbased.dll");
	HMODULE hMod = LoadLibrary(dllname);
	LPBYTE funcAddr = (LPBYTE)GetProcAddress(hMod, "strcmp");

	ULONG Size;
	IMAGE_IMPORT_DESCRIPTOR* pImpDesc;
	IMAGE_THUNK_DATA* pThunkINT, * pThunkIAT;
	IMAGE_IMPORT_BY_NAME* pImpByName;
	hMod = GetModuleHandle(NULL);
	// ベースアドレスからインポートデスクリプタのアドレスを得る
	pImpDesc = (IMAGE_IMPORT_DESCRIPTOR*)ImageDirectoryEntryToData(hMod, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &Size);
	while (pImpDesc->Name) {
		// モジュール名
		LPSTR pszModName = (LPSTR)((BYTE*)hMod + pImpDesc->Name);
		if (_stricmp(pszModName, "ucrtbased.dll") == 0) {
			// インポートネームテーブルのアドレスを得る
			pThunkINT = (IMAGE_THUNK_DATA*)((BYTE*)hMod + pImpDesc->OriginalFirstThunk);
			// インポートアドレステーブルのアドレスを得る
			pThunkIAT = (IMAGE_THUNK_DATA*)((BYTE*)hMod + pImpDesc->FirstThunk);

			// インポートAPIの情報
			while (pThunkINT->u1.Function) {
				// API アドレスを出力
					pImpByName = (IMAGE_IMPORT_BY_NAME*)
						((BYTE*)hMod + pThunkINT->u1.AddressOfData);
					if (_stricmp(pImpByName->Name, "strcmp")==0) {
						if ((LPBYTE)pThunkIAT->u1.Function != funcAddr) {
							//strcmp is hooked!
							return 1;
						}
				}
				pThunkINT++;
				pThunkIAT++;
			}
		}
		
		pImpDesc++;
	}
	return 0;
}

typedef struct _PROCESS_BASIC_INFORMATION {
	PVOID Reserved1;
	void* PebBaseAddress;
	PVOID Reserved2[2];
	ULONG_PTR UniqueProcessId;
	ULONG_PTR ParentProcessId;
} PROCESS_BASIC_INFORMATION;
bool CheckParentProcessId()
{
	// explore.exe の pid
	DWORD dwExplorerPid = 0;
	GetWindowThreadProcessId(GetShellWindow(), &dwExplorerPid);

	typedef NTSTATUS(WINAPI* TNtQueryInformationProcess)(HANDLE, UINT, PVOID, ULONG, PULONG);
	TNtQueryInformationProcess fnNtQueryInformationProcess;

	NTSTATUS Status = 0;
	PROCESS_BASIC_INFORMATION pbi;
	ZeroMemory(&pbi, sizeof(PROCESS_BASIC_INFORMATION));

	fnNtQueryInformationProcess = (TNtQueryInformationProcess)
		GetProcAddress(
			GetModuleHandle("ntdll.dll"),
			"NtQueryInformationProcess");

	if (fnNtQueryInformationProcess == 0)
		return false;

	Status = fnNtQueryInformationProcess(GetCurrentProcess(),
		0, (void*)&pbi, sizeof(PROCESS_BASIC_INFORMATION), 0);

	if (Status != 0x00000000)
		return false;

	if (pbi.ParentProcessId != dwExplorerPid)
		return false;

	return true;

}

void crypt2b(char *str,int size)
{
	for (int i = 0; i < size; i += 2) {
		str[i] = ~str[i];
	}
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	
	//フック対策
	srand((unsigned int)time(NULL));
	if (rand() % 2 == 0) {
		if (antiiathook() == 1) {
			char str1[60] = "|t|b|N}ﾍvｴ}ｪq~}ﾟ}驃I|t|b|N}ｵ}ｽ}｢}ﾈ}轅ｴ}|}ｹ~I~I";
			char str2[30] = "|s|s~[~I|t|b|Nsxq@}ﾅ}ｷ~I";
			crypt2b(str1, 60);
			crypt2b(str2,30);
			
			MessageBox(NULL, str1,str2 , MB_OK);
			return 0;
		}
			
	}else{
		if (!CheckParentProcessId()) {
			char str1[60] = "il}ﾍ|G|N|X|v|降[|円[}ｿ}痾ﾈuO}ﾌsｾ}､}ｱ}ﾆ}ﾍjｷ}ｩ}ﾈ}｢}ｾ~I~I";
			char str2[30] = "kｽrRu僘ﾅ}ｷ~I";
			crypt2b(str1, 60);
			crypt2b(str2, 30);
			MessageBox(NULL, str1, str2, MB_OK);
			return 0;
		}
	}
	
	
	DWORD dwID,dwID2;
	HANDLE hThread1,hThread2=NULL;
	hThread1 = CreateThread(NULL, 0, threadFunc, NULL, 0, &dwID);
	
	//デバッガ対策
	if (IsDebuggerPresent() == 0) {
		hThread2 = CreateThread(NULL, 0, threadFunc2, NULL, 0, &dwID2);
	}else{
		fake();
	}
	if (hThread2 != NULL) {
		WaitForSingleObject(hThread2, INFINITE);
	}
	
	

	return 0;
}
