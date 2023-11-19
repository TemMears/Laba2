#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node_stack {
	char value;
	struct Node_stack* next;
} Node_stack;


void push(Node_stack** head, char data) {
	Node_stack* tmp = (Node_stack*)malloc(sizeof(Node_stack));
	tmp->value = data;
	tmp->next = (*head);
	(*head) = tmp;
}
char pop(Node_stack** head) {
	Node_stack* prev = NULL;
	char val;
	if (head == NULL) {
		return NULL;
	}
	prev = (*head);
	if (prev == NULL) {
		return NULL;
	}
	val = prev->value;
	(*head) = (*head)->next;
	free(prev);
	return val;
}

char headstack(Node_stack* head) {
	if (head != NULL) {
		//head = head->next;
		return head->value;
	}

}

bool isOperator(char value) {
	return (value == '+' || value == '-' || value == '*' || value == '/'
		|| value == '^');
}

int prior(char o) {
	if (o == '+' || o == '-') {
		return 1;
	}
	if (o == '*' || o == '/') {
		return 2;
	}
	if (o == '^') {
		return 3;
	}
	return -1;
}

char* infixToPostfix(char* infix, int len, int& size, int& skobka) {
	Node_stack* stack = NULL;
	char* postfix = (char*)malloc(sizeof(char));
	size = 0;
	int j = 0;
	for (int i = 0; i < strlen(infix); i++) {
		if (isalnum(infix[i])) {
			postfix[j++] = infix[i];
			size++;
		}
		if (infix[i] == '(') {
			push(&stack, infix[i]);
			skobka++;
			//len++;
		}
		else if (infix[i] == ')') {
			while (headstack(stack) != '(') {
				postfix[j++] = pop(&stack);
				size++;
			}
			skobka++;
			pop(&stack);
		}
		else if (isOperator(infix[i])) {
			while (headstack(stack) != NULL && prior(headstack(stack)) >= prior(infix[i])) {
				postfix[j++] = pop(&stack);
				size++;
			}
			push(&stack, infix[i]);
		}
	}
	while (headstack(stack) != NULL) {
		if (stack == NULL) {
			break;
		}
		postfix[j++] = pop(&stack);
		size++;
	}
	return postfix;
}

int main()
{
	char infix[72] = "(A+B)*C";
	int len = strlen(infix);
	int size = 0;
	int skobka = 0;
	char* postfix = infixToPostfix(infix, len, size, skobka);
	for (int i = 0; i < strlen(postfix); i++) {
		printf("%c", postfix[i]);
	}
}
