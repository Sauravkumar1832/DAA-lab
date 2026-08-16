#include<stdio.h>
#include<stdlib.h>

void addMatrix(long long *A, long long *B, long long *C, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            C[i*n+j]=A[i*n+j]+B[i*n+j];
        }
    }
}

void subtractMatrix(long long *A, long long *B, long long *C, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            C[i*n+j]=A[i*n+j]-B[i*n+j];
        }
    }
}

void specialMultiply(long long *A, long long *B, long long *C, int n)
{
    if(n==1)
    {
        C[0]=A[0]*B[0];
        return;
    }

    int m=n/2;
    int size=m*m;

    long long *A1=malloc(size*sizeof(long long));
    long long *A2=malloc(size*sizeof(long long));
    long long *B1=malloc(size*sizeof(long long));
    long long *B2=malloc(size*sizeof(long long));

    long long *AplusA2=malloc(size*sizeof(long long));
    long long *AminusA2=malloc(size*sizeof(long long));

    long long *BplusB2=malloc(size*sizeof(long long));
    long long *BminusB2=malloc(size*sizeof(long long));

    long long *P=malloc(size*sizeof(long long));
    long long *Q=malloc(size*sizeof(long long));

    long long *C1=malloc(size*sizeof(long long));
    long long *C2=malloc(size*sizeof(long long));

    if(A1==NULL || A2==NULL || B1==NULL || B2==NULL ||
       AplusA2==NULL || AminusA2==NULL ||
       BplusB2==NULL || BminusB2==NULL ||
       P==NULL || Q==NULL || C1==NULL || C2==NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            A1[i*m+j]=A[i*n+j];
            A2[i*m+j]=A[i*n+j+m];

            B1[i*m+j]=B[i*n+j];
            B2[i*m+j]=B[i*n+j+m];
        }
    }

    addMatrix(A1,A2,AplusA2,m);
    subtractMatrix(A1,A2,AminusA2,m);

    addMatrix(B1,B2,BplusB2,m);
    subtractMatrix(B1,B2,BminusB2,m);

    specialMultiply(AplusA2,BplusB2,P,m);

    specialMultiply(AminusA2,BminusB2,Q,m);

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            C1[i*m+j]=(P[i*m+j]+Q[i*m+j])/2;
            C2[i*m+j]=(P[i*m+j]-Q[i*m+j])/2;
        }
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            C[i*n+j]=C1[i*m+j];
            C[i*n+j+m]=C2[i*m+j];

            C[(i+m)*n+j]=C2[i*m+j];
            C[(i+m)*n+j+m]=C1[i*m+j];
        }
    }

    free(A1);
    free(A2);
    free(B1);
    free(B2);

    free(AplusA2);
    free(AminusA2);

    free(BplusB2);
    free(BminusB2);

    free(P);
    free(Q);

    free(C1);
    free(C2);
}

int isPowerOfTwo(int n)
{
    if(n<=0)
        return 0;

    while(n%2==0)
    {
        n=n/2;
    }

    return n==1;
}

void printMatrix(long long *A, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%lld ",A[i*n+j]);
        }

        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter the size of the matrix: ");
    scanf("%d",&n);

    if(!isPowerOfTwo(n))
    {
        printf("Matrix size must be a power of 2.\n");
        printf("Valid sizes are 1, 2, 4, 8, 16, ...\n");
        return 1;
    }

    long long *A=malloc(n*n*sizeof(long long));
    long long *B=malloc(n*n*sizeof(long long));
    long long *C=malloc(n*n*sizeof(long long));

    if(A==NULL || B==NULL || C==NULL)
    {
        printf("Memory allocation failed.\n");

        free(A);
        free(B);
        free(C);

        return 1;
    }

    printf("\nEnter the first special-pattern matrix:\n");

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%lld",&A[i*n+j]);
        }
    }

    printf("\nEnter the second special-pattern matrix:\n");

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%lld",&B[i*n+j]);
        }
    }

    specialMultiply(A,B,C,n);

    printf("\nFirst Matrix:\n");
    printMatrix(A,n);

    printf("\nSecond Matrix:\n");
    printMatrix(B,n);

    printf("\nResultant Matrix:\n");
    printMatrix(C,n);

    printf("\nMatrix multiplication completed using the special-pattern D&C approach.\n");
    printf("Time Complexity: O(n^2)\n");

    free(A);
    free(B);
    free(C);

    return 0;
}