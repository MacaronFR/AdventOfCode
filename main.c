#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct node{
	char value;
	struct node *bellow;
} node;

typedef struct stack{
	node *top;
} stack;

node *pop(stack *s, int level){
	if(s == NULL || s->top == NULL){
		return NULL;
	}
	node *res = s->top;
	node *n = s->top;
	for(int i = 1; i < level; ++i){
		n = n->bellow;
	}
	s->top  = n->bellow;
	n->bellow = NULL;
	return res;
}

void push(stack *s, node *n){
	if(n == NULL || s == NULL){
		return;
	}
	node *tmp = n;
	while(tmp->bellow){
		tmp = tmp->bellow;
	}
	tmp->bellow = s->top;
	s->top = n;
}

node *createNode(char value){
	node *n = malloc(sizeof(node));
	n->bellow = NULL;
	n->value = value;
	return n;
}

stack *createStack(){
	stack *s = malloc(sizeof(stack));
	s->top = NULL;
	return s;
}

stack **initStacks(FILE *f, int *nStack){
	stack **stacks;
	char buffer[100] = {0};
	char **lines = NULL;
	char *tmp;
	int nLine = 0;
	(*nStack) = 0;
	while(true){
		memset(buffer, 0, 100);
		fgets(buffer, 90, f);
		if(buffer[0] == '['){
			nLine++;
			lines = realloc(lines, sizeof(char*) * nLine);
			lines[nLine-1] = malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(lines[nLine-1], buffer);
		}else{
			tmp = buffer + 1;
			while(*tmp){
				if(*tmp == ' ' && tmp[-1] != ' '){
					(*nStack)++;
				}
				tmp++;
			}
			break;
		}
	}
	stacks = malloc(sizeof(stack*) * *nStack);
	for(int i = 0; i < *nStack; ++i){
		stacks[i] = createStack();
	}
	for(int i = nLine - 1; i >= 0; i--){
		tmp = lines[i];
		for(int j = 0; j < *(nStack); ++j){
			if(isalpha(tmp[j*4+1])){
				push(stacks[j], createNode(tmp[j*4+1]));
			}
		}
		free(lines[i]);
	}
	free(lines);
	return stacks;
}

int main() {
	// READ FILE INIT
	char buffer[100] = {0};
	FILE *f = fopen("../data", "r");
	fseek(f, 0, SEEK_END);
	long total = ftell(f);
	fseek(f, 0, SEEK_SET);

	//START CUSTOM VARIABLE
	int stacksNumber = 0;
	stack **stacks = initStacks(f, &stacksNumber);
	int move, from, to;

	//START READ FILE
	while(ftell(f) != total) {
		memset(buffer, 0, 100);
		fgets(buffer, 90, f);
		int lec = sscanf(buffer, "move %d from %d to %d", &move, &from, &to);
		if(lec == 3) {
			push(stacks[to - 1], pop(stacks[from - 1], move));
		}
	}
	for(int i = 0; i < stacksNumber; ++i){
		printf("%c", stacks[i]->top->value);
	}
}