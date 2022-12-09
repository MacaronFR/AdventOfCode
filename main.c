#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void readLine(char *buffer, int size, FILE *stream){
	memset(buffer, 0, 100);
	fgets(buffer, size, stream);
	buffer[strlen(buffer) - 1] = 0;
}

typedef struct item item;

typedef struct file {
	char *name;
	size_t size;
} file;

typedef struct dir {
	item **items;
	size_t size;
	char *name;
	struct dir *parent;
} dir;

typedef enum type {
	DIR,
	FIL
}type;

typedef union item_value {
	file f;
	dir d;
} item_value;

struct item {
	item_value value;
	type valueType;
};

size_t countItems(item **items){
	if(items == NULL){
		return 0;
	}
	size_t count = 0;
	while(items[count] != NULL){
		count++;
	}
	return count;
}

void addItem(dir *current, type t, char *name, size_t size){
	size_t newSize = countItems(current->items) + 1;
	current->items = realloc(current->items, sizeof(item*) * (newSize + 1));
	item *i = malloc(sizeof(item));
	i->valueType = t;
	switch (t) {
		case FIL:
			i->value.f.size = size;
			i->value.f.name = name;
			break;
		case DIR:
			i->value.d.size = size;
			i->value.d.name = name;
			i->value.d.items = NULL;
			i->value.d.parent = current;
			break;
	}
	current->items[newSize-1] = i;
	current->items[newSize] = NULL;
}

dir *searchDir(item **items, const char *search){
	while(*items != NULL){
		if((*items)->valueType == DIR){
			if(strcmp((*items)->value.d.name, search) == 0){
				return &(*items)->value.d;
			}
		}
		items++;
	}
	return NULL;
}

void cd(dir *root, const char *line, dir **current){
	if(line[2] == 'c' && line[3] == 'd'){
		const char *path = line + 5;
		if(path[0] == '/'){
			*current = root;
		}else if(path[0] == '.' && path[1] == '.') {
			*current = (*current)->parent;
		}else{
			*current = searchDir((*current)->items, path);
		}
	}
}

void ls(dir *current, char *line, FILE *f){
	if(line[2] == 'l' && line[3] == 's'){
		readLine(line, 90, f);
		do{
			if(strncmp(line, "dir", 3) == 0){
				char *name = malloc(sizeof(char) * (strlen(line + 4) + 1));
				strcpy(name, line+4);
				addItem(current, DIR, name, 0);
			}else{
				int i = 0;
				while(isdigit(line[i++]));
				line[i] = 0;
				char *name = malloc(sizeof(char) * (strlen(line+i+1) + 1));
				strcpy(name, line+i+1);
				size_t size = atoi(line);
				addItem(current, FIL, name, size);
			}
			readLine(line, 90, f);
		}while (line[0] != '$' && line[0] != 0);
	}
}

size_t calcSize(dir *root){
	int i = 0;
	while(root->items[i] != NULL){
		if(root->items[i]->valueType == DIR){
			root->size += calcSize(&(root->items[i]->value.d));
		}else{
			root->size += root->items[i]->value.f.size;
		}
		i++;
	}
	return root->size;
}

size_t calcUnder100000Size(dir *root){
	int i = 0;
	size_t total = 0;
	while(root->items[i] != NULL){
		if(root->items[i]->valueType == DIR){
			if(root->items[i]->value.d.size < 100000){
				total += root->items[i]->value.d.size;
			}
			total += calcUnder100000Size(&(root->items[i]->value.d));
		}
		i++;
	}
	return total;
}

int main() {
	// READ FILE INIT
	char buffer[100] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	dir root = {
			NULL,
			0,
			"/",
			NULL
	};
	dir *current = &root;

	//START READ FILE
	while(ftell(f) != total) {
		readLine(buffer, 90, f);
		if(buffer[0] == '$'){
			ls(current, buffer, f);
			cd(&root, buffer, &current);
		}
	}
	calcSize(&root);
	printf("Total = %lu\n", calcUnder100000Size(&root));
	return 0;
}