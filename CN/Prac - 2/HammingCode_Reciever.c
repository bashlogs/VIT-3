#include <stdio.h>

int main() 
{
    int datacheck[10],c,c1,c2,c3,i;

    printf("Enter received data bits one by one\n");
    for(i=0;i<7;i++)
        scanf("%d",&datacheck[i]);

    //checking the parity
    // p1->D3 D5 D7
    // p2-> D3 D6 D7
    // p3-> D5 D6 D7
    //if parity is correct then result is zero else 1 
    c1=datacheck[6]^datacheck[4]^datacheck[2]^datacheck[0];
    c2=datacheck[5]^datacheck[4]^datacheck[1]^datacheck[0];
    c3=datacheck[3]^datacheck[2]^datacheck[1]^datacheck[0];
    //Formula to calculate the error bit position
    c=c3*4+c2*2+c1;
    printf("%d%d%d%d\n",c1,c2,c3,c);

    if(c==0) 
    {
        printf("\nNo error while transmission of data\n");
    }
    else 
    {
        printf("\nFound error on position %d",c);

        printf("\nData out : ");
        for(i=0;i<7;i++)
            printf("%d",datacheck[i]);

        printf("\nCorrect message is :");

        //if errorn bit is 0 we complement it else vice versa
        if(datacheck[7-c]==0)
            datacheck[7-c]=1;
        else
            datacheck[7-c]=0;

        for (i=0;i<7;i++) 
        {
            printf("%d",datacheck[i]);
        }
    }
}