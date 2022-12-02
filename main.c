#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char buffer[50] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);
	long max1 = 0;
	long max2 = 0;
	long max3 = 0;
	long current = 0;
	while(ftell(f) != total){
		memset(buffer, 0, 50);
		fgets(buffer, 40, f);
		if(buffer[0] == '\n'){
			if(max1 < current){
				max3 = max2;
				max2 = max1;
				max1 = current;
			}else if(max2 < current){
				max3 = max2;
				max2 = current;
			}else if(max3 < current){
				max3 = current;
			}
			current = 0;
		}else {
			current += atoi(buffer);
		}
	}
	printf("max1 = %ld, max2 = %ld, max3 = %ld", max1, max2, max3);
	printf("total 3 max = %ld", max1 + max2 + max3);
}