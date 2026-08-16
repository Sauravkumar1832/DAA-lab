#include<stdio.h>
#include<stdlib.h>

struct Result
{
    int min;
    int max;
};


/*
   Divide and Conquer function to find
   minimum and maximum
*/

struct Result findMinMax(int arr[], int low, int high, int *comparison)
{
    struct Result result;
    struct Result left;
    struct Result right;

    /*
       Only one element
    */

    if(low == high)
    {
        result.min = arr[low];
        result.max = arr[low];

        return result;
    }


    /*
       Two elements
    */

    if(high == low + 1)
    {
        (*comparison)++;

        if(arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }


    /*
       More than two elements:
       divide the array into two halves
    */

    int mid = low + (high - low) / 2;

    left = findMinMax(arr, low, mid, comparison);

    right = findMinMax(arr, mid + 1, high, comparison);


    /*
       Compare the two maximum values
    */

    (*comparison)++;

    if(left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;


    /*
       Compare the two minimum values
    */

    (*comparison)++;

    if(left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;


    return result;
}


int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d",&n);


    if(n <= 0)
    {
        printf("Invalid input.\n");
        return 1;
    }


    int arr[n];


    printf("Enter the elements:\n");

    for(int i=0; i<n; i++)
    {
        scanf("%d",&arr[i]);
    }


    int comparison = 0;


    struct Result result;

    result = findMinMax(arr,0,n-1,&comparison);


    printf("\nMinimum element: %d\n",result.min);

    printf("Maximum element: %d\n",result.max);

    printf("Number of comparisons: %d\n",comparison);


    /*
       Theoretical upper bound
    */

    double bound = (3.0 * n) / 2.0;

    printf("3n/2 bound: %.1f\n",bound);


    if(comparison <= bound)
    {
        printf("Comparison count is within the 3n/2 bound.\n");
    }
    else
    {
        printf("Comparison count exceeds the 3n/2 bound.\n");
    }


    /*
       Create data file for Gnuplot
    */

    FILE *data = fopen("minmax_data.txt","w");


    if(data == NULL)
    {
        printf("Error creating minmax_data.txt\n");
        return 1;
    }


    /*
       Generate comparison data for
       different input sizes
    */

    for(int size=1; size<=1000; size++)
    {
        int *testArr;

        testArr = (int *)malloc(size * sizeof(int));


        if(testArr == NULL)
        {
            printf("Memory allocation failed.\n");

            fclose(data);

            return 1;
        }


        /*
           Generate test data
        */

        for(int i=0; i<size; i++)
        {
            testArr[i] = i;
        }


        int testComparison = 0;


        findMinMax(testArr,0,size-1,&testComparison);


        /*
           Theoretical upper bound
           = 3n/2
        */

        double theoreticalBound = (3.0 * size) / 2.0;


        fprintf(data,"%d %d %.1f\n",
                size,
                testComparison,
                theoreticalBound);


        free(testArr);
    }


    fclose(data);


    /*
       Create Gnuplot script
    */

    FILE *gnuplot = fopen("minmax_graph.gnu","w");


    if(gnuplot == NULL)
    {
        printf("Error creating minmax_graph.gnu\n");
        return 1;
    }


    fprintf(gnuplot,
        "set title 'Divide and Conquer: Maximum and Minimum'\n"
        "set xlabel 'Number of Elements (n)'\n"
        "set ylabel 'Number of Comparisons'\n"
        "set grid\n"
        "set key left top\n"
        "plot 'minmax_data.txt' using 1:2 with linespoints title 'Actual Comparisons', "
        "'minmax_data.txt' using 1:3 with lines title '3n/2 Bound'\n"
        "pause -1\n"
    );


    fclose(gnuplot);


    printf("\nGraph files created successfully.\n");
    printf("Opening Gnuplot...\n");


    /*
       Open Gnuplot
    */

    system("gnuplot minmax_graph.gnu");


    return 0;
}