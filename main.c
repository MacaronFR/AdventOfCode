#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char buffer[50] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);
	int max = 0;
	int current = 0;
	while(ftell(f) != total){
		memset(buffer, 0, 50);
		fgets(buffer, 40, f);
		if(buffer[0] == '\n'){
			if(max < current){
				max = current;
			}
			current = 0;
		}else {
			current += atoi(buffer);
		}
	}
	printf("Max = %d", max);
}