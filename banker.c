#include<stdio.h>
int N;
int M;
int Available[10];
int tempAvailable[10];
int Max[10][10];
int Need[10][10];
int Safeseq[10];
int Alloc[10][10];
void AcceptInput()
{
	int i;
	int j;
	printf("\nEnter the number of process:");
	scanf("%d",&N);
	printf("\nEnter the number of res type:");
	scanf("%d",&M);
	printf("\nEnter Available:");
	for(i=0;i<M;i++)
	{
		printf("\nEnter number of instance for res type %c:",65+i);
		scanf("%d",&Available[i]);
		tempAvailable[i]=Available[i];
	}
	printf("\nEnter Max:\n");
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
		{
			printf("\nEnter Max for Process P%d,Res[%c]",i,65+j);
			scanf("\n%d",&Max[i][j]);
		}
		printf("\nEnter Allocation:\n");
		for(i=0;i<N;i++)
			for(j=0;j<M;j++)
			{
				printf("\nEnter Alloc for Process P%d,Res[%c]",i,65+j);
				scanf("\n%d",&Alloc[i][j]);
			}
			for(i=0;i<N;i++)
				Safeseq[i]=-1;
}
void DisplayMatrix(int a[10][10],int N,int M)
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
			printf("%5d",a[i][j]);
		printf("\n");
	}
}
void CalNeed()
{
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			Need[i][j]=Max[i][j]-Alloc[i][j];
}
int IsFeasible(int Pno)
{
	int i;
	for(i=0;i<M;i++)
		if(Need[Pno][i]>Available[i])
			return 0;
	return 1;
}
void Banker()
{
	int k=0;
	int i,j;
	int flags[5]={0,0,0,0,0};
	int finish=0;
	while(finish!=1)
	{
		for(i=0;i<N;i++)
		{
			if(IsFeasible(i) & flags[i]!=1)
			{
				for(j=0;j<M;j++)
				Available[j]=Available[j]-Need[i][j];
				
				for(j=0;j<M;j++)
				Alloc[i][j]=Alloc[i][j]+Need[i][j];
					
				for(j=0;j<M;j++)
					Available[j]=Available[j]+Alloc[i][j];
				Safeseq[k++]=i;
				flags[i]=1;
			}
		}
		for(i=0;i<N;i++)
			if(flags[i]==1)
				continue;
			else
				break;
		
		if(i==N)
			finish=1;
	}
}
void PrintSafeSeq()
{
	int i;
	printf("\nSafe Seq");
	printf("\n<");
	for(i=0;i<N;i++)
		printf("p%d,",Safeseq[i]);
	printf("\b>\n");
}
void NewRequest()
{
		int i;
		int NewReq[10];
		for(i=0;i<M;i++)
		{
			printf("\nEnter %c:",65+i);
			scanf("%d",&NewReq[i]);
		}
		for(i=0;i<M;i++)
			if(NewReq[i]>tempAvailable[i])
				break;
			else
				continue;
		if(i!=M)
		printf("\nNot Feasible, hence resource cannot be granted");
		else
			printf("\nFeasible,and request can be granted");
}

int main()
{
	AcceptInput();
	CalNeed();
	printf("\nMAX:\n");
	DisplayMatrix(Max,N,M);
	printf("\nALLOCATION:\n");
	DisplayMatrix(Alloc,N,M);
	printf("\nNEED:\n");
	DisplayMatrix(Need,N,M);
	Banker();
	PrintSafeSeq();
	NewRequest();
	return 0;
}
	
				
					
				
		
			
				
