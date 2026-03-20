#pragma once
#include "type_info.h"

const TypeInfo* get_int_type_info(void);

//вспомогательные функции для работы с int (функции внутри type_info)
void* alloc_int(void);

void dealloc_int(void* ptr);

void add_int(const void* a, const void* b, void* result);

void multiply_int(const void* a, const void* b, void* result);

void assign_int(void* result, const void* arg);

void print_int(const void* element);

int compare_int(const void* a, const void* b);

void zero_int(void* result);

void one_int(void* result);