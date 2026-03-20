#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "int_type.h"
#include "double_type.h"

static int tests_passed = 0;
static int tests_failed = 0;

//тест 1: создание вектора
void test_vector_create_int() {
    printf("тест1: создание вектора int: ");

    const TypeInfo* info = get_int_type_info();

    Vector* vec = vector_create(info, 5);
    assert(vec!=NULL);
    assert(vector_size(vec)==0);
    assert(vector_get_type_info(vec)==info);
    vector_destroy(vec);

    printf("PASSED\n");
    tests_passed++;
}

//тест 2: добавление и получение элементов
void test_vector_push_and_get() {
    printf("тест2: добавление и получение элементов: ");

    const TypeInfo* info = get_int_type_info();
    Vector* vec = vector_create(info, 2);

    int val1=10,val2=20;

    vector_push(vec,&val1);
    vector_push(vec,&val2);

    assert(vector_size(vec)==2);

    assert(*(int*)vector_get(vec,0)==10);
    assert(*(int*)vector_get(vec,1)==20);

    vector_destroy(vec);

    printf("PASSED\n");
    tests_passed++;
}

//тест 3: векторное сложение
void test_vector_addition() {
    printf("тест3: векторное сложение: ");

    const TypeInfo* info = get_int_type_info();
    Vector* v1 = vector_create(info, 3);
    Vector* v2 = vector_create(info,3);

    int a1=1, a2=2, a3=3;
    vector_push(v1, &a1);
    vector_push(v1, &a2);
    vector_push(v1, &a3);

    int b1=4, b2=5, b3=6;
    vector_push(v2, &b1);
    vector_push(v2, &b2);
    vector_push(v2, &b3);

    Vector* result = vector_add(v1,v2);

    assert(result!=NULL);

    assert(vector_size(result)==3);

    assert(*(int*)vector_get(result,0)==5);//1+4=5
    assert(*(int*)vector_get(result,1)==7);//2+5=7
    assert(*(int*)vector_get(result,2)==9);//3+6=9

    vector_destroy(v1);
    vector_destroy(v2);
    vector_destroy(result);

    printf("PASSED\n");
    tests_passed++;
}

//тест 4: скалярное произведение
void test_scalar_product_int() {
    printf("тест4: скалярное произведение: ");

    const TypeInfo* info = get_int_type_info();
    Vector* v1 = vector_create(info, 2);
    Vector* v2 = vector_create(info,2);

    int a1=1, a2=2;
    int b1=3, b2=4;
    vector_push(v1, &a1);
    vector_push(v1, &a2);
    vector_push(v2, &b1);
    vector_push(v2, &b2);

    int result=0;

    vector_scalar_product(v1,v2,&result);

    assert(result==11);//1*3+2*4=11

    vector_destroy(v1);
    vector_destroy(v2);

    printf("PASSED\n");
    tests_passed++;
}

//тест 5: несовпадение типов векторов
void test_type_mismatch() {
    printf("тест5: несовпадение типов векторов: ");

    const TypeInfo* int_info = get_int_type_info();
    const TypeInfo* double_info = get_double_type_info();

    Vector* v1=vector_create(int_info,2);
    Vector* v2=vector_create(double_info,2);

    Vector* result = vector_add(v1,v2);

    assert(result==NULL);

    vector_destroy(v1);
    vector_destroy(v2);

    printf("PASSED\n");
    tests_passed++;
}

//тест 6: несовпадение размеров векторов
void test_size_mismatch() {
    printf("тест6: несовпадение размеров векторов: ");

    const TypeInfo* info = get_int_type_info();

    Vector* v1=vector_create(info,2);
    Vector* v2=vector_create(info,3);

    int val1 = 1, val2 = 2;

    vector_push(v1, &val1);

    vector_push(v2, &val1);
    vector_push(v2, &val2);

    Vector* result = vector_add(v1, v2);

    assert(result == NULL);

    vector_destroy(v1);
    vector_destroy(v2);

    printf("PASSED\n");
    tests_passed++;
}

//тест 7: скалярное произведение для double
void test_scalar_product_double() {
    printf("тест7: скалярное произведение double: ");

    const TypeInfo* info =  get_double_type_info();
    Vector* v1 = vector_create(info,2);
    Vector* v2 = vector_create(info,2);

    double a1=1.5, a2=2.5;
    double b1=2.0, b2=4.0;
    vector_push(v1, &a1);
    vector_push(v1, &a2);
    vector_push(v2, &b1);
    vector_push(v2, &b2);
    double result=0.0;

    vector_scalar_product(v1,v2,&result);
    double expected  = 13.0;
    double diff = result - expected;
    if (diff < 0) diff = -diff;
    assert(diff<0.001);

    vector_destroy(v1);
    vector_destroy(v2);

    printf("PASSED\n");
    tests_passed++;
}

//тест 8: пустой вектор
void test_empty_vector() {
    printf("тест8: пустой вектор: ");

    const TypeInfo* info = get_int_type_info();
    Vector* v1 = vector_create(info,0);
    Vector* v2 = vector_create(info,0);
    int result=0;

    vector_scalar_product(v1,v2,&result);

    assert(result==0);

    vector_destroy(v1);
    vector_destroy(v2);

    printf("PASSED\n");
    tests_passed++;
}

//функция запуска всех тестов
void run_all_tests() {
    printf("запуск модульных тестов ...\n");

    test_vector_create_int();
    test_vector_push_and_get();
    test_vector_addition();
    test_scalar_product_int();
    test_type_mismatch();
    test_size_mismatch();
    test_scalar_product_double();
    test_empty_vector();

    printf("итоги тестов\n");
    printf("Пройдено: %d\n", tests_passed);
    printf("Провалено: %d\n", tests_failed);
    printf("\n");

    if (tests_failed==0) {
        printf("все тесты прошли успешно\n");
    } else {
        printf("есть тесты провалены\n");
    }
    printf("\n");
}




































