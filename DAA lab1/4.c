#include<stdio.h>
long long moves=0;

void towerOfHanoi(int n,char source,char auxilary,char destination){
    if(n==1)
    {
        printf("Move disk 1 from %c to %c\n",source,destination);
        moves++;
        return;
    }

    //move n-1 disk from source to auxilary
    towerOfHanoi(n-1,source,destination,auxilary);

    //Move nth disk from source to destination
    printf("Move disk %d from %c to %c\n",n,source,destination);
    moves++;

    //move n-1 disks from auxilary to destination
    towerOfHanoi(n-1,auxilary,source,destination);
}
int main(){
    int n;
    printf("Enter number of disks:");
    scanf("%d",&n);

    towerOfHanoi(n,'A','B','C');
    printf("\nTotal no of moves=%lld\n",moves);
    return 0;
}