#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i, j, temp;
    int duplicate = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    srand(time(NULL));

    // Generate n random numbers
    printf("Random numbers:\n");

    for(i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;

        printf("%d ", arr[i]);
    }

    // Sort the array using Bubble Sort
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Check adjacent elements for duplicates
    for(i = 0; i < n - 1; i++)
    {
        if(arr[i] == arr[i + 1])
        {
            duplicate = 1;
            break;
        }
    }

    if(duplicate == 1)
        printf("\nDuplicate element exists.\n");
    else
        printf("\nAll elements are unique.\n");

    return 0;
}