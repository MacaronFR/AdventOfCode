#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char buffer[50] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);
	int o;
	int m;
	int res[3][3] = {
			{3 + 0, 1 + 3, 2 + 6},
			{1 + 0, 2 + 3, 3 + 6},
			{2 + 0, 3 + 3, 1 + 6}
	};
	long score = 0;
	while(ftell(f) != total) {
		memset(buffer, 0, 50);
		fgets(buffer, 40, f);
		o = buffer[0] - 'A';
		m = buffer[2] - 'X';
		score += res[o][m];
	}
	printf("%ld\n", score);
}