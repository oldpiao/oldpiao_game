//作者 朴老大
//俄罗斯方块1.0
//bug1 向右有可能会穿墙，需要在move中逐个加*p对于*p4的约束条件
//左右脚有可能会冲出地图
//左右移动的时候有些方块会穿过去，因为没有设置单独的判定
//偶尔有消除，只消了一块的情况
#include<stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include<conio.h>
#define M 20
#define N 18
#define S 500
#define W 5
int ditu(int a[M][N],int *m,int *n);
int dayin(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p1,int p2,int *x1);
int fangkuai(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p1,int p2);
int fangkuai2(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p3,int p4);
int stop(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p3,int p4,int *x1);
int move(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int *p3,int *p4,int *x1,char *ch);
void main()
{
	int m,n;
	int a[M][N],b[W],c[W];
	int p,q;//选择方块，初始化下一方块
	int p1=6,p2=13;
	int p3,p4,sum;
	int x1;
	int s;//下落速度
	int pd,pd2=0;//判断是否落地
	char ch;//点击
	int i,j,k;
	int bjm;//消除专用
	s=S;//初始化下落速度（毫秒）
	x1=0;
	m=M;
	n=N;
	ditu(a,&m,&n);//创建地图
	srand((unsigned)time(NULL));
	q=rand()%28;//初始化一个方块
	do
	{   	
		p3=1;
		p4=5;//初始化方块位置
		pd=1;//初始化落地条件
		p=q;//选择方块
		q=rand()%28;//确定下一个方块
//		p=25;//测试用，之后删掉
		fangkuai(a,b,c,&m,&n,&q,p1,p2);//创建方块
		while(pd!=0)//下落条件
		{
			if(!kbhit())
			{
				system("cls");
				for(i=0;i<W;i++)
				{
					b[i]=0;
					c[i]=0;
				}//初始化b,c
				dayin(a,b,c,&m,&n,&p,p3,p4,&x1);//打印地图
		/*		for(i=0;b[i]!='\0';i++)
				{
					printf("%d,%d,%d\n",b[i],c[i],a[b[i]+1][c[i]]);
				}//测试用
		*/
				pd=stop(a,b,c,&m,&n,&p,p3,p4,&x1);//方块停止条件
				if(pd==0)
					continue;//跳过循环中剩下的内容
				fangkuai2(a,b,c,&m,&n,&p,p3,p4);//恢复方块
				p3++;
				Sleep(s);
			}
			else
			{
				system("cls");
				for(i=0;i<W;i++)
				{
					b[i]=0;
					c[i]=0;
				}//初始化b,c
				ch=getche();
				fangkuai2(a,b,c,&m,&n,&p,p3,p4);//恢复方块
				move(a,b,c,&m,&n,&p,&p3,&p4,&x1,&ch);//移动			
				dayin(a,b,c,&m,&n,&p,p3,p4,&x1);//打印地图
				pd=stop(a,b,c,&m,&n,&p,p3,p4,&x1);//方块停止条件
				Sleep(100);
				if(pd==0)
					continue;//跳过循环中剩下的内容
			}
		}
		for(i=1;i<19;i++)
		{
			sum=0;
			for(j=1;j<11;j++)
				sum=sum+a[i][j];
			if(sum==110)
			{
				x1=x1+10;
				for(k=i;k>1;k--)
				{
					sum=0;
					for(j=1;j<11;j++)
					{
						a[k][j]=a[k-1][j];
						sum=sum+a[i][j];
						if(sum==0)
						{
							bjm=0;
							break;
						}
						bjm=1;
					}
					if(bjm==0)
						break;
				}

			}
		}
		for(i=5;i<10;i++)
			for(j=n-6;j<n-1;j++)
			{
				a[i][j]=0;	
			}
	}while(pd2==0);//写入游戏结束的条件
}//main end;
int ditu(int a[M][N],int *m,int *n)
{
	int i,j;
	for(i=0;i<*m;i++)
		for(j=0;j<*n;j++)
		{
			a[i][j]=0;
		}
		for(j=0;j<*n;j++)
		{
			a[0][j]=1;
			a[19][j]=1;
		}
		for(j=12;j<*n-1;j++)
		{
			a[4][j]=1;
			a[10][j]=1;
			a[15][j]=1;
		}
		for(i=0;i<*m;i++)
		{
			a[i][0]=2;
			a[i][11]=2;
			a[i][17]=2;
		}

		a[0][0]=3;
		a[19][0]=4;
		a[0][17]=5;
		a[19][17]=6;
		a[0][11]=7;
		a[4][11]=8;
		a[10][11]=8;
		a[15][11]=8;
		a[4][17]=9;
		a[10][17]=9;
		a[15][17]=9;
		a[19][11]=10;
		a[17][12]=12;
		a[17][13]=13;
		a[17][14]=14;
		a[17][15]=15;
		a[17][16]=16;

}//ditu end;
int dayin(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p1,int p2,int *x1)
{
	int i,j;
	printf("  a,b：左右移动\n  w:变形\n  s:加速下落\n");
	fangkuai(a,b,c,m,n,p,p1,p2);//创建方块
	for(i=0;i<*m;i++)
	{
		for(j=0;j<*n;j++)
		{
			if(a[i][j]==0)
			{
				printf("□");
			}
			if(a[i][j]==1)
				printf("━");
			if(a[i][j]==2)
				printf("┃");
			if(a[i][j]==3)
				printf("┏");
			if(a[i][j]==4)
				printf("┗");
			if(a[i][j]==5)
				printf("┓");
			if(a[i][j]==6)
				printf("┛");
			if(a[i][j]==7)
				printf("┳");
			if(a[i][j]==8)
				printf("┣");
			if(a[i][j]==9)
				printf("┫");
			if(a[i][j]==10)
				printf("┻");
			if(a[i][j]==11)
			{
				printf("■");
//				system("color 01");//01，前面是被景色，后面是前景色
			}
			if(a[i][j]==12)
				printf("分");
			if(a[i][j]==13)
				printf("数");
			if(a[i][j]==14)
				printf("%6d",*x1);
		
		}
		printf("\n");
	}

}//dayin end;
int fangkuai(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p1,int p2)
{
	int i,j,k;
	for(i=0;i<W;i++)
	{
		b[i]=0;
		c[i]=0;
	}
	if(*p==0)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
//		printf("%d,%d,%d,%d,%d",p1+1,b[k],c[k],b[k+1],c[k+1]);//测试用
	}//■
	if(*p==1)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
	}//■
	if(*p==2)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
	}//■
	if(*p==3)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
	}//■
	if(*p==4)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2]=11;
		a[p1+3][p2]=11;
		b[k]=p1+3;
		c[k]=p2;
	}// ▎
	if(*p==5)
	{
		k=0;
		a[p1][p2]=11;
		a[p1][p2+1]=11;
		a[p1][p2+2]=11;
		a[p1][p2+3]=11;
		b[k]=p1;
		c[k]=p2;
		b[k+1]=p1;
		c[k+1]=p2+1;
		b[k+2]=p1;
		c[k+2]=p2+2;
		b[k+3]=p1;
		c[k+3]=p2+3;
	}// ▂
	if(*p==6)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2]=11;
		a[p1+3][p2]=11;
		b[k]=p1+3;
		c[k]=p2;
	}// ▎
	if(*p==7)
	{
		k=0;
		a[p1][p2]=11;
		a[p1][p2+1]=11;
		a[p1][p2+2]=11;
		a[p1][p2+3]=11;
		b[k]=p1;
		c[k]=p2;
		b[k+1]=p1;
		c[k+1]=p2+1;
		b[k+2]=p1;
		c[k+2]=p2+2;
		b[k+3]=p1;
		c[k+3]=p2+3;
	}// ▂
	if(*p==8)
	{
		k=0;
		a[p1][p2+1]=11;
		a[p1+1][p2]=11;
		a[p1+1][p2+1]=11;
		a[p1+1][p2+2]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
		b[k+2]=p1+1;
		c[k+2]=p2+2;
	}//┻
	if(*p==9)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+1][p2+1]=11;
		a[p1+2][p2]=11;
		b[k]=p1+1;
		c[k]=p2+1;
		b[k+1]=p1+2;
		c[k+1]=p2;
	}//┣
	if(*p==10)
	{
		k=0;
		a[p1][p2]=11;
		a[p1][p2+1]=11;
		a[p1][p2+2]=11;
		a[p1+1][p2+1]=11;	
		b[k]=p1;
		c[k]=p2;
		b[k+1]=p1;
		c[k+1]=p2+2;
		b[k+2]=p1+1;
		c[k+2]=p2+1;
	}//┳
	if(*p==11)
	{
		k=0;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2+1]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+2;
		c[k+1]=p2+1;
	}//┫
	if(*p==12)
	{
		k=0;
		a[p1][p2+1]=11;
		a[p1][p2]=11;
		a[p1+1][p2+1]=11;
		a[p1+1][p2+2]=11;
		b[k]=p1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
		b[k+2]=p1+1;
		c[k+2]=p2+2;
	}//Z
	if(*p==13)
	{
		k=0;
		a[p1+2][p2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+2;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
	}//N
	if(*p==14)
	{
		k=0;
		a[p1][p2+1]=11;
		a[p1][p2]=11;
		a[p1+1][p2+1]=11;
		a[p1+1][p2+2]=11;
		b[k]=p1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
		b[k+2]=p1+1;
		c[k+2]=p2+2;
	}//Z
	if(*p==15)
	{
		k=0;
		a[p1+2][p2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+2;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
	}//N
	if(*p==16)
	{
		k=0;
		a[p1][p2+2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1;
		c[k]=p2+2;
		b[k+1]=p1+1;
		c[k+1]=p2;
		b[k+2]=p1+1;
		c[k+2]=p2+1;
	}//S
	if(*p==17)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+2;
		c[k+1]=p2+1;
	}//H
	if(*p==18)
	{
		k=0;
		a[p1][p2+2]=11;
		a[p1+1][p2]=11;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1;
		c[k]=p2+2;
		b[k+1]=p1+1;
		c[k+1]=p2;
		b[k+2]=p1+1;
		c[k+2]=p2+1;
	}//S
	if(*p==19)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2+1]=11;
		a[p1+1][p2+1]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+2;
		c[k+1]=p2+1;
	}//H
	if(*p==20)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2]=11;
		a[p1+2][p2+1]=11;
		b[k]=p1+2;
		c[k]=p2;
		b[k+1]=p1+2;
		c[k+1]=p2+1;
	}// L
	if(*p==21)
	{
		k=0;
		a[p1][p2]=11;
		a[p1][p2+1]=11;
		a[p1][p2+2]=11;
		a[p1+1][p2]=11;
		b[k]=p1;
		c[k]=p2+1;
		b[k+1]=p1;
		c[k+1]=p2+2;
		b[k+2]=p1+1;
		c[k+2]=p2;
	}// ┏━
	if(*p==22)
	{
		k=0;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		a[p1+2][p2+1]=11;
		a[p1][p2]=11;
		b[k]=p1+2;
		c[k]=p2+1;
		b[k+1]=p1;
		c[k+1]=p2;
	}//7
	if(*p==23)
	{
		k=0;
		a[p1+1][p2]=11;
		a[p1+1][p2+1]=11;
		a[p1+1][p2+2]=11;
		a[p1][p2+2]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
		b[k+2]=p1+1;
		c[k+2]=p2+2;
	}// ━┛
		if(*p==24)
	{
		k=0;
		a[p1][p2+1]=11;
		a[p1+1][p2+1]=11;
		a[p1+2][p2+1]=11;
		a[p1+2][p2]=11;
		b[k]=p1+2;
		c[k]=p2+1;
		b[k+1]=p1+2;
		c[k+1]=p2;
	}//J
	if(*p==25)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+1][p2+1]=11;
		a[p1+1][p2+2]=11;
		b[k]=p1+1;
		c[k]=p2;
		b[k+1]=p1+1;
		c[k+1]=p2+1;
		b[k+2]=p1+1;
		c[k+2]=p2+2;
	}// ┗━
		if(*p==26)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2]=11;
		a[p1][p2+1]=11;
		b[k]=p1+2;
		c[k]=p2;
		b[k+1]=p1;
		c[k+1]=p2+1;
	}// F
	if(*p==27)
	{
		k=0;
		a[p1][p2]=11;
		a[p1][p2+1]=11;
		a[p1][p2+2]=11;
		a[p1+1][p2+2]=11;
		b[k]=p1;
		c[k]=p2;
		b[k+1]=p1;
		c[k+1]=p2+1;
		b[k+2]=p1+1;
		c[k+2]=p2+2;
	}// ━┓
	


}//fangkuai end;
int fangkuai2(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p1,int p2)
{
	int i,j,k;
	for(i=0;i<W;i++)
	{
		b[i]=0;
		c[i]=0;
	}
	if(*p==0)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//■
	if(*p==1)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//■
	if(*p==2)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//■
	if(*p==3)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//■
	if(*p==4)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2]=0;
		a[p1+3][p2]=0;
	}// ▎
	if(*p==5)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1][p2+3]=0;
	}// ▂
	if(*p==6)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2]=0;
		a[p1+3][p2]=0;
	}// ▎
	if(*p==7)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1][p2+3]=0;
	}// ▂
	if(*p==8)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1+1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2+2]=0;
	}//┻
	if(*p==9)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+2][p2]=0;
	}//┣
	if(*p==10)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1+1][p2+1]=0;	
	}//┳
	if(*p==11)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2+1]=0;
	}//┫
	if(*p==12)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2+2]=0;
	}//Z
	if(*p==13)
	{
		k=0;
		a[p1+2][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//N
	if(*p==14)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2+2]=0;
	}//Z
	if(*p==15)
	{
		k=0;
		a[p1+2][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//N
	if(*p==16)
	{
		k=0;
		a[p1][p2+2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//S
	if(*p==17)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//H
	if(*p==18)
	{
		k=0;
		a[p1][p2+2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//S
	if(*p==19)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//H
	if(*p==20)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2]=0;
		a[p1+2][p2+1]=0;
	}// L
	if(*p==21)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1+1][p2]=0;
	}// ┏━
	if(*p==22)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
		a[p1+2][p2+1]=0;
		a[p1][p2]=0;
	}//7
	if(*p==23)
	{
		k=0;
		a[p1+1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2+2]=0;
		a[p1][p2+2]=0;
	}// ━┛
		if(*p==24)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
		a[p1+2][p2+1]=0;
		a[p1+2][p2]=0;
	}//J
	if(*p==25)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2+2]=0;
	}// ┗━
		if(*p==26)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2]=0;
		a[p1][p2+1]=0;
	}// F
	if(*p==27)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1+1][p2+2]=0;
	}// ━┓

}//fangkuai2 end;

int stop(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p3,int p4,int *x1)
{
	int i;
	for(i=0;b[i]!='\0';i++)//判断是否落地
	{
//	    printf("%d,%d,%d\n",b[i],c[i],a[b[i]+1][c[i]]);//测试用
		if(a[b[i]+1][c[i]]!=0)
			return 0;
	}
	return 1;
}//stop end;
int move(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int *p3,int *p4,int *x1,char *ch)
{
	switch(*ch)
	{
		case 'a':
			(*p4)--;
			if(*p4==0)
				(*p4)++;
				break;
		case 'd':
			(*p4)++;
			switch(*p)
			{
			case 4:case 6:
				if(*p4==11)(*p4)--;break;
			case 0:case 1:case 2:case 3:case 9:case 11:case 13:case 15:case 17:case 19:case 20:case 22:case 24:case 26:
				if(*p4==10)(*p4)--;break;
			case 8:case 10:case 12:case 14:case 16:case 18:case 21:case 23:case 25:case 27:
				if(*p4==9)(*p4)--;break;
			case 5:case 7:
				if(*p4==8)(*p4)--;break;
			}
			if(*p4==11)
				(*p4)--;
			break;
		case 'w':
			(*p)++;
			switch(*p)
			{
			case 4:case 6:
				if(*p4>=11)*p4=10;break;
			case 0:case 1:case 2:case 3:case 9:case 11:case 13:case 15:case 17:case 19:case 20:case 22:case 24:case 26:
				if(*p4>=10)*p4=9;break;
			case 8:case 10:case 12:case 14:case 16:case 18:case 21:case 23:case 25:case 27:
				if(*p4>=9)*p4=8;break;
			case 5:case 7:
				if(*p4>=8)*p4=7;break;
			}
			if((*p)%4==0)
				*p=(*p)-4;
			
			break;
		case 's':(*p3)++;
			switch(*p)
			{
			case 4:case 6:
				if(*p4>=11)*p4=10;break;
			case 0:case 1:case 2:case 3:case 9:case 11:case 13:case 15:case 17:case 19:case 20:case 22:case 24:case 26:
				if(*p4>=10)*p4=9;break;
			case 8:case 10:case 12:case 14:case 16:case 18:case 21:case 23:case 25:case 27:
				if(*p4>=9)*p4=8;break;
			case 5:case 7:
				if(*p4>=8)*p4=7;break;
			}
			break;
		default:break;
	}
}//move end;
