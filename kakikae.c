#include <stdio.h>
#include <string.h>
#include<stdlib.h>
void xorchar(char*,int,int);


int main(){
char flag[]="GM@F^gsthu";
int key=1;
xorchar(flag,sizeof(flag)-1,key);

char moji[]="ringo";
puts("CTF�ł��BFLAG�Q�Z�Z�̌`�Ŏ����ꂽ�t���O�������Ă��������B");
printf("char�^�z��moji�̒��ɂ�ringo�������Ă��܂��B\n��������p��ɒ����Ă��������B\n");
if(strcmp(moji,"apple")==0){
	printf("�N���A�ł��I\n�t���O��%s�ł��B",flag);
	getchar();
}else{
	puts("�q���g���~�����Ȃ玟�̓�������͂��Ă�\nA xor B=?\n(16�i��)");
	if(getchar()=='1'){
	puts("�q���g:�o�C�i���G�f�B�^�ŊJ���ƁE�E�E");
	getchar();
	getchar();
	}
}
if(0)
puts("////���E���g���q���g:�u�r...�E�Ei...�E�E n...�E�Eg...�E�� o..�v�̂Ƃ�������Ă݂āB�����������������OK�I////");
return 0;
}

void xorchar(char *str,int strnum,int key){
	int i;
	for(i=0;i<strnum;i++){
		str[i]=(int)(str[i])^key;
	}
}