#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

typedef struct item {
	int value;
	struct item *next;
} item;

typedef struct monkey{
	item *list;
	char operation;
	bool op1Old;
	bool op2Old;
	int op1;
	int op2;
	int test;
	int ifTrue;
	int ifFalse;
	int inspection;
} monkey;

monkey *createMonkey(){
	monkey *m = malloc(sizeof(monkey));
	m->list = NULL;
	m->inspection = 0;
	return m;
}

item *addAtEnd(int value, item *root){
	if(root != NULL){
		root->next = addAtEnd(value, root->next);
		return root;
	}
	item *res = malloc(sizeof(item));
	res->value = value;
	res->next = NULL;
	return res;
}

item *addItemAtEnd(item *toAdd, item *root){
	if(root != NULL){
		root->next = addItemAtEnd(toAdd, root->next);
		return root;
	}
	toAdd->next = NULL;
	return toAdd;
}

item *removeRoot(item **root){
	item *res = *root;
	(*root) = res->next;
	return res;
}

int newStress(monkey *m, int value){
	int op1 = m->op1Old ? value : m->op1;
	int op2 = m->op2Old ? value : m->op2;
	switch (m->operation) {
		case '*':
			return op1 * op2;
		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		case '/':
			return op1 / op2;
	}
}

int main() {
	// READ FILE INIT
	char buffer[110] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	int tot = 0;
	int turn = 0;
	monkey *monkeys[20];
	monkey *current;
	char *number;

	memset(monkeys, 0, sizeof(monkeys));

	//START READ FILE
	while (ftell(f) != total) {
		memset(buffer, 0, 110);
		fgets(buffer, 105, f);
		if (buffer[0] == 'M') {
			monkeys[turn] = createMonkey();
			current = monkeys[turn];
			turn++;
		} else if (buffer[0] == ' ') {
			if (buffer[2] == 'S') {
				number = strtok(buffer + 18, ",");
				while (number != NULL) {
					current->list = addAtEnd(atoi(number), current->list);
					number = strtok(NULL, ",");
				}
			} else if (buffer[2] == 'O') {
				number = strtok(buffer + 19, " ");
				if (strcmp("old", number) == 0) {
					current->op1Old = true;
				} else {
					current->op1Old = false;
					current->op1 = atoi(number);
				}
				number = strtok(NULL, " ");
				current->operation = number[0];
				number = strtok(NULL, " ");
				if (strncmp("old", number, 3) == 0) {
					current->op2Old = true;
				} else {
					current->op2Old = false;
					current->op2 = atoi(number);
				}
			} else if (buffer[2] == 'T') {
				sscanf(buffer, "  Test: divisible by %d", &tot);
				current->test = tot;
			} else if (buffer[2] == ' ') {
				if (buffer[7] == 't') {
					current->ifTrue = atoi(buffer + 29);
				} else {
					current->ifFalse = atoi(buffer + 30);
				}
			}
		}
	}

	for(int i = 0; i < 20; ++i){
		turn = 0;
		while(monkeys[turn] != NULL){
			current = monkeys[turn];
			while(current->list != NULL){
				current->inspection++;
				current->list->value = newStress(current, current->list->value) / 3;
				if(current->list->value % current->test == 0){
					monkeys[current->ifTrue]->list = addItemAtEnd(removeRoot(&current->list), monkeys[current->ifTrue]->list);
				}else{
					monkeys[current->ifFalse]->list = addItemAtEnd(removeRoot(&current->list), monkeys[current->ifFalse]->list);
				}
			}
			turn++;
		}
	}

	turn = 0;
	int max1 = 0;
	int max2 = 0;
	while(monkeys[turn] != NULL){
		if(monkeys[turn]->inspection > max1){
			max2 = max1;
			max1 = monkeys[turn]->inspection;
		}else if(monkeys[turn]->inspection > max2){
			max2 = monkeys[turn]->inspection;
		}
		turn++;
	}
 	printf("Total = %d by %d * %d", max1 * max2, max1, max2);
}