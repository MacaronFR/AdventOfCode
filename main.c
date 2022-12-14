#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

int main() {
	// READ FILE INIT
	char buffer[110] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	int cycle = 0;
	int tot = 0;
	int x = 0;
	int add;
	memset(buffer, 0, 110);

	//START READ FILE
	while(ftell(f) != total) {
		if(buffer[0] == 0) {
			memset(buffer, 0, 110);
			fgets(buffer, 105, f);
		}
		if(cycle % 40 < x || cycle % 40 > x + 2){
			printf(".");
		}else{
			printf("#");
		}
		if((cycle + 1) % 40 == 0){
			printf("\n");
		}
		cycle++;
		if(strncmp("noop", buffer, 4) == 0){
			buffer[0] = 0;
		}else if(strncmp("addx", buffer, 4) == 0){
			buffer[0] = 1;
		}else if(buffer[0] == 1){
			sscanf(buffer + 5, "%d", &add);
			x += add;
			buffer[0] = 0;
		}
	}

	printf("Total = %d", tot);
}