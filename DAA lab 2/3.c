#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge two sorted arrays
void merge(int a[], int n1, int b[], int n2, int result[])
{
    int i = 0, j = 0, k = 0;

    while(i < n1 && j < n2)
    {
        if(a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while(i < n1)
        result[k++] = a[i++];

    while(j < n2)
        result[k++] = b[j++];
}

// Method 1: Merge arrays one by one
void method1(int **arrays, int k, int n, int result[])
{
    int currentSize = n;

    // Copy first array
    for(int i = 0; i < n; i++)
        result[i] = arrays[0][i];

    for(int i = 1; i < k; i++)
    {
        int newSize = currentSize + n;

        int *temp = (int *)malloc(newSize * sizeof(int));

        merge(result, currentSize,
              arrays[i], n,
              temp);

        for(int j = 0; j < newSize; j++)
            result[j] = temp[j];

        free(temp);

        currentSize = newSize;
    }
}

// Method 2: Merge arrays in pairs
void method2(int **arrays, int k, int n, int result[])
{
    int currentK = k;
    int currentSize = n;

    int **current = arrays;

    while(currentK > 1)
    {
        int newK = (currentK + 1) / 2;

        int **next = (int **)malloc(newK * sizeof(int *));

        int index = 0;

        for(int i = 0; i < currentK; i += 2)
        {
            // If there is no pair
            if(i + 1 >= currentK)
            {
                next[index] = current[i];
            }
            else
            {
                next[index] =
                    (int *)malloc(2 * currentSize * sizeof(int));

                merge(current[i], currentSize,
                      current[i + 1], currentSize,
                      next[index]);
            }

            index++;
        }

        /*
           Free only the pointer array created
           in the previous level.
        */
        if(current != arrays)
            free(current);

        current = next;

        currentK = newK;
        currentSize = currentSize * 2;
    }

    // Copy final merged array
    for(int i = 0; i < k * n; i++)
        result[i] = current[0][i];

    free(current[0]);

    free(current);
}

int main()
{
    int n, k;

    printf("Enter number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter number of elements in each array (n): ");
    scanf("%d", &n);

    // Allocate k arrays
    int **arrays = (int **)malloc(k * sizeof(int *));

    // Create sorted arrays
    for(int i = 0; i < k; i++)
    {
        arrays[i] = (int *)malloc(n * sizeof(int));

        for(int j = 0; j < n; j++)
        {
            arrays[i][j] = i * n + j;
        }
    }

    int total = k * n;

    int *result1 =
        (int *)malloc(total * sizeof(int));

    int *result2 =
        (int *)malloc(total * sizeof(int));

    // ---------------- Method 1 ----------------

    clock_t start = clock();

    method1(arrays, k, n, result1);

    clock_t end = clock();

    double time1 =
        (double)(end - start) / CLOCKS_PER_SEC;


    // ---------------- Method 2 ----------------

    start = clock();

    method2(arrays, k, n, result2);

    end = clock();

    double time2 =
        (double)(end - start) / CLOCKS_PER_SEC;


    // ---------------- Output ----------------

    printf("\nMethod 1 Time = %lf seconds\n", time1);

    printf("Method 2 Time = %lf seconds\n", time2);


    printf("\nMerged array using Method 1:\n");

    for(int i = 0; i < total; i++)
        printf("%d ", result1[i]);


    printf("\n\nMerged array using Method 2:\n");

    for(int i = 0; i < total; i++)
        printf("%d ", result2[i]);

    printf("\n");


    // Free memory
    for(int i = 0; i < k; i++)
        free(arrays[i]);

    free(arrays);
    free(result1);
    free(result2);

    return 0;
}