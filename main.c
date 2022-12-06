#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool different14(char* s){
	if(strlen(s) < 14){
		return false;
	}
	for(int i = 0; i < 13; ++i){
		for(int j = i + 1; j < 14; ++j){
			if(s[i] == s[j]){
				return false;
			}
		}
	}
	return true;
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
		read = buffer;
		while(read - buffer < strlen(buffer) - 14){
			if(different14(read)){
				printf("%ld\n", read - buffer + delta + 14);
				return 0;
			}
			read++;
		}
		delta += strlen(buffer);
	}
}