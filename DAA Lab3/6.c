#include<stdio.h>
#include<stdlib.h>

void selectionSort(int arr[], int n, int *comparison)
{
    int i, j, minIndex, temp;

    for(i=0; i<n-1; i++)
    {
        minIndex=i;

        for(j=i+1; j<n; j++)
        {
            (*comparison)++;

            if(arr[j]<arr[minIndex])
            {
                minIndex=j;
            }
        }

        temp=arr[i];
        arr[i]=arr[minIndex];
        arr[minIndex]=temp;
    }
}

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    if(n<=0)
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

    int comparison=0;

    selectionSort(arr,n,&comparison);

    printf("\nSorted array:\n");

    for(int i=0; i<n; i++)
    {
        printf("%d ",arr[i]);
    }

    printf("\n");

    printf("Number of comparisons: %d\n",comparison);

    printf("\nBest-case time complexity: O(n^2)\n");
    printf("Worst-case time complexity: O(n^2)\n");


    /*
       Create data file for Gnuplot
    */

    FILE *data=fopen("selection_data.txt","w");

    if(data==NULL)
    {
        printf("Error creating selection_data.txt\n");
        return 1;
    }


    /*
       Generate data for best and worst cases
    */

    for(int size=10; size<=1000; size+=10)
    {
        int *bestArr=(int *)malloc(size*sizeof(int));
        int *worstArr=(int *)malloc(size*sizeof(int));

        if(bestArr==NULL || worstArr==NULL)
        {
            printf("Memory allocation failed\n");

            free(bestArr);
            free(worstArr);

            fclose(data);

            return 1;
        }


        /*
           Best-case input:
           Already sorted array
        */

        for(int i=0; i<size; i++)
        {
            bestArr[i]=i;
        }


        /*
           Worst-case input:
           Reverse sorted array
        */

        for(int i=0; i<size; i++)
        {
            worstArr[i]=size-i;
        }


        int bestComparison=0;
        int worstComparison=0;


        selectionSort(bestArr,size,&bestComparison);

        selectionSort(worstArr,size,&worstComparison);


        fprintf(data,"%d %d %d\n",
                size,
                bestComparison,
                worstComparison);


        free(bestArr);
        free(worstArr);
    }

    fclose(data);


    /*
       Create Gnuplot script
    */

    FILE *gnuplot=fopen("selection_graph.gnu","w");

    if(gnuplot==NULL)
    {
        printf("Error creating selection_graph.gnu\n");
        return 1;
    }

    fprintf(gnuplot,
        "set title 'Selection Sort: Best Case vs Worst Case'\n"
        "set xlabel 'Number of Elements (n)'\n"
        "set ylabel 'Number of Comparisons'\n"
        "set grid\n"
        "set key left top\n"
        "plot 'selection_data.txt' using 1:2 with linespoints title 'Best Case', "
        "'selection_data.txt' using 1:3 with linespoints title 'Worst Case'\n"
        "pause -1\n"
    );

    fclose(gnuplot);


    printf("\nGraph files created successfully.\n");
    printf("Opening Gnuplot...\n");

    system("gnuplot selection_graph.gnu");


    return 0;
}