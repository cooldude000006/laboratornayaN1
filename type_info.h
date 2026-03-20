#pragma once
#include <stddef.h>


// Типы указателей на функции операций


// Бинарная операция (сложение, умножение)
typedef void (*BinaryOperator)(const void* a, const void* b, void* result);

// Унарная операция (присваивание)
typedef void (*UnaryOperator)(void* result, const void* arg);

// Выделение памяти под элемент
typedef void* (*Allocator)(void);

// Освобождение памяти элемента
typedef void (*Deallocator)(void* ptr);

// Вывод элемента в консоль
typedef void (*PrintFunc)(const void* element);

// Сравнение элементов (для тестов) — ВОЗВРАЩАЕТ int!
typedef int (*CompareFunc)(const void* a, const void* b);

// Получение нулевого значения типа
typedef void (*ZeroFunc)(void* result);

// Получение единичного значения типа
typedef void (*OneFunc)(void* result);


// Структура описания типа (TypeInfo)
typedef struct {
    size_t element_size;      // Размер элемента в байтах
    BinaryOperator add;       // Функция сложения
    BinaryOperator multiply;  // Функция умножения (для скалярного произведения)
    UnaryOperator assign;     // Функция присваивания
    Allocator alloc;          // Функция выделения памяти под элемент
    Deallocator dealloc;      // Функция освобождения памяти
    PrintFunc print;          // Функция вывода элемента
    CompareFunc compare;      // Функция сравнения (для тестов) — возвращает int
    ZeroFunc zero;            // Функция получения нуля
    OneFunc one;              // Функция получения единицы
} TypeInfo;