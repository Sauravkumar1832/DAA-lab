#include <stdio.h>
#include <stdlib.h>

void convolution(int A[], int m, int B[], int n, int C[])
{
    int mid, i;
    int size1, size2;
    int *C1, *C2;

    /* Base case */
    if (n == 1)
    {
        for (i = 0; i < m; i++)
            C[i] = A[i] * B[0];

        return;
    }

    /* Divide B into two parts */
    mid = n / 2;

    size1 = m + mid - 1;
    size2 = m + (n - mid) - 1;

    C1 = (int *)calloc(size1, sizeof(int));
    C2 = (int *)calloc(size2, sizeof(int));

    /* Convolve A with left half */
    convolution(A, m, B, mid, C1);

    /* Convolve A with right half */
    convolution(A, m, B + mid, n - mid, C2);

    /* Initialize C */
    for (i = 0; i < m + n - 1; i++)
        C[i] = 0;

    /* Add first result */
    for (i = 0; i < size1; i++)
        C[i] += C1[i];

    /* Add second result with shift */
    for (i = 0; i < size2; i++)
        C[i + mid] += C2[i];

    free(C1);
    free(C2);
}

int main()
{
    int A[100], B[100], C[200];
    int m, n, i;

    printf("Enter size of A: ");
    scanf("%d", &m);

    printf("Enter elements of A:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &A[i]);

    printf("Enter size of B: ");
    scanf("%d", &n);

    printf("Enter elements of B:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &B[i]);

    if (m < n)
    {
        printf("Please enter m >= n.\n");
        return 0;
    }

    convolution(A, m, B, n, C);

    printf("Convolution:\n");

    for (i = 0; i < m + n - 1; i++)
        printf("%d ", C[i]);

    printf("\n");

    return 0;
}