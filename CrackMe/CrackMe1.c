#include <stdio.h>

int main(void)
{
	puts("Search Correct PASS.");
	puts("Enter appropriate PASS.");
	char pass[100];
	int flag=0;
	scanf("%s",pass);
	//////////////////////////
	if(pass[0]=='3'){
		if(pass[1]=='t'){
			if(pass[2]=='q'){
				if(pass[3]=='\0'){				
					flag=1;
				}
			}
		}
	}
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