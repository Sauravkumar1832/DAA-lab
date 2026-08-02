#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    int i,n;   //n:no of tosses and i:no of loops
    int fairHead=0,fairTail=0;
    int biasedHead=0,biasedTail=0;

    printf("enter number of tosses:");
    scanf("%d",&n);
    srand(time(NULL));   //rand generates random nos.

    //fair coin
    for(int i=0;i<n;i++){
        if(rand()%2==0)
        fairHead++;
        else
        fairTail++;
    }

    //baised coin (70% Head, 30% Tail)
    for(int i=0;i<n;i++){
        int r=rand()%100;  //random no: 0 to 99
        if(r<70)
        biasedHead++;
        else
        biasedTail++;
    }
    printf("\n----- Fair Coin -----\n");
    printf("Heads = %d\n", fairHead);
    printf("Tails = %d\n", fairTail);
    printf("Probability of Head = %.4f\n", (float)fairHead / n);
    printf("Probability of Tail = %.4f\n", (float)fairTail / n);

    printf("\n----- Biased Coin (70%% Head) -----\n");
    printf("Heads = %d\n", biasedHead);
    printf("Tails = %d\n", biasedTail);
    printf("Probability of Head = %.4f\n", (float)biasedHead / n);
    printf("Probability of Tail = %.4f\n", (float)biasedTail / n);

    return 0;
}
