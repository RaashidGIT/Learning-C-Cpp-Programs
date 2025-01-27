#include<stdio.h>
#include<unistd.h>
int main(){
	for(int a = 0; a < 5; a++){
		fork();
		printf("Hello!\n");		
	}
	return 0;
}

