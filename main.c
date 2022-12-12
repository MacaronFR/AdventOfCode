#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

typedef struct item{
	int x;
	int y;
	struct item *next;
} item;

item *addItem(int x, int y, item *root){
	item *new = malloc(sizeof(item));
	new->x = x;
	new->y = y;
	new->next = root;
	return new;
}

bool isIn(item *root, int x, int y){
	while(root != NULL){
		if(x == root->x && y == root->y){
			return true;
		}
		root = root->next;
	}
	return false;
}

int main() {
	// READ FILE INIT
	char buffer[110] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	item *root = addItem(0, 0, NULL);
	item *tmp;
	int xTail = 0;
	int yTail = 0;
	int xHead = 0;
	int yHead = 0;
	int tot = 0;
	char dir;
	int amount;

	//START READ FILE
	while(ftell(f) != total) {
		memset(buffer, 0, 110);
		fgets(buffer, 105, f);
		sscanf(buffer, "%c %d", &dir, &amount);
		for(int i = 0; i < amount; ++i) {
			switch (buffer[0]) {
				case 'L':
					xHead--;
					break;
				case 'R':
					xHead++;
					break;
				case 'U':
					yHead++;
					break;
				case 'D':
					yHead--;
					break;
			}
			if (abs(xHead - xTail) > 1) {
				if (yHead != yTail) {
					yTail = yHead;
				}
				xTail += (xHead - xTail) / 2;
			} else if (abs(yHead - yTail) > 1) {
				if (xHead != xTail) {
					xTail = xHead;
				}
				yTail += (yHead - yTail) / 2;
			}
			if (!isIn(root, xTail, yTail)) {
				root = addItem(xTail, yTail, root);
			}
		}
	}

	while(root != NULL){
		tot++;
		tmp = root->next;
		free(root);
		root = tmp;
	}

	printf("Total = %d", tot);
}