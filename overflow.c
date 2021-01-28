#include <stdio.h>
#include<string.h>
int main(void)
{
	char flag[3]="0";
	char pass[15]="";
	int i=0;
	puts("CTFです。フラグはFLAG_〇〇の形で示されます。");
	while(i<3){
	puts("パスワードを入力してください:");
	scanf("%s",pass);
	if(strcmp(pass,"banana")==0){
		strcpy(flag,"correct");
	}
	if(strcmp(flag,"0")!=0){
		puts("ログインしました。");
		puts("パスワードはbananaでした。\nバッファオーバーフローの問題でした。\nフラグはFLAG_OVERFLOWです。");
		system("pause");
		break;
	}else{
		puts("パスワードが正しくありません。");
		if(i==1){
		puts("ヒント:");
		printf("変数passのアドレス:%p\n",pass);
		printf("変数flagのアドレス:%p\n",flag);
		getchar();
		}
		if(i==2){
		puts("ヒント:");
		puts("flagのアドレスがpassの後にあるということは、passが長いとflagに影響が・・・？");
		getchar();
		getchar();
		}
	}
	i++;
	}
	return 0;
}

