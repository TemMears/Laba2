#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define sizetable 10

typedef struct node {
    char* key;
    void* value;
} node;

typedef struct HashTable {
    node** items;
    int size;
    int count;
} HashTable;

unsigned long hashfunc(char* str) {
    unsigned long i = 0;
        for (int j = 0; str[j]; j++)
        {
            i += str[j];
        }
    return i % sizetable;
}

node* createitem(char* key, char* value) {
    node* item = (node*)malloc(sizeof(node));
    item->key = (char*)malloc(strlen(key) + 1);
    item->value = (char*)malloc(strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item;
}

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (node**)calloc(table->size, sizeof(node*));
    return table;
}

void free_item(node* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        node* item = table->items[i];
        if (item != NULL) {
            free_item(item);
        }
    }
    free(table->items);
    free(table);
}

void insert_item(HashTable* table, node* item) { //добавить элемент
    int index = hashfunc(item->key);

    while (table->items[index] != NULL) { //ищем свободную ячейку
        index = (index + 1) % table->size; //переходим к след ячейке
    }

    table->items[index] = item; 
    table->count++;
}

void pushHashTable(HashTable* table, char* key, char* value) { //функция добавления
    if (table == NULL) {
        return;
    }

    node* item = createitem(key, value);

    if (table->count == table->size) {
        printf("Хэш-таблица заполнена\n");
        return;
    }

    insert_item(table, item);
}

char* searchHashTable(HashTable* table, char* key) { //поиск элемента по ключу
    int index = hashfunc(key);

    while (table->items[index] != NULL) {
        if (strcmp(table->items[index]->key, key) == 0) {
            return table->items[index]->value;
        }
        index = (index + 1) % table->size;
    }

    return NULL;
}

void printHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL) {
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);
        }
    }
}

void delete_item(HashTable* table, int index) {
    free_item(table->items[index]);
    table->items[index] = NULL;
    table->count--;
}

void deleteHashTable(HashTable* table, char* key) {
    int index = hashfunc(key);

    while (table->items[index] != NULL) {
        if (strcmp(table->items[index]->key, key) == 0) {
            delete_item(table, index);
            index = (index + 1) % table->size;

            while (table->items[index] != NULL) {
                node* item = table->items[index];
                delete_item(table, index);
                insert_item(table, item);
                index = (index + 1) % table->size;
            }

            return;
        }

        index = (index + 1) % table->size;
    }
}

int main() {
    HashTable* hashtable = createHashTable(5);

    pushHashTable(hashtable, "grass", "burdock");
    pushHashTable(hashtable, "grass", "cactus");
    pushHashTable(hashtable, "paint", "red");
    pushHashTable(hashtable, "number", "one");
    pushHashTable(hashtable, "number", "ten");

    printHashTable(hashtable);

    return 0;
}
