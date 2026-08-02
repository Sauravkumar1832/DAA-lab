#include <stdio.h>

int findPartition(int arr[], int n)
{
    int low = 0;
    int high = n - 1;

    while(low <= high)
    {
        int mid = (low + high) / 2;

        // Check if mid is the first 1
        if(arr[mid] == 1 && (mid == 0 || arr[mid - 1] == 0))
        {
            return mid;
        }

        if(arr[mid] == 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int main()
{
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements (0s followed by 1s):\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int partition = findPartition(arr, n);

    if(partition == -1)
    {
        printf("No partition point found.\n");
    }
    else
    {
        printf("Partition point is at index %d\n", partition);
    }

    return 0;
}