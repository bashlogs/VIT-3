#include <stdio.h>

int main(){
    int n,b=2;
    printf("Enter the number of people: ");
    scanf("%d", &n);
    printf("Every alternate person is killed\n");
    int a[n];
    for(int i=0; i<n; i++){
        a[i] = 1;
    }

    int pos = b;
    for(int i=0; i<n-1; i++){
        int count = 0;
        // printf("%d\n", pos);
        a[pos-1] = 0;
        printf("%dth iteration: ",i+1);
        for(int i=0; i<n; i++){
            printf("%d ", a[i]);
        }
        printf("\n");
        while(count < b){
            pos = pos%n;
            if(a[pos] == 1){
                count++;
                pos++;
            }
            else{
                pos++;
            }
        }
    }

    for(int i=0; i<n; i++){
        if(a[i] == 1){
            printf("\nSurvived Person is at position: %d", i+1);
        }
    }
}