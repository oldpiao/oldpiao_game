
#include<stdio.h>
#define M 4
#define N 4
#define W 1
void scout(char t1[][N],int,int);
void xg1(char t3[][N],int,int);
void xg2(char t2[][N],int,int);
int tj(char t4[][N],int,int);
void main()
{
	int x=0,y=0;
	char a[M][N];
	int i,j,k;
	for(k=0;k<W;k++)
		printf("第%d关\n",W);
	{
		for(i=0;i<M;i++)
			for(j=0;j<N;j++)
				a[i][j]='O';//○会出错
			scout(a,M,N);
			xg1(a,M,N);
	}
}//main end;

void scout(char t1[][N],int p1,int p2)
{
	int i,j;
	printf("  ");
	for(i=0;i<p2;i++)
	{
		printf("%d ",i);
	}
	printf("\n");
	for(i=0;i<p1;i++)
	{
		printf("%d ",i);
		for(j=0;j<p2;j++)
		{
			if(t1[i][j]=='X')
				printf("●");
			if(t1[i][j]=='O')
				printf("○");
		}
		printf("\n");
	}
}//scout end;

void xg1(char t3[][N],int p5,int p6)
{
	while(tj(t3,p5,p6)==0)
	{
		xg2(t3,p5,p6);
		scout(t3,p5,p6);
	}
	printf("恭喜过关!\n继续第%d关\n",p5);
}//xg1 end;

void xg2(char t2[][N],int p3,int p4)
{
	int i,j,k;
	printf("输入坐标:");
	scanf("%d%d",&i,&j);
	if(i>=p3||i<0||j>=p4||j<0)
	{
		printf("坐标不在区间内\n");
	}
	else
	{
		for(k=0;k<p4;k++)
		{
			if(t2[i][k]=='X')
				t2[i][k]='O';
			else if(t2[i][k]=='O')
				t2[i][k]='X';
		}
		for(k=0;k<p3;k++)
		{
			if(t2[k][j]=='X')
				t2[k][j]='O';
			else if(t2[k][j]=='O')
				t2[k][j]='X';
		}
		if(t2[i][j]=='X')
			t2[i][j]='O';
		else if(t2[i][j]=='O')
			t2[i][j]='X';
	}
	}//xg2 end;

int tj(char t4[][N],int p7,int p8)
{
	int i,j;
	for(i=0;i<p7;i++)
		for(j=0;j<p8;j++)
		{
			if(t4[i][j]!='X')
				return 0;
		}
		return 1;
}//tj end;
