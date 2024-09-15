#include <stdio.h>



//Funtion Exchange values A to B 
void swap(int *a ,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

//Funtion partite the array 
int partition(int arr[],int low,int high){

    int pivot= arr[high];
    int i=low-1;

    for(int j=low;j<high;j++){
        if(arr[j]<=pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;

}





int main(){

    return 0;
}