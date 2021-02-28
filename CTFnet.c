#include <stdio.h>
#include<windows.h>
#include <stdlib.h>
typedef struct {
	BYTE* p;
	long size;
}bin_t;

int b64table(int b64)
{
	int ascii=-1;
	//0~9 48~57 -> 52~61
	if (b64 >= 48 && b64 <= 57) {
		ascii = b64 + 4;
	}
	//A~Z 65~90 -> 0~25
	if (b64 >= 65 && b64 <= 90) {
		ascii = b64 - 65;
	}
	//a~z 97~122 -> 26~51
	if (b64 >= 97 && b64 <= 122) {
		ascii = b64 - 71;
	}
	//'+' 43 -> 62
	if (b64 == 43) {
		ascii = b64 + 19;
	}
	//'/' 47 -> 63
	if (b64 == 47) {
		ascii = b64 + 16;
	}
	//'=' 61 -> 0
	if (b64 == 61) {
		ascii = 0;
	}
	//error
	if (b64 == -1) {
		printf("ascii=%d\n",b64);
	}
	return ascii;
}

void b64decode(bin_t *data)
{
	int b64size = data->size * 6 / 8;
	BYTE* decode = (BYTE*)malloc(b64size);
	memset(decode, 0, b64size);
	int i;
	for ( i = 0; i < data->size; i += 3) {
		int comp = i / 3;
		if (i + comp >= data->size)break;
		decode[i] += b64table(data->p[i + comp]) << 2;
		if (i + 1 + comp >= data->size)break;
		decode[i] += b64table(data->p[i + 1 + comp]) >> 4;
		decode[i + 1] += b64table(data->p[i + 1 + comp]) << 4;
		if (i + 2 + comp >= data->size)break;
		decode[i + 1] += b64table(data->p[i + 2 + comp]) >> 2;
		decode[i + 2] += b64table(data->p[i + 2 + comp]) << 6;
		if (i + 3 + comp >= data->size)break;
		decode[i + 2] += b64table(data->p[i + 3 + comp]);
	}
	/*
	for (int i = 0; i < b64size; i++) {
		putchar(decode[i]);
	}*/
	//puts("");
	data->p = decode;
	data->size = b64size;
}

void b64encode(BYTE* moji, int size)
{
	char base64[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int b64size = (int)(size * 8 / 24) * 4;
	int surplus = (size) * 8 % 6 % 3;
	b64size += (4 - surplus) % 4;
	BYTE* encode = (BYTE*)malloc(b64size);
	memset(encode, 0, b64size);
	int i = 0;
	for (i = 0; i < size; i += 3) {
		int comp = i / 3;
		if (i >= size)break;
		encode[i + comp] += (moji[i] & 0b11111100) >> 2;
		encode[i + 1 + comp] += (moji[i] & 0b00000011) << 4;
		if (i + 1 >= size)break;
		encode[i + 1 + comp] += (moji[i + 1] & 0b11110000) >> 4;
		encode[i + 2 + comp] += (moji[i + 1] & 0b00001111) << 2;
		if (i + 2 >= size)break;
		encode[i + 2 + comp] += (moji[i + 2] & 0b11000000) >> 6;
		encode[i + 3 + comp] += (moji[i + 2] & 0b00111111);
	}
	for (i = 0; i < b64size; i++) {
		putchar(base64[encode[i] % 64]);
	}
	for (i = 0; i < surplus; i++) {
		putchar('=');
	}
	puts("");

}



bin_t readbin(char name[])
{
	FILE* fp;
	fp = fopen(name, "rb");
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	BYTE* p;
	p = (BYTE*)malloc(size);
	memset(p, 0, size);
	fread(p, 1, size, fp);
	fclose(fp);
	bin_t a;
	a.p = p;
	a.size = size;

	return a;
}

void savebin(char* name, BYTE* data, int size)
{
	FILE* fp;
	fp = fopen(name, "ab+");
	fwrite(data, 1, size, fp);
	fclose(fp);
}

void DLURL(char* url,char* file)
{
	char dll[MAX_PATH];
	GetSystemDirectory(dll,MAX_PATH);
	strcat(dll,"\\urlmon.dll");
	HMODULE hMod=LoadLibrary(dll);
	long (*urldltofile)(long,char*,char*,long,long)=(long (*)(long,char*,char*,long,long))GetProcAddress(hMod,"URLDownloadToFileA");
	urldltofile(0,url,file,0,0);
}

int cmp(char *flag)
{
	BYTE b64url[] = "aHR0cHM6Ly95c2tydC5naXRodWIuaW8vd2ViL0NURm5ldC5odG1s";
	bin_t urldata;
	urldata.p = b64url;
	urldata.size = sizeof(b64url);
	b64decode(&urldata);
	char *url=(char*)malloc(urldata.size+1);
	int i;
	for (i = 0; i < urldata.size; i++) {
		url[i] = urldata.p[i];
	}
	url[urldata.size] = '\0';
	//DLURL(url,"a");
	char temp[1000];
	GetCurrentDirectory(1000,temp);
	strcat(temp,"\\a");
	char temp2[1000];
	sprintf(temp2,"powershell -Command \"(New-Object System.Net.WebClient).DownloadFile(\'%s\',\'%s\')\"",url,temp);
	system(temp2);
	
	bin_t data = readbin((char*)"a");
	b64decode(&data);
	remove("a");

	for (i = 0;;i++) {
		if (flag[i] == '\0')break;
		if (data.p[i]*2 != flag[i]*2) {
			return -1;
		}
	}

	ZeroMemory(data.p,data.size+1);
	return 0;
}
int main()
{
	puts("正しいフラグを入力してください");
	char flag[100];
	scanf("%s",flag);
	if (cmp(flag) == -1) {
		puts("フラグは正しくありません。頑張って！！");
	}
	else {
		puts("正しいフラグです！おめでとう！！");
	}
	getchar();
	getchar();
	return 0;
}