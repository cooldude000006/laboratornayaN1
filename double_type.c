#include "double_type.h"
#include <stdlib.h>
#include <stdio.h>

//выделение памяти
void* alloc_double(void) {
    double* ptr = (double*)malloc(sizeof(double));
    if (ptr != NULL) {
        *ptr = 0.0;
    }
    return ptr;
}

//освобождение памяти
void dealloc_double(void* ptr) {
    if (ptr!=NULL) {
        free(ptr);
    }
}

//сложение a + b = result
void add_double(const void* a, const void* b, void* result) {
    const double* arg1 = (const double*)a;
    const double* arg2 = (const double*)b;
    double* res = (double*)result;

    *res=*arg1 + *arg2;
}

//умножение a * b = result
void multiply_double(const void* a, const void* b, void* result) {
    const double* arg1 = (const double*)a;
    const double* arg2 = (const double*)b;
    double* res = (double*)result;

    *res=*arg1 * *arg2;
}

//присваивание result = arg
void assign_double (void* result, const void* arg) {
    const double* src = (const double*)arg;
    double* dst = (double*)result;

    *dst = *src;
}

//вывод в консоль
void print_double(const void* element) {
    const double* val = (const double*)element;
    printf("%g", *val);
}

//сравнение с epsilon (защита от погрешности)
int compare_double(const void* a, const void* b) {
    const double* arg1 = (const double*)a;
    const double* arg2 = (const double*)b;

    const double epsilon = 1e-9;
    double diff = *arg1 - *arg2;

    if (diff < -epsilon) return -1;
    if (diff > epsilon) return 1;
    return 0;
}

// запись нуля
void zero_double(void* result) {
    double* res = (double*)result;
    *res=0.0;
}

//запись единицы
void one_double(void* result) {
    double* res = (double*)result;
    *res=1.0;
}

//ленивая инициализация
static TypeInfo* double_type_info = NULL;

const TypeInfo* get_double_type_info(void) {
    if (double_type_info == NULL) {
        double_type_info = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (double_type_info == NULL) {
            return NULL;
        }

        //заполнение таблицы функций
        double_type_info->element_size = sizeof(double);
        double_type_info->add = add_double;
        double_type_info->multiply = multiply_double;
        double_type_info->assign = assign_double;
        double_type_info->alloc = alloc_double;
        double_type_info->dealloc = dealloc_double;
        double_type_info->print = print_double;
        double_type_info->compare = compare_double;
        double_type_info->zero = zero_double;
        double_type_info->one = one_double;
    }
    return double_type_info;
}





