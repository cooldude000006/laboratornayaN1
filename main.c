#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "int_type.h"
#include "double_type.h"
#include"tests.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void clear_input_buffer(void) {
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
}

//вывод вектора в консоль
void print_vector(const Vector* vec) {
    if (vec==NULL) {
        printf("NULL\n");
        return;
    }
    printf("[");

    for (size_t current=0; current<vector_size(vec); current++) {
        if (current>0) {
            printf(", ");
        }
        vec->type_info->print(vector_get(vec,current));
    }
    printf("]\n");
}

//ввод вектора от пользователя
Vector* input_vector(const TypeInfo* type_info) {
    size_t size;

    printf("введите размер вектора: ");

    if (scanf("%zu",&size)!=1 || size == 0) {
        printf("ошибка ввода, число должно быть положительным\n");
        clear_input_buffer();
        return NULL;
    }

    Vector* vec = vector_create(type_info,size);
    if (vec==NULL) {
        printf("ошибка выделения памяти\n");
        return NULL;
    }

    printf("введите %zu элементов \n", size);
    for (size_t current=0; current<size; current++) {
        void* elem = type_info->alloc();
        if (elem==NULL) {
            printf("ощибка выделения памяти для элемента");
            vector_destroy(vec);
            return NULL;
        }

        if (type_info == get_int_type_info()) {
            if (scanf("%d", (int*)elem)!=1) {
                printf("ошибка ввода элемента\n");
                clear_input_buffer();
                type_info->dealloc(elem);
                vector_destroy(vec);
                return NULL;
            }
        }else {
            if (scanf("%d", (int*)elem)!=1) {
                printf("ошибка ввода элемента\n");
                clear_input_buffer();
                type_info->dealloc(elem);
                vector_destroy(vec);
                return NULL;
            }
        }
        vector_push(vec,elem);

        type_info->dealloc(elem);
    }
    return vec;
}

//КОНСОЛЬНОЕ МЕНЮ
int main(void) {

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    int choice;
    Vector* v1 = NULL;
    Vector* v2 = NULL;
    const TypeInfo* current_type = NULL;

    //главный цикл
    while (1) {
        printf("\n");
        printf("  Лабораторная работа №1 (Вариант 1)   \n");
        printf("          Полиморфный Вектор           \n");
        printf("          Мусин Иван Б25-507           \n");
        printf("\n");
        printf("ВЕКТОРЫ:\n");
        printf("1. Создать вектор 1 (int)\n");
        printf("2. Создать вектор 1 (double)\n");
        printf("3. Создать вектор 2 (int)\n");
        printf("4. Создать вектор 2 (double)\n");
        printf("\n");
        printf("ПРОСМОТР:\n");
        printf("5. Вывести вектор 1\n");
        printf("6. Вывести вектор 2\n");
        printf("\n");
        printf("ОПЕРАЦИИ:\n");
        printf("7. Сложить векторы (v1 + v2)\n");
        printf("8. Скалярное произведение (v1 * v2)\n");
        printf("\n");
        printf("ТЕСТИРОВАНИЕ:\n");
        printf("9. Запустить модульные тесты\n");
        printf("\n");
        printf("ВЫХОД:\n");
        printf("0. Выход из программы\n");
        printf("\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choice)!=1) {
            printf("ошибка вывода,введите число от 0 до 9\n");
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                if (v1) {
                    vector_destroy(v1);
                }
                current_type = get_int_type_info();
                v1=input_vector(current_type);
                if (v1) {
                    printf("вектор 1 успешно создан\n");
                }
                break;

            case 2:
                if (v2) {
                    vector_destroy(v1);
                }
                current_type = get_double_type_info();
                v1=input_vector(current_type);
                if (v1) {
                    printf("вектор 1 успешно создан\n");
                }
                break;

            case 3:
                if (v2) {
                    vector_destroy(v2);
                }
                current_type = get_int_type_info();
                v2 = input_vector(current_type);
                if (v2) {
                    printf("вектор 2 успешно создан\n");
                }
                break;

            case 4:
                if (v2) {
                    vector_destroy(v2);
                }
                current_type = get_double_type_info();
                v2 = input_vector(current_type);
                if (v2) {
                    printf("вектор 2 успешно создан\n");
                }
                break;

            case 5:
                printf("вектор 1: ");
                print_vector(v1);
                break;

            case 6:
                printf("вектор 2: ");
                print_vector(v2);
                break;

            case 7:
                if (v1 && v2) {
                    Vector* result = vector_add(v1,v2);
                    if (result) {
                        printf("результат сложения: \n");
                        print_vector(result);
                        vector_destroy(result);
                    }else {
                        printf("ошибка: векторы несовместимы, разные типы или разные размеры\n");
                    }
                }else {
                    printf("создайте оба вектора сначала\n");
                }
                break;

            case 8:
                if (v1&&v2) {
                    void* result = current_type->alloc();
                    if (result) {
                        vector_scalar_product(v1,v2,result);
                        printf("скалярное произведение: ");
                        current_type->print(result);
                        printf("\n");
                        current_type->dealloc(result);
                    }else {
                        printf("ошибка выделения памяти для результата\n");
                    }
                }else {
                    printf("создайте сначала оба вектора\n");
                }
                break;

            case 9:
                printf("\n");
                run_all_tests();
                break;

            case 0:
                printf("\n");
                printf("         завершение работы...          \n");

                if (v1) {
                    vector_destroy(v1);
                }
                if (v2) {
                    vector_destroy(v2);
                }

                printf("память освобождена. конец.\n");
                return 0;

            default:
                printf("неверный ввод, введите число от 0 до 9\n");
                break;
        }

        printf("нажмите ENTER для продолжения...");
        clear_input_buffer();
        getchar();
    }
}


















