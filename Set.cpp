#include <stdio.h>
#include <stdlib.h>

typedef struct node_set {
	const char* value;
	bool check;
} node_set;

typedef struct Set {
	node_set settabl[10];
	unsigned int size;
} Set;

Set* createSet() {
	Set* set = (Set*)malloc(sizeof(Set));
	set->settabl[0].value = NULL;
	set->settabl[0].check = false;
	return set;
}

int hashFunc(const char* value, int* size) {
	int x = *size;
	int hashValue = 0;
	for (int i = 0; value[i] != '\0'; i++) {
		hashValue += value[i];
	}
	return hashValue % x;
}

void pushset(Set* set, const char* value, int* size) {
	int index = hashFunc(value, size);
	for (index; index <= *size;) {
		if (set->settabl[index].check) {
			if (set->settabl[index].value == value) {
				//printf("„N„u „…„~„y„{„p„|„Ž„~„„z „„|„u„}„u„~„„\n");
				return;
			}
			index = (index + 1) % *size;
		}
		if (set->settabl[index].check == false) {
			break;
		}
	}
	(*size)++;
	set->settabl[index].value = value;
	set->settabl[index].check = true;
	set->settabl[index + 1].value = NULL;
	set->settabl[index + 1].check = false;
}

int popset(Set* set, const char* value, int* size) {
	for (int index = 0; index <= *size;) {
		if (set->settabl[index].check) {
			if (set->settabl[index].value == value) {
				set->settabl[index].value = NULL;
				set->settabl[index].check = false;
				return 0;
			}
			index++;
		}
		if (set->settabl[index].check == false) {
			break;
		}
	}
	(*size)--;
	return 1;
}

int readSet(const Set* set, const char* value, int* size) {
	int index = hashFunc(value, size);

	while (set->settabl[index].check) {
		if (set->settabl[index].value == value) {
			//printf("Element %s is in structure\n", value);
			return 1;
		}
		index = (index + 1) % *size;
	}

	//printf("Element %s is not in structure\n", value);
	return 0;
}

void printSet(Set* set, int* size) {
	for (int i = 0; i < *size; i++) {
		if (set->settabl[i].check)
		{
			printf("%s ", set->settabl[i].value);
		}
	}
	printf("\n");
}

Set* unionofsets(Set* set1, Set* set2, int* size1, int* size2, int* size3) {
	Set* set3 = createSet();
	for (int i = 0; i < *size1; i++) {
		if (set1->settabl[i].value != NULL) {
			pushset(set3, set1->settabl[i].value, size3);
		}
	}
	for (int i = 0; i < *size2; i++) {
		if (set2->settabl[i].check) {
			pushset(set3, set2->settabl[i].value, size3);
		}
	}
	return set3;
}

Set* intersection(Set* set1, Set* set2, int* size1, int* size2, int* size3) {
	Set* set3 = createSet();
	for (int i = 0; i < *size1; i++) {
		for (int j = 0; j < *size2; j++) {
			if (set1->settabl[i].check && set2->settabl[j].check) {
				if (set1->settabl[i].value == set2->settabl[j].value) {
					pushset(set3, set1->settabl[i].value, size3);
				}
			}
		}
	}
	return set3;
}

Set* setdifference(Set* set1, Set* set2, int* size1, int* size2, int* size3) {
	Set* set3 = createSet();
	for (int i = 0; i < *size1; i++) {
		if (set1->settabl[i].check) {
			if (readSet(set2, set1->settabl[i].value, size2) == 0) {
				pushset(set3, set1->settabl[i].value, size3);
			}
		}
	}

	for (int i = 0; i < *size2; i++) {
		if (set2->settabl[i].check) {
			if (readSet(set1, set2->settabl[i].value, size1) == 0) {
				pushset(set3, set2->settabl[i].value, size3);
			}
		}
	}

	return set3;
}

int main() {
	Set* Set1 = createSet();
	Set* Set2 = createSet();
	int size1 = 1;
	int size2 = 1;
	pushset(Set1, "l", &size1);
	pushset(Set1, "g", &size1);
	pushset(Set1, "k", &size1);
	printSet(Set1, &size1);
	printf("\n");
	pushset(Set2, "o", &size2);
	pushset(Set2, "p", &size2);
	pushset(Set2, "l", &size2);
	printSet(Set2, &size2);
	printf("\n");
	int size3 = 1;
	Set* unionset = unionofsets(Set1, Set2, &size1, &size2, &size3);
	printSet(unionset, &size3);
	printf("\n");
	int size4 = 1;
	Set* intersectionset = intersection(Set1, Set2, &size1, &size2, &size4);
	printSet(intersectionset, &size4);
	printf("\n");
	int size5 = 1;
	Set* difference = setdifference(Set1, Set2, &size1, &size2, &size5);
	printSet(difference, &size5);
	printf("\n");
}