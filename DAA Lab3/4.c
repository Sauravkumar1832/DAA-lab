#include<stdio.h>
#include<stdlib.h>

void addMatrix(int n, int A[][n], int B[][n], int C[][n])
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            C[i][j]=A[i][j]+B[i][j];
        }
    }
}

void subtractMatrix(int n, int A[][n], int B[][n], int C[][n])
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            C[i][j]=A[i][j]-B[i][j];
        }
    }
}

void strassen(int n, int A[][n], int B[][n], int C[][n])
{
    if(n==1)
    {
        C[0][0]=A[0][0]*B[0][0];
        return;
    }

    int newSize=n/2;

    int (*A11)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*A12)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*A21)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*A22)[newSize]=malloc(sizeof(int[newSize][newSize]));

    int (*B11)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*B12)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*B21)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*B22)[newSize]=malloc(sizeof(int[newSize][newSize]));

    int (*M1)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*M2)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*M3)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*M4)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*M5)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*M6)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*M7)[newSize]=malloc(sizeof(int[newSize][newSize]));

    int (*T1)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*T2)[newSize]=malloc(sizeof(int[newSize][newSize]));

    int (*C11)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*C12)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*C21)[newSize]=malloc(sizeof(int[newSize][newSize]));
    int (*C22)[newSize]=malloc(sizeof(int[newSize][newSize]));

    for(int i=0; i<newSize; i++)
    {
        for(int j=0; j<newSize; j++)
        {
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][j+newSize];
            A21[i][j]=A[i+newSize][j];
            A22[i][j]=A[i+newSize][j+newSize];

            B11[i][j]=B[i][j];
            B12[i][j]=B[i][j+newSize];
            B21[i][j]=B[i+newSize][j];
            B22[i][j]=B[i+newSize][j+newSize];
        }
    }

    addMatrix(newSize,A11,A22,T1);
    addMatrix(newSize,B11,B22,T2);
    strassen(newSize,T1,T2,M1);

    addMatrix(newSize,A21,A22,T1);
    strassen(newSize,T1,B11,M2);

    subtractMatrix(newSize,B12,B22,T2);
    strassen(newSize,A11,T2,M3);

    subtractMatrix(newSize,B21,B11,T2);
    strassen(newSize,A22,T2,M4);

    addMatrix(newSize,A11,A12,T1);
    strassen(newSize,T1,B22,M5);

    subtractMatrix(newSize,A21,A11,T1);
    addMatrix(newSize,B11,B12,T2);
    strassen(newSize,T1,T2,M6);

    subtractMatrix(newSize,A12,A22,T1);
    addMatrix(newSize,B21,B22,T2);
    strassen(newSize,T1,T2,M7);

    addMatrix(newSize,M1,M4,T1);
    subtractMatrix(newSize,T1,M5,T2);
    addMatrix(newSize,T2,M7,C11);

    addMatrix(newSize,M3,M5,C12);

    addMatrix(newSize,M2,M4,C21);

    addMatrix(newSize,M1,M3,T1);
    subtractMatrix(newSize,T1,M2,T2);
    addMatrix(newSize,T2,M6,C22);

    for(int i=0; i<newSize; i++)
    {
        for(int j=0; j<newSize; j++)
        {
            C[i][j]=C11[i][j];
            C[i][j+newSize]=C12[i][j];
            C[i+newSize][j]=C21[i][j];
            C[i+newSize][j+newSize]=C22[i][j];
        }
    }

    free(A11);
    free(A12);
    free(A21);
    free(A22);

    free(B11);
    free(B12);
    free(B21);
    free(B22);

    free(M1);
    free(M2);
    free(M3);
    free(M4);
    free(M5);
    free(M6);
    free(M7);

    free(T1);
    free(T2);

    free(C11);
    free(C12);
    free(C21);
    free(C22);
}

int nextPowerOfTwo(int n)
{
    int power=1;

    while(power<n)
    {
        power=power*2;
    }

    return power;
}

int main()
{
    int n;

    printf("Enter the size of the matrix: ");
    scanf("%d",&n);

    if(n<=0)
    {
        printf("Invalid matrix size.\n");
        return 1;
    }

    int size=nextPowerOfTwo(n);

    int (*A)[size]=calloc(size,sizeof(int[size]));
    int (*B)[size]=calloc(size,sizeof(int[size]));
    int (*C)[size]=calloc(size,sizeof(int[size]));

    if(A==NULL || B==NULL || C==NULL)
    {
        printf("Memory allocation failed.\n");

        free(A);
        free(B);
        free(C);

        return 1;
    }

    printf("\nEnter elements of first matrix:\n");

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%d",&A[i][j]);
        }
    }

    printf("\nEnter elements of second matrix:\n");

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%d",&B[i][j]);
        }
    }

    strassen(size,A,B,C);

    printf("\nResultant Matrix:\n");

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%d ",C[i][j]);
        }

        printf("\n");
    }

    printf("\nMatrix multiplication completed using Strassen's method.\n");

    printf("Time Complexity: O(n^log2(7)) approximately O(n^2.807).\n");

    free(A);
    free(B);
    free(C);

    return 0;
}