#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define sizetable 20

typedef struct node_arr {
    const char* value;
} node_arr;

typedef struct Array {
    struct Array** items;
    unsigned int size;
    int count;
} Array;

unsigned long hashfuncarr(const char* val)
{
    unsigned long i = 0;
    for (int j = 0; val[j]; j++)
    {
        i += val[j] * j;
    }
    return i % sizetable;
}

node_arr* createit(const char* value)
{
    node_arr* item = (node_arr*)malloc(sizeof(node_arr));
    item->value = (char*)malloc(strlen(value) + 1);
    strcpy(item->value, value);

    return item; //„r„€„x„r„‚„p„‹„p„u„} „…„{„p„x„p„„„u„|„Ž „~„p „„|„u„}„u„~„„
}

Array* cteateArr(int size)
{
    Array* table = (Array*)malloc(sizeof(Array));
    table->size = size;
    table->count = 0;
    table->items = (node_arr**)calloc(table->size, sizeof(node_arr*));
    for (int i = 0; i < table->size; i++)
    {
        table->items[i] = NULL;
        return table;
    }
}

void pushArr(Array* arr, const char* value)
{
    if (arr == NULL)
    {
        return;
    }
    node_arr* item = createit(value);  //„ƒ„€„x„t„p„v„} „„|„u„}„u„~„„
    int index = hashfuncarr(value);
    node_arr* current_item = arr->items[index];
    if (arr->count == arr->size) {
            return;
        }
    arr->items[index] = item;
    arr->count++;
}

void printarr(Array* arr)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->items[i])
        {
            node_arr* tmp = arr->items[i];
            printf("Index:%d, Value:%s\n", i, tmp->value);
        }
    }
    printf("\n\n");
}


void printSubarray(char* arr[], int subarray[], int size) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%s, ", arr[subarray[i]]);
    }
    printf("}\n");
}

void generateSubarrays(char* arr[], int n) {
    int numSubarrays = pow(2, n); //„t„|„‘ „r„„‰„y„ƒ„|„u„~„y„‘ „{„€„|„y„‰„u„ƒ„„„r„p „„€„t„}„p„ƒ„ƒ„y„r„€„r
    for (int i = 0; i < numSubarrays; i++) {
        int* subarray = (int*)malloc(n * sizeof(int));
        int size = 0;
        int temp = i;
        for (int j = 0; j < n; j++) { //„„€„|„…„‰„p„u„} „„€„t„}„p„ƒ„ƒ„y„r
            if (temp % 2 == 1) {
                subarray[size] = j;
                size++;
            }
            temp /= 2;
        }

        printSubarray(arr, subarray, size);

        free(subarray);
    }
}

int main() {
    char* arr[3] = { "1", "2", "3" };
    int n = sizeof(arr) / sizeof(arr[0]);

    generateSubarrays(arr, n);

    return 0;
}
