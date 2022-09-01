#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split(char* line,int* ans){
	int i = 1;
	char* tmp;
	ans[0] = atoi(strtok(line, ","));
	while((tmp = strtok(NULL, ",")) != NULL){
		ans[i] = atoi(tmp);
		i++;
	}
}

int main(){
	char line[128] = "9,1,3,5";
	int ans[128];
	split(line, ans);
	printf("%d\n", ans[0]);
	printf("%d\n", ans[1]);
	return 0;
}
