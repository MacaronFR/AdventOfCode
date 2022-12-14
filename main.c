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
	int cycle = 1;
	int tot = 0;
	int x = 1;
	int add;
	memset(buffer, 0, 110);

	//START READ FILE
	while(ftell(f) != total) {
		cycle++;
		if(buffer[0] == 0) {
			memset(buffer, 0, 110);
			fgets(buffer, 105, f);
		}
		if(strncmp("noop", buffer, 4) == 0){
			buffer[0] = 0;
		}
		if(buffer[0] == 1){
			sscanf(buffer + 5, "%d", &add);
			x += add;
			buffer[0] = 0;
		}
		switch (cycle){
			case 20:
			case 60:
			case 100:
			case 140:
			case 180:
			case 220:
				printf("X = %d\n", x);
				tot += x * cycle;
				break;
		}
		if(strncmp("addx", buffer, 4) == 0){
			buffer[0] = 1;
		}
	}

	printf("Total = %d", tot);
}