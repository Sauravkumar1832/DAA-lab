//Dictionary operation using an unsorted array
#include<stdio.h>
#define MAX 100

int arr[MAX]={1,2,3,4,5};
int n=5;

//insert
void insert(int key){
    if(n==MAX){
        printf("dictionary full");
        return;
    }
    arr[n]=key;
    n++;
    printf("inserted successfully!");
}

//search
int search(int key){
    for(int i=0;i<n;i++){
        if(arr[i]==key){
            return i;
        }
    }
    return -1;
}

//delete
void delete(int key){
    int pos=search(key);
    if(pos==-1){
        printf("Key not found\n");
        return;
    }
    for(int i=pos;i<n-1;i++){
        arr[i]=arr[i+1];
    }
    n--;
    printf("deleted successfully");
}
//maximum
void maximum(){
    int max=arr[0];
    if(n==0){
        printf("dictionary is empty");
    }
    for(int i=0;i<n;i++){
        if(arr[i]>max){
            max=arr[i];
        }
    }
    printf("max:%d\n",max);
}
//minimum
void minimum(){
    int min=arr[0];
    if(n==0){
        printf("dictionary is empty");
        return;
    }
    for(int i=0;i<n;i++){
        if(arr[i]<min){
            min=arr[i];
        }
    }
    printf("min:%d\n",min);
}
//predecessor
void predecessor(int key){
    int pred=-1;
    for(int i=0;i<n;i++){
        if(arr[i]<key){
            if(pred==-1 || arr[i]>pred){
                pred=arr[i];
            }
        }   
    }
    if(pred==-1) {
        printf("no predecessor");
    }else
    printf("predecessor:%d\n",pred);
}

//successor
void successor(int key){
    int succ=0;
    for(int i=0;i<n;i++){
        if(arr[i]>key){
            if(succ=-1 || arr[i]<succ){
                succ=arr[i];
            }
        }
    }
    if(succ==-1){
        printf("no successor");
    }
    else
    printf("successor:%d\n",succ);
}
//display
void display(){
    if(n==0){
        printf("dictionary is empty");
        return;
    }
    printf("\ndictionary\n");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
        printf("\n");
    }
}
int main(){
    int choice,key,pos;
    while(1){
        printf("\n====dictionary====\n");
        printf("1.insert\n");
        printf("2.search\n");
        printf("3.delete\n");
        printf("4.maximum\n");
        printf("5.minimum\n");
        printf("6.predecessor\n");
        printf("7.successor\n");
        printf("8.display\n");
        printf("9.Exit\n");

        printf("enter a choice:");
        scanf("%d",&choice);

        switch(choice){
            case 1:
            printf("enter key:");
            scanf("%d",&key);
            insert(key);
            break;

            case 2:
            printf("enter key:");
            scanf("%d",&key);
            pos=search(key);
            if(pos==-1){
                printf("key not found");
            }
            else{
                printf("key found at index: %d\n",pos);
            }
            break;

            case 3:
            printf("enter key:");
            scanf("%d",&key);
            delete(key);
            break;

            case 4:
            maximum();
            break;

            case 5:
            minimum();
            break;

            case 6:
            printf("enter key:");
            scanf("%d",&key);
            predecessor(key);
            break;

            case 7:
            printf("enter key:");
            scanf("%d",&key);
            successor(key);
            break;

            case 8:
            display();
            break;

            case 9:
            return 0;

            default: 
            printf("invalid choice\n!");
        }
    }
    return 0;
}