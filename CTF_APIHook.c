#include<stdio.h>
#include<windows.h>

int main();
void fake();
void judge();

void xorchar(char* str, int strnum, int key) {
	int i;
	for (i = 0; i < strnum; i++) {
		str[i] = (int)(str[i]) ^ key;
	}
}

void changeCode(LPBYTE p,BYTE *str,int size)
{
	DWORD dwOldProtect, dwNewProtect;
	VirtualProtect(p, size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	int i=0;
	for(i=0;i<size;i++){
		*(p+i)=(BYTE)str[i];
	}
	VirtualProtect(p, size, dwOldProtect, &dwNewProtect);
}
//judge�̃G���g���|�C���g������������B
//fake��jmp����
void rewrite()
{
	DWORD dwOldProtect, dwNewProtect;
	LPVOID p=judge;
	VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	DWORD jmpto;
	jmpto=((DWORD)fake-(DWORD)p-0x5);
	*(LPVOID)((DWORD)p+0x0)=0xe9;
	*(LPVOID)((DWORD)p+0x1)=jmpto;

	VirtualProtect(p, 5, dwOldProtect, &dwNewProtect);
	
}

void fake()
{
	puts("FROG_fake");
}

int isDBG()
{
	/*
	mov eax,dword ptr fs:[30]
	movzx eax,byte ptr ds:[eax+2]
	str���Ăяo���Ƃ�ebp-20��p���Ă������炻����IsDebuggerPresent�̖߂�l����ꂽ�B
	mov dword ptr ss:[ebp-20],eax
	ret
	*/
	BYTE s[]={0x64,0xa1,0x30,0,0,0,
	0x0f,0xb6,0x40,0x02,
	0x89,0x45,0xe0,
	0xc3};
	BYTE *str=(BYTE*)malloc(sizeof(s));
	memset(str,0,sizeof(s));
	int i=0;
	for(i=0;i<sizeof(s);i++){
		str[i]=s[i];
	}
	void (*p)();
	p=(void(*)())str;
	(*p)();
	free(str);
	/*
	mov eax,dword ptr ss:[ebp-20]
	�߂�l��IsDebuggerPresent�̖߂�l��Ԃ��B
	*/
	BYTE s2[]={0x8b,0x45,0xe0,0x90,0x90};
	changeCode((LPBYTE)(isDBG+0x14a),s2,sizeof(s2));
	return 0;
}


int mystrcmp(char* str1,char* str2)
{
	char strcmpdll[MAX_PATH];
	GetSystemDirectory(strcmpdll,MAX_PATH);
	strcat(strcmpdll,"\\ucrtbased.dll");
	HMODULE hMod=LoadLibrary(strcmpdll);
	int (*strcmplib)(char*,char*)=(int (*)(char*,char*))GetProcAddress(hMod,"strcmp");
	return strcmplib(str1,str2);
}

void judge()
{
	char flag[]="CIDBZdvv`hgi`p�";
	if(mystrcmp("1+1","2")==0){
		xorchar(flag,sizeof(flag),5);
		puts(flag);
	}else{
		puts("search FLAG!!");
	}
}

int main()
{
	if(IsDebuggerPresent()){
		puts("Debbuger Detected!!");
		getchar();
		return 0;
	}
	if(strcmp("a","b")==0){
		puts("IAT Hooked!!");
	}
	if(isDBG()==1){
	rewrite();
	}
	judge();

	getchar();

	return 0;
}