#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define GETVALUE(x) (*(int*)ptr)

struct List{
    void* pVoid;
    int length;
    size_t size;
};

typedef struct List List;


bool checkValid(int index, List* list){
    if (index < 0 || list->length <= index){
        printf("Out of Bounds :(");
        return false;
    }
    return true;
}


void append(int value, List* list){
    list->pVoid = realloc(list->pVoid, list->length * list->size);

    int* newValuePtr = list->pVoid + list->length * list->size;
    *newValuePtr = value;

    list->length += 1;
}

void set(int index, int value, List* list){
    int* ValuePtr = list->pVoid + index * list->size;

    if (checkValid(index, list)){
        return;
    }

    *ValuePtr = value;
}

void delete(int index, List* list){
    int* ValuePtr = list->pVoid + index * list->size;

    if (checkValid(index, list)){
        return;
    }

    for (int i = 0; i < list->length - index; ++i) {
        int *currentPtr = ValuePtr + i;
        *currentPtr = *(currentPtr + 1);
    }
    list->pVoid = realloc(list->pVoid, list->length * list->size - 1);
    list->length -= 1;
}

void insert(int index, int value, List* list){

    if (checkValid(index, list)){
        return;
    }

    list->length += 1;
    list->pVoid = realloc(list->pVoid, list->length * list->size);

    int* lPtr = list->pVoid + list->size * index;
    int* rPtr = list->pVoid + list->size * list->length;

    int lVal = *(lPtr);
    int temp;

    for (; lPtr < rPtr; lPtr++) {
        temp = *lPtr;
        *lPtr = lVal;
        lVal = temp;
    }
    set(index, value, list);
}


void print(List* list){
    printf("[");
    for (int i = 0; i < list->length; ++i) {
        int* p = list->pVoid + i * list->size;
        printf("%d, ", *p);
    }
    printf("]");
}

List new(int NumOfElements){
    List list;
    list.pVoid = calloc(NumOfElements, sizeof(int));
    list.length = NumOfElements;
    list.size = sizeof(int);
    return list;
}

int main() {
    List list = new(1);

    for (int i = 0; i < 10; ++i) {
        append(i, &list);
    }

    set(0, 10, &list);


    print(&list);
}
