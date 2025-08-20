#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 50
#define MIN_SIZE 399
#define MAX_SIZE 400
#define MAX_NUM 10000000.0

int main() {
    srand((unsigned) time(NULL));

    int size = MAX_SIZE, iterator = 0; // MIN_SIZE + (rand() % MAX_SIZE)
    double time_spent = 0.0;
    double A[size][size] __attribute__((aligned(64))), B[size][size] __attribute__((aligned(64))), C[size][size] __attribute__((aligned(64)));


    while (iterator++ < N) {
        printf("Running iteration number: %d\n", iterator);

        clock_t begin_time = clock();

        // Start modifying here

        // Usamos punteros para acceder secuencialmente y más facil a la memoria
        double *pA = &A[0][0];
        double *pB = &B[0][0];
        double *pC = &C[0][0];

        // Inicialización -> llenamos de valores aleatorios las matrices A y B (usando punteros)
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                unsigned int seed = time(NULL) + omp_get_thread_num();
                *(pA + i * size + j) = 1 + ((double)rand_r(&seed) / RAND_MAX) * MAX_NUM; // Cambiamos la forma en que se accedde
                *(pB + j * size + i) = 1 + ((double)rand_r(&seed) / RAND_MAX) * MAX_NUM; // al random para optimizar la  paralelización
                *(pC + i * size + j) = 0;
            }
        }


        // Multiplicamos teniendo en cuenta el acceso de punteros
        #pragma omp parallel for
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                for (int i = 0; i < size; i++) {
                    *(pC + i * size + j) +=
                        *(pA + i * size + k) * *(pB + j * size + k);
                }
            }
        }

        // Stop modifying here

        clock_t end_time = clock();
        time_spent += (double)(end_time - begin_time) / CLOCKS_PER_SEC;
    }

    printf("Size of matrices: %d\n", size);
    printf("Running time: %f\n", (time_spent / N));

    return 0;
}
