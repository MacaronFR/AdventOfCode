#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

typedef enum cardinaux{
	NORTH,
	SOUTH,
	EAST,
	WEST
} cardinaux;

typedef enum visibility{
	YES,
	NO,
	UNKNOWN
} visibility;

typedef struct item{
	int value;
	int maxD[4];
	visibility visible;
} item;

item empty = {
		0,
		{-1,-1,-1,-1},
		UNKNOWN
};

item *getNext(item **array, int *y, int *x, cardinaux direction){
	switch (direction) {
		case NORTH:
			(*y)--;
			break;
		case SOUTH:
			(*y)++;
			break;
		case EAST:
			(*x)++;
			break;
		case WEST:
			(*x)--;
			break;
	}
	return &(array[*y][*x]);
}

int getMax(item **array, int y, int x, cardinaux direction){
	item *current = &(array[y][x]);
	item *next = getNext(array, &y, &x, direction);
	if(next->maxD[direction] == -1){
		next->maxD[direction] = getMax(array, y, x, direction);
	}
	if(next->maxD[direction] >= next->value){
		current->maxD[direction] = next->maxD[direction];
	}else{
		current->maxD[direction] = next->value;
	}
	return current->maxD[direction];
}

void setVisibility(item *i){
	i->visible =
			i->maxD[NORTH] >= i->value &&
			i->maxD[EAST] >= i->value &&
			i->maxD[SOUTH] >= i->value &&
			i->maxD[WEST] >= i->value
			? NO
			: YES;
}

int main() {
	// READ FILE INIT
	char buffer[110] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	item **array;
	int nLine = 0;
	size_t col;
	size_t tot = 0;

	//START READ FILE
	while(ftell(f) != total) {
		memset(buffer, 0, 110);
		fgets(buffer, 105, f);
		nLine++;
	}
	fseek(f, 0, SEEK_SET);
	memset(buffer, 0, 110);
	fgets(buffer, 105, f);
	col = strlen(buffer) - 1;
	fseek(f, 0, SEEK_SET);

	array = malloc(sizeof(item *) * (nLine));

	for(int i = 0; i < nLine; ++i){
		memset(buffer, 0, 110);
		fgets(buffer, 105, f);
		array[i] = malloc(sizeof(item) * col);
		for(int j = 0; j < col; ++j){
			array[i][j] = empty;
			array[i][j].value = buffer[j] - '0';
			if(i == 0){
				array[i][j].visible = YES;
				array[i][j].maxD[NORTH] = 0;
			}
			if(j == 0){
				array[i][j].visible = YES;
				array[i][j].maxD[WEST] = 0;
			}
			if(i == nLine - 1){
				array[i][j].visible = YES;
				array[i][j].maxD[SOUTH] = 0;
			}
			if(j == col - 1){
				array[i][j].visible = YES;
				array[i][j].maxD[EAST] = 0;
			}
		}
	}

	for(int i = 1; i < nLine - 1; ++i){
		for(int j = 1; j < col - 1; ++j){
			getMax(array, i, j, NORTH);
			getMax(array, i, j, SOUTH);
			getMax(array, i, j, EAST);
			getMax(array, i, j, WEST);
			setVisibility(&(array[i][j]));
		}
	}

	for(int i = 0; i < nLine; ++i){
		for (int j = 0; j < col; ++j) {
			if(array[i][j].visible == YES){
				printf("V");
				tot++;
			}else{
				printf("X");
			}
		}
		printf("\n");
	}
	printf("Total = %lu\n", tot);
}