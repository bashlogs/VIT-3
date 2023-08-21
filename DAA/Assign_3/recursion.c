#include <stdio.h>

int josephus(int n){
    if(n==1){
        return 1;
    }
    else if(n%2==0){
        int m=n/2;
        return  2*josephus(m)-1;
    }
    else{
        int m=(n-1)/2;
        return 2*josephus(m)+1;
    }
}

int main()
{
    int n, a;
    printf("\nEnter no. of peoples: ");
    scanf("%d", &n);
    printf("The value of K is fixed to 2\n");
    int survivor = josephus(n);
    printf("\nTime Complexity: O(logN)");
    printf("\nThe survivor is at position: %d\n", survivor);
    return 0;
}
