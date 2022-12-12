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

typedef struct item{
	int value;
	int visibilityD[4];
	int total;
} item;

item empty = {
		0,
		{-1,-1,-1,-1},
		-1
};

void getVisibility(item **array, int y, int x);

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

int getVisibilityDirection(item **array, int y, int x, cardinaux direction, bool start, int height){
	item *current = &(array[y][x]);
	if(!start && (current->value >= height || current->visibilityD[direction] == 0)){
		return 1;
	}
	getNext(array, &y, &x, direction);
	return getVisibilityDirection(array, y, x, direction, false, height) + (start ? 0 : 1);
}

void setTotal(item *i){
	i->total = i->visibilityD[NORTH] * i->visibilityD[EAST] * i->visibilityD[SOUTH] * i->visibilityD[WEST];
}

void getVisibility(item **array, int y, int x){
	array[y][x].visibilityD[NORTH] = getVisibilityDirection(array, y, x, NORTH, true, array[y][x].value);
	array[y][x].visibilityD[EAST] = getVisibilityDirection(array, y, x, EAST, true, array[y][x].value);
	array[y][x].visibilityD[SOUTH] = getVisibilityDirection(array, y, x, SOUTH, true, array[y][x].value);
	array[y][x].visibilityD[WEST] = getVisibilityDirection(array, y, x, WEST, true, array[y][x].value);
	setTotal(&(array[y][x]));
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
	int max = 0;

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
				array[i][j].total = 0;
				array[i][j].visibilityD[NORTH] = 0;
			}
			if(j == 0){
				array[i][j].total = 0;
				array[i][j].visibilityD[WEST] = 0;
			}
			if(i == nLine - 1){
				array[i][j].total = 0;
				array[i][j].visibilityD[SOUTH] = 0;
			}
			if(j == col - 1){
				array[i][j].total = 0;
				array[i][j].visibilityD[EAST] = 0;
			}
		}
	}

	for(int i = 1; i < nLine - 1; ++i){
		for (int j = 1; j < col - 1; ++j) {
			getVisibility(array, i, j);
		}
	}

	for(int i = 0; i < nLine; ++i){
		for (int j = 0; j < col; ++j) {
			printf("%d ", array[i][j].total);
			if(array[i][j].total > max){
				max = array[i][j].total;
			}
		}
		printf("\n");
	}
	printf("Total = %d\n", max);
}