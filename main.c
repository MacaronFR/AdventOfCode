#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool allDifferent(char a, char b, char c, char d){
	return a != b && a != c && a != d
	&& b != c && b != d
	&& c != d;
}

int main() {
	// READ FILE INIT
	char buffer[100] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	char *read;
	unsigned long delta = 0;

	//START READ FILE
	while(ftell(f) != total) {
		memset(buffer, 0, 100);
		fgets(buffer, 90, f);
		read = buffer + 3;
		while(read - buffer < strlen(buffer)){
			if(allDifferent(read[0], read[-1], read[-2], read[-3])){
				printf("%ld\n", read - buffer + delta +1);
				return 0;
			}
			read++;
		}
		delta += strlen(buffer);
	}
}