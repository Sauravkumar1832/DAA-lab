#include <stdio.h>
#include <stdlib.h>

long long bubbleSortNormal(int a[], int n)
{
    int i, j, temp;
    long long comparisons = 0;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

long long bubbleSortOptimized(int a[], int n)
{
    int i, j, temp;
    int swapped;
    long long comparisons = 0;

    for (i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for (j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }

    return comparisons;
}

void generateSortedArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
}

int main()
{
    int sizes[] = {100, 500, 1000, 2000, 5000, 10000};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    FILE *data = fopen("bubble.dat", "w");

    if (data == NULL)
    {
        printf("Error creating bubble.dat\n");
        return 1;
    }

    fprintf(data, "# n Normal Optimized\n");

    printf("\n");
    printf("NORMAL BUBBLE SORT vs OPTIMIZED BUBBLE SORT\n");
    printf("Input: Sorted Array\n\n");

    printf("%-10s %-20s %-20s\n",
           "n",
           "Normal",
           "Optimized");

    printf("------------------------------------------------\n");

    for (int s = 0; s < count; s++)
    {
        int n = sizes[s];

        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        if (arr1 == NULL || arr2 == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(data);
            return 1;
        }

        generateSortedArray(arr1, n);

        for (int i = 0; i < n; i++)
        {
            arr2[i] = arr1[i];
        }

        long long normal =
            bubbleSortNormal(arr1, n);

        long long optimized =
            bubbleSortOptimized(arr2, n);

        printf("%-10d %-20lld %-20lld\n",
               n,
               normal,
               optimized);

        fprintf(data,
                "%d %lld %lld\n",
                n,
                normal,
                optimized);

        free(arr1);
        free(arr2);
    }

    fclose(data);

    FILE *gp = fopen("bubble.gnu", "w");

    if (gp == NULL)
    {
        printf("Error creating bubble.gnu\n");
        return 1;
    }

    fprintf(gp,
        "set terminal wxt size 900,600\n"
        "set title 'Normal Bubble Sort vs Optimized Bubble Sort'\n"
        "set xlabel 'Number of Elements (n)'\n"
        "set ylabel 'Number of Comparisons'\n"
        "set grid\n"
        "set key left top\n"
        "plot "
        "'bubble.dat' using 1:2 with linespoints lw 2 pt 7 "
        "title 'Normal Bubble Sort', "
        "'bubble.dat' using 1:3 with linespoints lw 2 pt 5 "
        "title 'Optimized Bubble Sort'\n"
        "pause -1\n"
    );

    fclose(gp);

    printf("\nData saved to bubble.dat\n");
    printf("Opening Gnuplot...\n");

    system("gnuplot bubble.gnu");

    return 0;
}
