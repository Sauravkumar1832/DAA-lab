#include <stdio.h>
#include <math.h>

void addMatrix(int A[10][10], int B[10][10], int C[10][10], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}

void multiplyMatrix(int A[10][10], int B[10][10], int C[10][10], int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int isZeroMatrix(int A[10][10], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (A[i][j] != 0)
                return 0;
        }
    }

    return 1;
}

int isSymmetric(int A[10][10], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (A[i][j] != A[j][i])
                return 0;
        }
    }

    return 1;
}

double determinant(int A[10][10], int n)
{
    double temp[10][10];
    double det = 1;
    double factor;
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            temp[i][j] = A[i][j];
    }

    for (i = 0; i < n; i++)
    {
        if (temp[i][i] == 0)
            return 0;

        for (j = i + 1; j < n; j++)
        {
            factor = temp[j][i] / temp[i][i];

            for (k = i; k < n; k++)
                temp[j][k] -= factor * temp[i][k];
        }

        det *= temp[i][i];
    }

    return det;
}

void transpose(int A[10][10], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/* Dominant eigenvalue and eigenvector */
void eigen(int A[10][10], int n)
{
    double x[10];
    double y[10];
    double lambda;
    double max;
    int i, j, k;

    for (i = 0; i < n; i++)
        x[i] = 1;

    for (k = 0; k < 100; k++)
    {
        for (i = 0; i < n; i++)
        {
            y[i] = 0;

            for (j = 0; j < n; j++)
                y[i] += A[i][j] * x[j];
        }

        max = fabs(y[0]);

        for (i = 1; i < n; i++)
        {
            if (fabs(y[i]) > max)
                max = fabs(y[i]);
        }

        for (i = 0; i < n; i++)
            x[i] = y[i] / max;

        lambda = max;
    }

    printf("Dominant Eigenvalue = %.4f\n", lambda);

    printf("Eigenvector:\n");

    for (i = 0; i < n; i++)
        printf("%.4f ", x[i]);

    printf("\n");
}

void display(int A[10][10], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d ", A[i][j]);

        printf("\n");
    }
}

int main()
{
    int A[10][10], B[10][10], C[10][10];
    int n, i, j;
    int choice;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter matrix A:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    }

    printf("\n1. Addition");
    printf("\n2. Multiplication");
    printf("\n3. Zero Matrix");
    printf("\n4. Symmetric Matrix");
    printf("\n5. Determinant");
    printf("\n6. Transpose");
    printf("\n7. Eigenvalue and Eigenvector");

    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Enter matrix B:\n");

            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++)
                    scanf("%d", &B[i][j]);

            addMatrix(A, B, C, n);

            printf("Result:\n");
            display(C, n);
            break;

        case 2:
            printf("Enter matrix B:\n");

            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++)
                    scanf("%d", &B[i][j]);

            multiplyMatrix(A, B, C, n);

            printf("Result:\n");
            display(C, n);
            break;

        case 3:
            if (isZeroMatrix(A, n))
                printf("It is a zero matrix.\n");
            else
                printf("It is not a zero matrix.\n");
            break;

        case 4:
            if (isSymmetric(A, n))
                printf("Matrix is symmetric.\n");
            else
                printf("Matrix is not symmetric.\n");
            break;

        case 5:
            printf("Determinant = %.2f\n",
                   determinant(A, n));
            break;

        case 6:
            transpose(A, n);

            printf("Transpose:\n");
            display(A, n);
            break;

        case 7:
            eigen(A, n);
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}