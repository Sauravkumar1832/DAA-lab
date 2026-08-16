#include<stdio.h>
#include<stdlib.h>

int binarySearch(int arr[],int n,int x, int *comparison){
    int low=0,high=n-1;

    while(low<=high){
        int mid=low+(high-low)/2;

        (*comparison)++;
        if(arr[mid]==x)
            return mid;

        (*comparison)++;
        if(arr[mid]>x){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }

    return -1;
}


int ternarySearch(int arr[],int n,int x,int *comparison){
    int low=0,high=n-1;

    while(low<=high){
        int third=(high-low)/3;

        int mid1=low+third;
        int mid2=high-third;

        (*comparison)++;
        if(arr[mid1]==x)
            return mid1;

        (*comparison)++;
        if(arr[mid2]==x)
            return mid2;

        (*comparison)++;
        if(x < arr[mid1]){
            high=mid1-1;
        }

        else{
            (*comparison)++;
            if(x > arr[mid2]){
                low=mid2+1;
            }

            else{
                low=mid1+1;
                high=mid2-1;
            }
        }
    }

    return -1;
}


int main(){

    int n,x;

    int binaryComparison=0;
    int ternaryComparison=0;

    printf("enter the no of element of sorted array: ");
    scanf("%d",&n);

    int arr[n];

    printf("enter the elements of sorted array: ");

    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    printf("enter target: ");
    scanf("%d",&x);


    int binaryResult=binarySearch(arr,n,x,&binaryComparison);

    int ternaryResult=ternarySearch(arr,n,x,&ternaryComparison);


    printf("\nBinary search:\n");

    if(binaryResult!=-1){
        printf("element found at index: %d\n",binaryResult);
    }
    else
        printf("element not found\n");

    printf("number of comparisons: %d\n",binaryComparison);


    printf("\nTernary search:\n");

    if(ternaryResult!=-1){
        printf("element found at index: %d\n",ternaryResult);
    }
    else
        printf("element not found\n");

    printf("number of comparisons: %d\n",ternaryComparison);


    printf("\nComparison:\n");

    if(binaryComparison<ternaryComparison)
        printf("binary search performed better\n");

    else if(ternaryComparison<binaryComparison)
        printf("ternary search performed better\n");

    else
        printf("both performed same comparison\n");


    FILE *data = fopen("graph_data.txt","w");

    if(data == NULL){
        printf("Error creating graph_data.txt\n");
        return 1;
    }


    /*
       Generate comparison data for different
       input sizes.
    */

    for(int size=10; size<=1000; size+=10){

        int *testArr = (int *)malloc(size * sizeof(int));

        if(testArr == NULL){
            printf("Memory allocation failed\n");
            fclose(data);
            return 1;
        }


        /*
           Create a sorted array:
           0, 1, 2, 3, ... size-1
        */

        for(int i=0;i<size;i++){
            testArr[i]=i;
        }


        int binaryCount=0;
        int ternaryCount=0;


        /*
           Search for an element that does not exist.
           This gives a large number of comparisons.
        */

        int target=-1;


        binarySearch(testArr,size,target,&binaryCount);

        ternarySearch(testArr,size,target,&ternaryCount);


        fprintf(data,"%d %d %d\n",
                size,
                binaryCount,
                ternaryCount);


        free(testArr);
    }

    fclose(data);


    FILE *gnuplot = fopen("graph.gnu","w");

    if(gnuplot == NULL){
        printf("Error creating graph.gnu\n");
        return 1;
    }


    fprintf(gnuplot,
        "set title 'Binary Search vs Ternary Search'\n"
        "set xlabel 'Number of Elements (n)'\n"
        "set ylabel 'Number of Comparisons'\n"
        "set grid\n"
        "set key left top\n"
        "plot 'graph_data.txt' using 1:2 with linespoints title 'Binary Search', "
        "'graph_data.txt' using 1:3 with linespoints title 'Ternary Search'\n"
        "pause -1\n"
    );


    fclose(gnuplot);


    printf("\nGraph files created successfully.\n");
    printf("Opening Gnuplot...\n");


    system("gnuplot graph.gnu");


    return 0;
}