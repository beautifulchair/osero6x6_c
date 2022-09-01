#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 256

typedef struct boardImfo{
	int n;
	int board[64];
}boardImfo;

void split(char* line, int* ans){
	char *token;
	int i = 1;
	ans[0] = atoi(strtok(line, ","));
	while((token = strtok(NULL, ",")) != NULL){
		ans[i] = atoi(token);
		i++;
	}
}

void printalay(int* alay, int n){
	for(int i=0;i<n;i++){
		printf("%d ", alay[i]);
	}
	printf("\n");
}

void printBoard(int* aray){
	printf("\n");
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			printf("%d ", aray[i*8+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void writeFile(boardImfo bi){
	FILE *fp;
	char *fname = "boardImfo.csv";
	fp = fopen(fname, "a");
	if(fp == NULL){
		printf("fopen failed.");
	}else{
		fprintf(fp, "%d", bi.board[0]);
		for(int i=1; i<64; i++){
			fprintf(fp, ",%d", bi.board[i]);
		}
	}
	fprintf(fp, "\n");
	fclose(fp);

}

boardImfo initialBoardImfo(){
	boardImfo new;
	new.n = -1;
	for(int i=0; i<64; i++){
		new.board[i] = 0;
	}
	new.board[27] = 2;
	new.board[28] = 1;
	new.board[35] = 1;
	new.board[36] = 2;
	return new;
}

void setBoard(boardImfo* bi, int* board){
	for(int i=0; i<64; i++){
		bi->board[i] = board[i];
	}
}

void changeBoard(boardImfo* bi, int x, int y, int v){
	bi->board[x*8+y] = v;
}

int main(){
	FILE *fp;
	char *fname = "boardImfo.csv";
	int record[180];
	int num;
	char tmp[256];
	int i;
	int yobi[64];
	boardImfo biArray[64];
	boardImfo bi;
	boardImfo latestBi;
	//read boardImfo.csv	
	fp = fopen(fname, "r");
	if(fp == NULL){
		printf("fopen failed.");
	}else{
		i = 0;
		while(fgets(tmp, SIZE, fp)){
			
			if(i%2==0)split(tmp, );
			else split(tmp, )
		}
	}
	fclose(fp);
	
	latestBi.board = infos[num-1];
	latestBi.n = num;
	
	
	return 0;
}
