#include <stdio.h>
int count = 0;
void toH(int n, char source[], char destination[], char auxillary[])
{
	if (n == 1)
	{
		count++;
		printf("\n%d) Move disk %d from rod %s to rod %s",count,n,source ,destination);
		return;
	}

	toH(n-1, source, auxillary, destination);
	count++;
	printf("\n%d) Move disk %d from rod %s to rod %s",count, n, source, destination);
	toH(n-1, auxillary, destination, source);
}

int main()
{
	int n;
	printf("Enter number of disks: ");
	scanf("%d", &n);
	char source[] = "source";
	char destination[] = "destination";
	char auxillary[] = "auxillary";
	toH(n, source,destination,auxillary); 
	return 0;
}
