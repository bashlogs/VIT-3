    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>

    int tile=1;

    void print_matrix(int **square,int size,int r,int s){
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++) {
                if(r==i && s==j) 
                    printf("X\t");
                else{ 
                    printf("%d\t",square[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    void matrix(int **square, int size, int i, int j, int x, int y){
        if(size==1) return;
        int size1=size/2;
        int current_tile=tile++;
        printf("current_tile: %d\n",current_tile);
        if(i<x+size1 && j<y+size1) 
            matrix(square,size1,i,j,x,y);
        else{
            square[x+size1-1][y+size1-1]=current_tile;
            print_matrix(square,size,x,y);
            matrix(square,size1,x+size1-1,y+size1-1,x,y) ;
        }

        if(i>=x+size1 && j<y+size1) 
            matrix(square,size1,i,j,x+size1,y);
        else{
            square[x+size1][y+size1-1]=current_tile;
            print_matrix(square,size,x,y);
            matrix(square,size1,x+size1,y+size1-1,x+size1,y);
        }
        print_matrix(square,size,x,y);

        if(i<x+size1 && j>=y+size1) 
            matrix(square,size1,i,j,x,y+size1);
        else{
            square[x+size1-1][y+size1]=current_tile;
            print_matrix(square,size,x,y);
            matrix(square,size1,x+size1-1,y+size1,x,y+size1);
        }
        print_matrix(square,size,x,y);

        if(i>=x+size1 && j>=y+size1) 
            matrix(square,size1,i,j,x+size1,y+size1);
        else{
            square[x+size1][y+size1]=current_tile;
            print_matrix(square,size,x,y);
            matrix(square,size1,x+size1,y+size1,x+size1,y+size1);
        }
        print_matrix(square,size,x,y);
    }

    

    int main() {
        int i,j,n;
        printf("Enter value of n: ");
        scanf("%d",&n);
        int size=pow(2,n);
        int **sqaure=(int **)malloc(size*sizeof(int*));

        for(int i=0;i<size;i++){
            sqaure[i]=(int *)malloc(size*sizeof(int));
        }

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++) 
                sqaure[i][j]=0;
        }

        printf("Enter x value of cell: ");
        scanf("%d",&i);
        printf("Enter y value of cell: ");
        scanf("%d",&j);

        matrix(sqaure,size,i,j,0,0);
        printf("\nMatrix:\n");
        print_matrix(sqaure,size,i,j);
        return 0;
    }