#include <stdio.h>
#include<string.h>
int main(void)
{
	char flag[3]="0";
	char pass[15]="";
	int i=0;
	puts("CTF�ł��B�t���O��FLAG_�Z�Z�̌`�Ŏ�����܂��B");
	while(i<3){
	puts("�p�X���[�h����͂��Ă�������:");
	scanf("%s",pass);
	if(strcmp(pass,"banana")==0){
		strcpy(flag,"correct");
	}
	if(strcmp(flag,"0")!=0){
		puts("���O�C�����܂����B");
		puts("�p�X���[�h��banana�ł����B\n�o�b�t�@�I�[�o�[�t���[�̖��ł����B\n�t���O��FLAG_OVERFLOW�ł��B");
		system("pause");
		break;
	}else{
		puts("�p�X���[�h������������܂���B");
		if(i==1){
		puts("�q���g:");
		printf("�ϐ�pass�̃A�h���X:%p\n",pass);
		printf("�ϐ�flag�̃A�h���X:%p\n",flag);
		getchar();
		}
		if(i==2){
		puts("�q���g:");
		puts("flag�̃A�h���X��pass�̌�ɂ���Ƃ������Ƃ́Apass��������flag�ɉe�����E�E�E�H");
		getchar();
		getchar();
		}
	}
	i++;
	}
	return 0;
}

