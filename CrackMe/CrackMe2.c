#include <stdio.h>
#include<windows.h>
int main(void)
{
	BYTE code[]={
	0x53,//push ebx
	0x50,//push eax
	0xBB,0,0,0,0,//mov ebx,[flag]
	0x53,//push ebx
	0xBB,0,0,0,0,//mov ebx,[pass]
	0x36,0x0F,0xBE,0x03,//movsx eax,byte ptr ss:[ebx]
	0x83,0xF8,0x50,//cmp eax,'P'
	0x0F,0x85,0x53,0,0,0,//jne 
	0x43,//inc ebx
	0x36,0x0F,0xBE,0x03,//movsx eax,byte ptr ss:[ebx]
	0xEB,0x0E,//jmp for fake!!!!!!!!!!!!!!!
	
	0x51,//push ecx!!!!!!!
	0xB9,0,0,0,0,//mov ecx,[]!!!!!!
	0x3E,0xC6,0x01,0x2D,//mov dword ptr ds:[ecx],0x2D!!!!!!!
	0x59,//pop ecx!!!!!
	0xEB,0x16,//jmp
	0xE9,//fake jmp!!!!!!!!!!!!!!!!!!!!
	
	
	0x83,0xF8,0x44,//cmp eax,'D'
	0x0F,0x85,0x35,0,0,0,//jne 
	0x43,//inc ebx
	0x36,0x0F,0xBE,0x03,//movsx eax,byte ptr ss:[ebx]
	0x05,0x99,0,0,0,//add eax,99!!!!!!
	
	0xEB,0xDD,//jmp back
	
	0x2D,0xEC,0,0,0,//sub eax,EC!!!!!!!!! 'S'
	0xEB,2,//jmp for fake!!!!!!!!!!!!!!!
	0x83,0xF8,//fake cmp eax!!!!!!!!!!!!!!!!!!!!
	0x85,0xC0,//test eax,eax!!!!!!!!!!!!
	0x0F,0x85,0x18,0,0,0,//jne 18!!!!!!!!
	0x43,//inc ebx
	0x36,0x0F,0xBE,0x03,//movsx eax,byte ptr ss:[ebx]
	0x83,0xF8,0,//cmp eax,0
	0x0F,0x85,0x0A,0,0,0,//jne A
	0xB8,0x01,0,0,0,//mov eax,1
	0xE9,0x05,0,0,0,//jmp 5
	
	0xB8,0x00,0,0,0,//mov eax,0
	0x5B,//pop ebx
	0x36,0x88,0x03,//mov byte ptr ss:[ebx],al
	0x58,//pop eax
	0x5B,//pop ebx
	0xC3//ret
	};
	char pass[100];
	code[9]=(BYTE)((DWORD)pass);
	code[10]=(BYTE)((DWORD)pass>>8);
	code[11]=(BYTE)((DWORD)pass>>16);
	code[12]=(BYTE)((DWORD)pass>>24);
	int flag=0;
	code[3]=(BYTE)((DWORD)&flag);
	code[4]=(BYTE)((DWORD)&flag>>8);
	code[5]=(BYTE)((DWORD)&flag>>16);
	code[6]=(BYTE)((DWORD)&flag>>24);
	
	code[35]=(BYTE)((DWORD)&code+0x3D);
	code[36]=(BYTE)(((DWORD)&code+0x3D)>>8);
	code[37]=(BYTE)(((DWORD)&code+0x3D)>>16);
	code[38]=(BYTE)(((DWORD)&code+0x3D)>>24);
	
	void (*p)()=(void(*)())code;
	puts("Search Correct PASS.");
	puts("Enter appropriate PASS.");
	scanf("%s",pass);
	//////////////////////////
	(*p)();
	//////////////////////////
	if(flag){
		puts("Correct");
	}else{
		puts("Wrong");
	}
	getchar();
	getchar();
return 0;
}