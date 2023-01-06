#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <locale.h>
#include <ctime>
using namespace std;

void randomMatr(int** matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matr[i][j] = rand() %1000;
        }
    }

    return;
}

int main(int argc, char** argv) {

    srand(time(NULL));
    char* locale = setlocale(LC_ALL, "");
    int nA = 0;
    int mA = 0;
    int nB = 0;
    int mB = 0;
    int threadsNum = 0;
    printf("введите количество строк в первой матрице(целое число,большее единицы):\n");
    scanf_s("%d", &nA);
    while (nA<=1) {
        while (getchar() != '\n') {
            continue;
        }
        printf("введите количество строк в первой матрице(целое число,большее единицы):\n");
        scanf_s("%d", &nA);
    }
    printf("введите количество столбцов в первой матрице(целое число,большее единицы):\n");
    scanf_s("%d", &mA);
    while (mA <= 1) {
        while (getchar() != '\n') {
            continue;
        }
        printf("введите количество столбцов в первой матрице(целое число,большее единицы):\n");
        scanf_s("%d", &mA);
    }
    nB = mA;//Две матрицы можно перемножить между собой тогда и только тогда, когда количество столбцов первой матрицы(матрицы A) равно количеству строк второй матрицы(матрицы B).
    printf("введите количество столбцов во второй матрице(целое число,большее единицы):\n");
    scanf_s("%d", &mB);
    while (mB <= 1) {
        while (getchar() != '\n') {
            continue;
        }
        printf("введите количество столбцов во второй матрице(целое число,большее единицы):\n");
        scanf_s("%d", &mB);
    }
    printf("введите количество параллельных потоков(целое число,большее единицы):\n");
    scanf_s("%d", &threadsNum);
    while (threadsNum <= 1) {
        while (getchar() != '\n') {
            continue;
        }
        printf("введите количество параллельных потоков(целое число,большее единицы):\n");
        scanf_s("%d", &threadsNum);
    }
    
    //Первая матрица из nA строк и mA столбцов(матрица A)
    int** matr1;
    //Вторая матрица из nB строк и mB столбцов(матрица B)
    int** matr2;

    matr1 = (int**)malloc(sizeof(int*) * nA);
    for (int i = 0; i < nA; i++) {
        matr1[i] = (int*)malloc(sizeof(int) * mA);
    }
    matr2 = (int**)malloc(sizeof(int*) * nB);
    for (int i = 0; i < nB; i++) {
        matr2[i] = (int*)malloc(sizeof(int) * mB);
    }

    //Генерируем случайные матрицы для умножения
    randomMatr(matr1, nA, mA);
    randomMatr(matr2, nB, mB);
    
    int** result = (int**)malloc(sizeof(int*) * nA);;
    for (int i = 0; i < nA; i++) {
        result[i] = (int*)malloc(sizeof(int) * mB);
    }
    
   
    
    int i, j, k;
    
    unsigned int start_time = clock();
#pragma omp parallel for shared(matr1, matr2, result) private(i, j, k)  num_threads(threadsNum)
    for (i = 0; i < nA; i++) {
        
        for (j = 0; j < mB; j++) {
            result[i][j] = 0;
            for (k = 0; k < nB; k++) {
                result[i][j] += (matr1[i][k] * matr2[k][j]);
            }
        }
    }
    unsigned int end_time = clock();
    
    unsigned int search_time = end_time - start_time;
    
    printf("Время перемножения - %d миллисекунд  кол-во параллельных потоков - %d", search_time ,threadsNum);
    return 0;
}