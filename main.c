#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
	// READ FILE INIT
	char buffer[100] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	long sum = 0;
	unsigned long len;
	char saveL[26];
	char saveU[26];

	//START READ FILE
	while(ftell(f) != total) {
		memset(buffer, 0, 100);
		fgets(buffer, 90, f);

		// START CODE
		memset(saveL, 0, 26);
		memset(saveU, 0, 26);
		len = strlen(buffer);
		for(int i = 0; i < len/2; ++i){
			for(unsigned long j = len/2; j < len; ++j){
				if(buffer[i] == buffer[j]){
					if(isupper(buffer[i]) && saveU[buffer[i]-'A'] != 1){
						saveU[buffer[i]-'A'] = 1;
						sum += buffer[i] - 'A' + 27;
					}else if(islower(buffer[i]) && saveL[buffer[i]-'a'] != 1){
						saveL[buffer[i]-'a'] = 1;
						sum += buffer[i] - 'a' + 1;
					}
				}
			}
		}
	}
	printf("%ld\n", sum);
}