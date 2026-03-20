#pragma once
#include "type_info.h"

typedef struct {
    void* data;
    size_t size;
    size_t capacity;
    const TypeInfo* type_info;
}Vector;
//Основные функции вектора
Vector* vector_create(const TypeInfo* type_info, size_t initial_capacity);

void vector_destroy(Vector* vec);

void vector_push(Vector* vec, const void* element);

void* vector_get(const Vector* vec, size_t index);

size_t vector_size(const Vector* vec);

const TypeInfo* vector_get_type_info(const Vector* vec);

//======
//Векторное сложение
Vector* vector_add(const Vector* v1, const Vector* v2);
//Векторное произведение
void vector_scalar_product(const Vector* v1, const Vector* v2, void* result);
//======

Vector* vector_copy(const Vector* vec);

void vector_clear(Vector* vec);