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
	long tot = 0;
	int start1, start2, end1, end2;

	//START READ FILE
	while(ftell(f) != total) {
		memset(buffer, 0, 100);
		fgets(buffer, 90, f);

		//START CODE
		sscanf(buffer, "%d-%d,%d-%d", &start1, &end1, &start2, &end2);
		tot += start1 <= start2 && end1 >= end2 || start2 <= start1 && end2 >= end1;
	}
	printf("%ld\n", tot);
}