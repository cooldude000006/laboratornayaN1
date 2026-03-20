#include "int_type.h"
#include <stdlib.h>
#include <stdio.h>

//выделение памяти
void* alloc_int(void) {
    int* ptr = (int*) malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 0;
    }
    return ptr;
}

//освобождение памяти
void dealloc_int (void* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

//сложение a + b = result
void add_int(const void* a, const void* b, void* result) {
    const int* arg1 = (const int*) a;
    const int* arg2 = (const int*) b;
    int* res = (int*)result;

    *res = *arg1 + *arg2;
}

//умножение a * b = result
void multiply_int(const void* a, const void* b, void* result) {
    const int* arg1 = (const int*) a;
    const int* arg2 = (const int*) b;
    int* res = (int*)result;

    *res = *arg1 * *arg2;
}

//присвание result = arg
void assign_int(void* result, const void* arg) {
    const int* src = (const int*) arg;
    int* dst = (int*)result;

    *dst = *src;
}

//вывод в консоль
void print_int(const void* element) {
    const int* val = (const int*) element;
    printf("%d", *val);
}

//сравнение
int compare_int(const void* a, const void* b) {
    const int* arg1 = (const int*) a;
    const int* arg2 = (const int*) b;

    if (*arg1 < *arg2) return -1;
    if (*arg1 > *arg2) return 1;
    return 0;
}

//запись нуля
void zero_int(void* result) {
    int* res = (int*)result;
    *res = 0;
}

//запись единицы
void one_int(void* result) {
    int* res = (int*)result;
    *res = 1;
}

//ленивая инициализация
static TypeInfo* int_type_info = NULL;

const TypeInfo* get_int_type_info(void) {
    if (int_type_info == NULL) {
        int_type_info = (TypeInfo*)malloc(sizeof(TypeInfo));

        if (int_type_info == NULL) {
            return NULL;
        }

        //заполнение таблицы функций
        int_type_info->element_size = sizeof(int);
        int_type_info->add = add_int;
        int_type_info->multiply = multiply_int;
        int_type_info->assign = assign_int;
        int_type_info->alloc = alloc_int;
        int_type_info->dealloc = dealloc_int;
        int_type_info->print = print_int;
        int_type_info->compare = compare_int;
        int_type_info->zero = zero_int;
        int_type_info->one = one_int;
    }
    return int_type_info;
}


