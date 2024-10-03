#include <stdio.h>
#include <stdlib.h>

#define ALIGN 64

float** matrix_1 = NULL;
float** matrix_2 = NULL;
float** matrix_res = NULL;

int alloc_matrix(unsigned int matrix_size)
{
    matrix_1 = (float**)aligned_alloc(ALIGN, matrix_size*sizeof(float*));
    matrix_2 = (float**)aligned_alloc(ALIGN, matrix_size*sizeof(float*));
    matrix_res = (float**)aligned_alloc(ALIGN, matrix_size*sizeof(float*));

    if (matrix_1 == NULL || matrix_2 == NULL || matrix_res == NULL)
        return 1;

    for (int i = 0; i < matrix_size; i++)
    {
        matrix_1[i] = (float*)aligned_alloc(ALIGN, matrix_size*sizeof(float));
        matrix_2[i] = (float*)aligned_alloc(ALIGN, matrix_size*sizeof(float));
        matrix_res[i] = (float*)aligned_alloc(ALIGN, matrix_size*sizeof(float));
        if (matrix_1[i] == NULL || matrix_2[i] == NULL || matrix_res[i] == NULL)
            return 1;
    }

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            matrix_1[i][j] = i*0.34 + 1;
            matrix_2[i][j] = j*0.28 + 1;
        }
    }

    return 0;
}

int mult_matrix(unsigned int matrix_size)
{
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            for (int k = 0; k < matrix_size; k++)
            {
                matrix_res[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }

    return 0;
}

int free_matrix(unsigned int matrix_size)
{
    for (int i = 0; i < matrix_size; i++)
    {
        free(matrix_res[i]);
        free(matrix_1[i]);
        free(matrix_2[i]);
    }
    free(matrix_res);
    free(matrix_1);
    free(matrix_2);

    return 0;
}

int main(int argc, char** argv)
{
    unsigned int matrix_size = 32;

    if (argc == 2)
    {
        if (atoi(argv[1]) < 1)
        {
            printf("error: matrix_size < 1\n");
            return -1;
        }
        matrix_size = atoi(argv[1]);
    }

    printf("matrix_size: %d\n", matrix_size);
    
    if (matrix_size < 32)
    {
        printf("error: matrix_size too small\n");
        return -1; 
    }
    
    if (alloc_matrix(matrix_size))
    {
        printf("error: allocation issue\n");
    }

    mult_matrix(matrix_size);

    free_matrix(matrix_size);
    return 0;
}
