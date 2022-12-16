#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

typedef struct item {
	int value;
	int *modulo;
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
	unsigned long inspection;
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

void newStress(monkey *m, int *modulos, int tot, const int *tests){
	for(int i = 0; i < tot; ++i) {
		int op1 = m->op1Old ? modulos[i] : m->op1;
		int op2 = m->op2Old ? modulos[i] : m->op2;
		switch (m->operation) {
			case '*':
				modulos[i] = (op1 * op2) % tests[i];
				break;
			case '+':
				modulos[i] = (op1 + op2) % tests[i];
				break;
			case '-':
				modulos[i] = (op1 - op2) % tests[i];
				break;
			case '/':
				modulos[i] = (op1 / op2) % tests[i];
				break;
		}
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
	int *tests = NULL;
	int totMonkey = 0;

	memset(monkeys, 0, sizeof(monkeys));

	//START READ FILE
	while (ftell(f) != total) {
		memset(buffer, 0, 110);
		fgets(buffer, 105, f);
		if (buffer[0] == 'M') {
			monkeys[totMonkey] = createMonkey();
			current = monkeys[totMonkey];
			totMonkey++;
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
				tests = realloc(tests, sizeof(int) * totMonkey);
				tests[totMonkey-1] = tot;
			} else if (buffer[2] == ' ') {
				if (buffer[7] == 't') {
					current->ifTrue = atoi(buffer + 29);
				} else {
					current->ifFalse = atoi(buffer + 30);
				}
			}
		}
	}

	for(int i = 0; i < totMonkey; ++i){
		item *currentItem = monkeys[i]->list;
		while(currentItem != NULL){
			currentItem->modulo = malloc(sizeof(int) * totMonkey);
			for(int j = 0; j < totMonkey; ++j){
				currentItem->modulo[j] = currentItem->value % tests[j];
			}
			currentItem = currentItem->next;
		}
	}

	for(int i = 0; i < 10000; ++i){
		turn = 0;
		while(monkeys[turn] != NULL){
			current = monkeys[turn];
			while(current->list != NULL){
				current->inspection++;
				newStress(current, current->list->modulo, totMonkey, tests);
				if(current->list->modulo[turn] == 0){
//				if(current->list->value % current->test == 0){
					monkeys[current->ifTrue]->list = addItemAtEnd(removeRoot(&current->list), monkeys[current->ifTrue]->list);
				}else{
					monkeys[current->ifFalse]->list = addItemAtEnd(removeRoot(&current->list), monkeys[current->ifFalse]->list);
				}
			}
			turn++;
		}
		if(i == 0 || i == 19 || i == 999 || i == 1999 || i == 2999 || i == 3999 || i == 4999|| i == 5999 || i == 6999 || i == 7999 || i == 8999 || i == 9999){
			printf("1 => %lu\n2 => %lu\n3 => %lu\n4 => %lu\n=====================================\n", monkeys[0]->inspection, monkeys[1]->inspection, monkeys[2]->inspection, monkeys[3]->inspection);
		}
	}

	turn = 0;
	unsigned long max1 = 0;
	unsigned long max2 = 0;
	while(monkeys[turn] != NULL){
		if(monkeys[turn]->inspection > max1){
			max2 = max1;
			max1 = monkeys[turn]->inspection;
		}else if(monkeys[turn]->inspection > max2){
			max2 = monkeys[turn]->inspection;
		}
		turn++;
	}
 	printf("Total = %lu by %lu * %lu", max1 * max2, max1, max2);
}