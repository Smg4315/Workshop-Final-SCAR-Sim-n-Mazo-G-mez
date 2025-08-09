#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50
#define MIN_SIZE 399
#define MAX_SIZE 400
#define MAX_NUM 10000000.0

int main(){
    srand((unsigned) time(NULL));
    int size = MAX_SIZE, iterator= 0; // MIN_SIZE + (rand() % MAX_SIZE), iterator = 0;
    double time_spent = 0.0;
    double A[size][size] , B[size][size] , C[size][size];

    while(iterator++ < N){
        printf("Running iteration number: %d\n", iterator);

        clock_t begin_time = clock();
        
        // Start modifying here

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                A[j][i] = 1 + ((double)rand() / RAND_MAX) * MAX_NUM; 
                B[j][i] = 1 + ((double)rand() / RAND_MAX) * MAX_NUM; 
                C[j][i] = 0;
            }
        }
        
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){
                for(int i = 0; i < size; i++){
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        // Stop modifying here
        
        clock_t end_time = clock();
        time_spent += (double)(end_time - begin_time) / CLOCKS_PER_SEC;
    }

    printf("Size of matrices: %d \n", size);
    printf("Running time: %f \n", (time_spent / N));

    return 0;
}