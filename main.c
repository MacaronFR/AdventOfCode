#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int findItemInThree(char *elf1, char *elf2, char*elf3){
	for(int i = 0; i < strlen(elf1); ++i){
		for(int j = 0; j < strlen(elf2); ++j){
			if(elf1[i] == elf2[j]){
				for(int k = 0; k < strlen(elf3); ++k){
					if(elf3[k] == elf2[j]){
						return elf3[k];
					}
				}
			}
		}
	}
	return -1;
}

int main() {
	// READ FILE INIT
	char buffer[100] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	char *elf1, *elf2, *elf3;
	long sum = 0;

	//START READ FILE
	while(ftell(f) != total) {
		memset(buffer, 0, 100);
		fgets(buffer, 90, f);

		elf1 = malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(elf1, buffer);

		memset(buffer, 0, 100);
		fgets(buffer, 90, f);

		elf2 = malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(elf2, buffer);

		memset(buffer, 0, 100);
		fgets(buffer, 90, f);

		elf3 = malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(elf3, buffer);

		int res = findItemInThree(elf1, elf2, elf3);
		if(islower(res)){
			sum += res - 'a' + 1;
		}else if(isupper(res)){
			sum += res - 'A' + 27;
		}

		free(elf1);
		free(elf2);
		free(elf3);
	}
	printf("%ld\n", sum);
}