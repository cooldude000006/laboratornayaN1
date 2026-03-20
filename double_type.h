#pragma once
#include "type_info.h"

const TypeInfo* get_double_type_info(void);

// Вспомогательные функции для работы с double (функции в type_info.c)
void* alloc_double(void);

void dealloc_double(void* ptr);

void add_double(const void* a,const void* b, void* result);

void multiply_double(const void* a, const void* b, void* result);

void assign_double(void* result, const void* arg);

void print_double(const void* element);

int compare_double(const void* a, const void* b);

void zero_double(void* result);

void one_double(void* result);
