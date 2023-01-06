#include <iostream>
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
    int nmax = 0;
    int mmax = 0;
    int mmin = 0;
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
    printf("введите количество строк во второй матрице(целое число,большее единицы):\n");
    scanf_s("%d", &nB);
    while (nB <= 1) {
        while (getchar() != '\n') {
            continue;
        }
        printf("введите количество строк во второй матрице(целое число,большее единицы):\n");
        scanf_s("%d", &nB);
    }
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
    if (nA > nB) {
        nmax = nA;
    }
    else {
        nmax = nB;
    }
    if (mA > mB) {
        mmax = mA;
        mmin = mB;
    }
    else {
        mmax = mB;
        mmin = mA;
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
    
    int** result = (int**)malloc(sizeof(int*) * nmax);;
    for (int i = 0; i < nmax; i++) {
        result[i] = (int*)malloc(sizeof(int) * mmax);
    }
    printf("первая матрица:\n");
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < mA; j++) {
            printf("%d ", matr1[i][j]);
        }
        printf("\n");
    }
    printf("вторая матрица:\n");
    for (int i = 0; i < nB; i++) {
        for (int j = 0; j < mB; j++) {
            printf("%d ", matr2[i][j]);
        }
        printf("\n");
    }
   
    
    int i, j, k;
   
    unsigned int start_time = clock();
#pragma omp parallel for shared(matr1, matr2, result) private(i, j, k)  num_threads(threadsNum)
    for (i = 0; i < nmax; i++) {
        
        for (j = 0; j < mmax; j++) {
            result[i][j] = 0;
            for (k = 0; k < mmin; k++) {
                result[i][j] += (matr1[i][k] * matr2[k][j]);
            }
        }
    }
    unsigned int end_time = clock();
    printf("Результат:\n");
    for (i = 0; i < nmax; i++) {

        for (j = 0; j < mmax; j++) {
            printf("%d ", result[i][j]);
            
        }
        printf("\n");
    }
    
    unsigned int search_time = end_time - start_time;
    
    printf("Время - %d", search_time);
    return 0;
}