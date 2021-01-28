// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include"sha1.h"
#include<stdio.h>
#include <cstdlib>
#include <time.h>

extern "C"
void makeSHA1(LPBYTE str, uint8_t* hash, int size)
{
    SHA1Context sha;
    uint8_t Message_Digest[20];
    int err = SHA1Reset(&sha);
    err = SHA1Input(&sha, (const unsigned char*)str, size);
    err = SHA1Result(&sha, Message_Digest);
    err = SHA1Reset(0);
    for (int i = 0; i < 20; ++i) {
        hash[i] = Message_Digest[i];
    }

}
//16進数の配列化
void writemem(BYTE *str,int size)
{
    char temp[10];
    OutputDebugString("{");
    for (int i = 0; i < size-1; i++) {
        sprintf_s(temp,sizeof(temp),"0x%x,",str[i]);
        OutputDebugString(temp);
  }
    sprintf_s(temp, sizeof(temp), "0x%x};\n", str[size-1]);
    OutputDebugString(temp);
}

//メモリの確認
void savemem(BYTE* str, int size)
{
    FILE* fp;
    fopen_s(&fp,"test.bin", "wb");
    fwrite(str, size, 1, fp);
    fclose(fp);
}

void dbgint(int n)
{
    char temp[100];
    sprintf_s(temp, sizeof(temp), "%x\n", n);
    OutputDebugString(temp);
}

int matchhash(uint8_t* hash1, uint8_t* hash2)
{
    for (int i = 0; i < 20; i++) {
        if (hash1[i] != hash2[i]) {
            return -1;
        }
    }
    return 0;
}
//334d10
//xorを探して書き換える
void crypto(LPBYTE EP,DWORD size, HANDLE hProc)
{
    for (int i = 0; i < (int)size - 4; i++) {
        if (*(EP + i) == 0x33 && *(EP + i + 1) == 0x4d && *(EP + i + 2) == 0x10) {
            if (*(EP + i + 2) != 0x14) {
                DWORD dwOldProtect, dwNewProtect;
                VirtualProtectEx(hProc, (LPBYTE)(EP+i+2), 1, PAGE_EXECUTE_READWRITE, &dwOldProtect);
                *(EP + i + 2) = 0x14;
                VirtualProtectEx(hProc, (LPBYTE)(EP + i + 2), 1, dwOldProtect, &dwNewProtect);
            }
        }
    }
}

void originalhash(BYTE *hash)
{
    //5バイトのダミー
    srand((unsigned int)time(NULL));
    BYTE rnd;
    char name[] = "Dll1.dll";
    FILE* fp; 
    fopen_s(&fp,name, "rb+");
    for (int i = 0; i < 5; i++) {
        rnd = rand() % 10;
        fwrite(&rnd, 1, 1, fp);
    }
    fclose(fp);
    
    //フラグ設定
    BYTE flag;
    fopen_s(&fp,name, "rb");
    fseek(fp, 5, SEEK_SET);
    fread(&flag, 1, 1, fp);
    fclose(fp);
    //初回起動だったら、ハッシュ書き込み
    if (flag == 0) {
        fopen_s(&fp, name, "rb+");
        fseek(fp, 6, SEEK_SET);
        fwrite(hash, 1, 20, fp);
        fclose(fp);
    }
    //ハッシュ読み込み
    BYTE temp[20];
    fopen_s(&fp, name, "rb");
    fseek(fp, 6, SEEK_SET);
    fread(temp, 1, 20, fp);
    fclose(fp);
    for (int i = 0; i < 20; i++) {
        hash[i] = temp[i];
    }
    //フラグ更新
    fopen_s(&fp, name, "rb+");
    fseek(fp, 5, SEEK_SET);
    flag++;
    fwrite(&flag, 1, 1, fp);
    fclose(fp);
    
}

_declspec(dllexport)
void protectcode(LPBYTE EP,DWORD size,HANDLE hProc)
{
    uint8_t oHash[20];
    uint8_t hash[20];
    
    //ハッシュ確認用
    makeSHA1(EP, oHash, size);
    originalhash(oHash);
    //writemem(hash,sizeof(hash));
    //
    while (1) {
        makeSHA1(EP, hash, size);
        if (matchhash(hash, oHash) != 0) {
            OutputDebugString("n");
            crypto(EP,size,hProc);
        }
        else {
            OutputDebugString("o");
        }
        Sleep(10);
    }
    


}
_declspec(dllexport)
void test()
{
    puts("Test");
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

