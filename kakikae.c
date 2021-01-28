#include <stdio.h>
#include <string.h>
#include<stdlib.h>
void xorchar(char*,int,int);


int main(){
char flag[]="GM@F^gsthu";
int key=1;
xorchar(flag,sizeof(flag)-1,key);

char moji[]="ringo";
puts("CTFです。FLAG＿〇〇の形で示されたフラグを見つけてください。");
printf("char型配列mojiの中にはringoが入っています。\nこれをを英語に直してください。\n");
if(strcmp(moji,"apple")==0){
	printf("クリアです！\nフラグは%sです。",flag);
	getchar();
}else{
	puts("ヒントが欲しいなら次の答えを入力してね\nA xor B=?\n(16進数)");
	if(getchar()=='1'){
	puts("ヒント:バイナリエディタで開くと・・・");
	getchar();
	getchar();
	}
}
if(0)
puts("////超ウルトラヒント:「ｸr...・・i...・・ n...・・g...・昤 o..」のところを見てみて。そこを書き換えればOK！////");
return 0;
}

void xorchar(char *str,int strnum,int key){
	int i;
	for(i=0;i<strnum;i++){
		str[i]=(int)(str[i])^key;
	}
}