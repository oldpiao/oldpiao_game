//贪吃蛇障碍版
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#define M 22
#define N 22
#define S 0.3
int bjm_cout(int p1[M][N],int,int);//地图，蛇，小球创建
int snake(int p2[M][N],int,int,int *,int *,int *);//创建蛇
int ball(int p3[M][N],int,int);//创建小球
int ditu(int p4[M][N],int,int);//创建地图
int bjm_gz(int p5[M][N],int,int);//小球创建规则
int snake2(int p6[M][N],int,int,int *,int *,int *,int *bjm_p6[]);//蛇运动
int bjm_gz2(int p6[M][N],int x6,int y6,int bjm_pd,int *);//蛇运动规则

void main()
{
	int a[M][N];
	int m=M,n=N;
	int k=3;//蛇的长度
	int b_x=10,b_y=9;//初始位置
	char begin;
	int *bjm_p6[100];
	bjm_p6[0]=&a[b_x][b_y];	
	ditu(a,m,n);//创建地图
	ball(a,m,n);//创建小球
	snake(a,m,n,&k,&b_x,&b_y);//创建蛇
	bjm_cout(a,m,n);//地图，蛇，小球创建
/*	printf("输入任意字符开始游戏：");
	scanf("%c",&begin);//开始游戏
*/	
		ditu(a,m,n);//创建地图
		ball(a,m,n);//创建小球
		snake2(a,m,n,&k,&b_x,&b_y,bjm_p6);//蛇运动
		a[10][9]=9;
		a[10][10]=10;
		bjm_cout(a,m,n);//地图，蛇，小球创建
}//主函数

int bjm_cout(int p1[M][N],int x1,int y1)
{
	int i,j;
	for(i=0;i<x1;i++)
	{
		for(j=0;j<y1;j++)
		{	
			if(p1[i][j]==0)
				printf("□");//地图
			else if(p1[i][j]==1)
				printf("●");//蛇
			else if(p1[i][j]==2)
				printf("★");//小球
			else if(p1[i][j]==3)
				printf("─");
			else if(p1[i][j]==4)
				printf("│");
			else if(p1[i][j]==5)
				printf("┍");
			else if(p1[i][j]==6)
				printf("┑");
			else if(p1[i][j]==7)
				printf("┕");
			else if(p1[i][j]==8)
				printf("┙");
			else if(p1[i][j]==9)
				printf("结");
			else if(p1[i][j]==10)
				printf("束");
		}
		printf("\n");
	}
}//地图，蛇，小球创建

int ditu(int p4[M][N],int x4,int y4)
{
	int i,j;
	for(i=0;i<x4;i++)
		for(j=0;j<y4;j++)
			p4[i][j]=0;
    for(j=1;j<y4-1;j++)
	   {
		    p4[0][j]=3;//─
			p4[x4-1][j]=3;//─	
	   }
	   for(i=1;i<x4-1;i++)
	   {
		   p4[i][0]=4;//│
		   p4[i][y4-1]=4;//
	   }
	p4[0][0]=5;//┍
    p4[0][y4-1]=6;//┑
    p4[x4-1][0]=7;//┕
    p4[x4-1][y4-1]=8;//┙
}//创建地图

int snake(int p2[M][N],int x2,int y2,int *t2,int *b_x,int *b_y)
{
	int j;
	for(j=0;j<*t2;j++)
       p2[*b_x][*b_y+j]=1;
}//创建蛇

int ball(int p3[M][N],int x3,int y3)
{
	int i,qu_1,qu_2;
	do
	{
		for(i=0;i<50;i++)
		{
			qu_1=rand()%(x3-2)+1;//地图边属于数组，小球不能在数组上，范围（1，M-2）
		}
		for(i=0;i<50;i++)
		{
			qu_2=rand()%(y3-2)+1;//地图边属于数组，小球不能在数组上，范围（1，N-2）
		}
	}while(p3[qu_1][qu_2]==1);
	p3[qu_1][qu_2]=2;
}//创建小球



int snake2(int p6[M][N],int x6,int y6,int *t6,int *b_x,int *b_y,int *bjm_p6[])
{
	int i,k=0;
	char ch;
	int s;
	for(i=0;i<*t6;i++)
	{
		bjm_p6[i]=&p6[*b_x][*b_y+3-i];
	}//初始化位置
	while(1)//bjm_gz 游戏规则
	{
		ch=getche();
		while(!kbhit()||s==1)//如果不点击就循环
		{
			system("cls");//清屏（电脑）手机c语言用clrscr();
			printf("方向键：w↑s↓a←d→\n");
			switch(ch)
			{
			case 'a': (*b_y)--;
					  s=bjm_gz2(p6,x6,y6,p6[*b_x][*b_y],t6);
					  if(s==1)
						  return 1;
					  
					  p6[*b_x][*b_y]=1;
					  if(s!=2)
					  {
						*bjm_p6[k]=0;
						bjm_p6[k]=&p6[*b_x][*b_y];
						k++;
						if(k==*t6)
							k=0;
					  }
					  else
					  {
						  (*t6)++; 
						  for(i=1;i<((*t6)-k-1);i++)
						  {
							  bjm_p6[(*t6)-i]=bjm_p6[k];
							  bjm_p6[k]=bjm_p6[k+i];
							  bjm_p6[k+i]=bjm_p6[(*t6)-i];						      
						  }
						  bjm_p6[(*t6)-1]=bjm_p6[k];
						  bjm_p6[k]=&p6[*b_x][*b_y];
						  k++;
						  ball(p6,x6,y6);//创建小球 	  
					  }
					  break;

			case 'd': (*b_y)++;
					  s=bjm_gz2(p6,x6,y6,p6[*b_x][*b_y],t6);
					  if(s==1)
						  return 1;
					  
					  p6[*b_x][*b_y]=1;
					  if(s!=2)
					  {
						*bjm_p6[k]=0;
						bjm_p6[k]=&p6[*b_x][*b_y];
						k++;
						if(k==*t6)
							k=0;
					  }
					  else
					  {
						  (*t6)++; 
						  for(i=1;i<((*t6)-k-1);i++)
						  {
							  bjm_p6[(*t6)-i]=bjm_p6[k];
							  bjm_p6[k]=bjm_p6[k+i];
							  bjm_p6[k+i]=bjm_p6[(*t6)-i];						      
						  }
						  bjm_p6[(*t6)-1]=bjm_p6[k];
						  bjm_p6[k]=&p6[*b_x][*b_y];
						  k++;
						  ball(p6,x6,y6);//创建小球 	  
					  }
					  break;
					  
			case 'w': (*b_x)--;
					  s=bjm_gz2(p6,x6,y6,p6[*b_x][*b_y],t6);
					  if(s==1)
						  return 1;
					  
					  p6[*b_x][*b_y]=1;
					  if(s!=2)
					  {
						*bjm_p6[k]=0;
						bjm_p6[k]=&p6[*b_x][*b_y];
						k++;
						if(k==*t6)
							k=0;
					  }
					  else
					  {
						  (*t6)++; 
						  for(i=1;i<((*t6)-k-1);i++)
						  {
							  bjm_p6[(*t6)-i]=bjm_p6[k];
							  bjm_p6[k]=bjm_p6[k+i];
							  bjm_p6[k+i]=bjm_p6[(*t6)-i];						      
						  }
						  bjm_p6[(*t6)-1]=bjm_p6[k];
						  bjm_p6[k]=&p6[*b_x][*b_y];
						  k++;
						  ball(p6,x6,y6);//创建小球 	  
					  }
					  break;
					  
			case 's': (*b_x)++;
					  s=bjm_gz2(p6,x6,y6,p6[*b_x][*b_y],t6);
					  if(s==1)
						  return 1;
					  
					  p6[*b_x][*b_y]=1;
					  if(s!=2)
					  {
						*bjm_p6[k]=0;
						bjm_p6[k]=&p6[*b_x][*b_y];
						k++;
						if(k==*t6)
							k=0;
					  }
					  else
					  {
						  (*t6)++; 
						  for(i=1;i<((*t6)-k-1);i++)
						  {
							  bjm_p6[(*t6)-i]=bjm_p6[k];
							  bjm_p6[k]=bjm_p6[k+i];
							  bjm_p6[k+i]=bjm_p6[(*t6)-i];						      
						  }
						  bjm_p6[(*t6)-1]=bjm_p6[k];
						  bjm_p6[k]=&p6[*b_x][*b_y];
						  k++;
						  ball(p6,x6,y6);//创建小球 	  
					  }
					  break;

			default: break;
			}
			bjm_cout(p6,x6,y6);//地图，蛇，小球创建
			Sleep(S*1000);//函数暂停S秒
		}//蛇运动
	}
}//蛇运动

int bjm_gz2(int p6[M][N],int x6,int y6,int bjm_pd,int *t6)
{
	if(bjm_pd==1||bjm_pd==3||bjm_pd==4||bjm_pd==5||bjm_pd==6||bjm_pd==7||bjm_pd==8)
	{
		return 1;
	}
	else if(bjm_pd==2)
	{
		return 2;
	}

}//蛇的运动规则
