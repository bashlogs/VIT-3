#include<stdio.h>
#include<math.h>

int toH(int a, int n){
    int i = pow(2, a-1);
    if (n==i)
    {
        return n-1;
    }
    else if (n<i)
    {
        return toH(a-1, n);
    }
    else{
        return toH(a-1, n-i);
    }
}

int main(){
    int disk, step;
    printf("Enter the total no. of disk: ");
    scanf("%d" , &disk);
    printf("Enter the step number: ");
    scanf("%d" , &step);
    int ans = toH(disk,step);
    printf("The disk moved at step %d is: %d", step, ans);
} 