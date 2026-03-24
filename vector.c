#include "vector.h"
#include <stdlib.h>
#include <string.h>

//Функция увлечение вместимости вектра
static int vector_ensure_capacity(Vector* vec, size_t new_capacity) {
    if (new_capacity <= vec->capacity) {
        return 0;
    }
    size_t new_bytes = new_capacity * vec->type_info->element_size;
    void* new_data = realloc(vec->data, new_bytes);

    if (new_data == NULL) {
        return -1;
    }

    vec->data = new_data;
    vec->capacity = new_capacity;
    return 0;
}

// == Основные функции вектора ==

//создание нового вектора
Vector* vector_create(const TypeInfo* type_info, size_t initial_capacity) {
    if (type_info == NULL) {
        return NULL;
    }
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        return NULL;
    }
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }

    vec->type_info = type_info;
    vec->size=0;
    vec->capacity = initial_capacity;

    size_t data_bytes = initial_capacity * type_info->element_size;
    vec->data = malloc(data_bytes);

    if (vec->data == NULL) {
        free(vec);
        return NULL;
    }
    return vec;
}

//уничтожение вектора и освобождение памяти
void vector_destroy(Vector* vec) {
    if (vec == NULL) {
        return;
    }
    if (vec->data != NULL) {
        free(vec->data);
    }
    free(vec);
}

//добавление элемента в вектор
void vector_push(Vector* vec, const void* element) {
    if (vec == NULL || element == NULL) {
        return;
    }
    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        if (vector_ensure_capacity(vec, new_capacity)!=0) {
            return;
        }
    }
    void* dest = (char*)vec->data + (vec->size * vec->type_info->element_size);
    vec->type_info->assign(dest, element);

    vec->size++;
}

//получение элемента по индексу (возврат указателя)
void* vector_get(const Vector* vec, size_t index) {
    if (vec==NULL || index >= vec->size) {
        return NULL;
    }
    return (char*)vec->data + (index * vec->type_info->element_size);
}

//получение текущего размера вектора
size_t vector_size(const Vector* vec) {
    if (vec == NULL) {
        return 0;
    }
    return vec->size;
}

const TypeInfo* vector_get_type_info(const Vector* vec) {
    if (vec == NULL) {
        return NULL;
    }
    return vec->type_info;
}

//очистка вектора (без освобождения памяти)
void vector_clear(Vector* vec) {
    if (vec == NULL) {
        return;
    }
    vec->size = 0;
}

//копирование вектора
Vector* vector_copy(const Vector* vec) {
    if (vec == NULL) {
        return NULL;
    }

    Vector* copy = vector_create(vec->type_info, vec->capacity);
    if (copy == NULL) {
        return NULL;
    }

    // Копируем данные
    size_t bytes = vec->size * vec->type_info->element_size;
    memcpy(copy->data, vec->data, bytes);
    copy->size = vec->size;

    return copy;
}

// == Операции для варианта 1 ==

//сложение векторов
Vector* vector_add(const Vector* v1, const Vector* v2) {
    if (v1 == NULL || v2 == NULL) {
        return NULL;
    }
    if (v1->type_info != v2->type_info) {
        return NULL;
    }
    if (v1->size != v2->size) {
        return NULL;
    }

    Vector* result = vector_create(v1->type_info, v1->capacity);
    if (result == NULL) {
        return NULL;
    }


    void* elem_result = v1->type_info->alloc();
    if ( elem_result == NULL) {
        vector_destroy(result);
        return NULL;
    }

    for (size_t current = 0; current < v1->size; current++) {
        void* elem1 = vector_get(v1,current);
        void* elem2 = vector_get(v2,current);

        v1->type_info->add(elem1,elem2, elem_result);
        vector_push(result,elem_result);
    }

    v1->type_info->dealloc(elem_result);

    return result;
}

//скалярное произведение векторов
void vector_scalar_product(const Vector* v1, const Vector* v2, void* result) {
    if (v1==NULL || v2==NULL || result==NULL) {
        return;
    }
    if (v1->type_info != v2->type_info) {
        return;
    }
    if (v1->size != v2->size) {
        return;
    }

    v1->type_info->zero(result);

    void* product = v1->type_info->alloc();
    void* sum = v1->type_info->alloc();

    if (product == NULL || sum == NULL) {
        if (product != NULL) v1->type_info->dealloc(product);
        if (sum != NULL) v1->type_info->dealloc(sum);
        return;
    }

    for (size_t current = 0; current < v1->size; current++) {
        void* elem1 = vector_get(v1,current);
        void* elem2 = vector_get(v2,current);

        v1->type_info->multiply(elem1,elem2,product);

        v1->type_info->add(result,product,sum);
        v1->type_info->assign(result,sum);
    }

    v1->type_info->dealloc(product);
    v1->type_info->dealloc(sum);
}



