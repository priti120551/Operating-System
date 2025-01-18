#include<stdio.h>
#include<stdlib.h>
main()
{
	int queue[2],n,head,i,j,k,seek=0,max,diff;
	float avg;
	printf("Enter the max range of disk\n");
	scanf("%d",&max);
	printf("Enter size of queue\n");
	scanf("%d",&n);
	printf("Enter the queue of disk positions to be read\n");
	for(i=0;i<n;i++)
		scanf("%d",&queue[i]);
	printf("Enter initial head position\n");
	scanf("%d",&head);
	queue[0]=head;
	for(j=0;j<=n-1;j++)
	{
		diff=abs(queue[j+1]-queue[j]);
		seek+=diff;
		printf("Disk head moves from %d to %d with %d\n",queue[j],queue[j+1],diff);
	}
	printf("Total seek time is%d\n",seek);
	avg=seek/(float)n;
	printf("Avearage seek time is%d\n",seek);
	avg=seek/(float)n;
	printf("Avearage seek time is %f\n",avg);
	return 0;
}

