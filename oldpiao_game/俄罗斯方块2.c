//���� ���ϴ�
//����˹����1.0
//bug1 �����п��ܻᴩǽ����Ҫ��move�������*p����*p4��Լ������
//���ҽ��п��ܻ�����ͼ
//�����ƶ���ʱ����Щ����ᴩ��ȥ����Ϊû�����õ������ж�
//ż����������ֻ����һ������
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
	int p,q;//ѡ�񷽿飬��ʼ����һ����
	int p1=6,p2=13;
	int p3,p4,sum;
	int x1;
	int s;//�����ٶ�
	int pd,pd2=0;//�ж��Ƿ����
	char ch;//���
	int i,j,k;
	int bjm;//����ר��
	s=S;//��ʼ�������ٶȣ����룩
	x1=0;
	m=M;
	n=N;
	ditu(a,&m,&n);//������ͼ
	srand((unsigned)time(NULL));
	q=rand()%28;//��ʼ��һ������
	do
	{   	
		p3=1;
		p4=5;//��ʼ������λ��
		pd=1;//��ʼ���������
		p=q;//ѡ�񷽿�
		q=rand()%28;//ȷ����һ������
//		p=25;//�����ã�֮��ɾ��
		fangkuai(a,b,c,&m,&n,&q,p1,p2);//��������
		while(pd!=0)//��������
		{
			if(!kbhit())
			{
				system("cls");
				for(i=0;i<W;i++)
				{
					b[i]=0;
					c[i]=0;
				}//��ʼ��b,c
				dayin(a,b,c,&m,&n,&p,p3,p4,&x1);//��ӡ��ͼ
		/*		for(i=0;b[i]!='\0';i++)
				{
					printf("%d,%d,%d\n",b[i],c[i],a[b[i]+1][c[i]]);
				}//������
		*/
				pd=stop(a,b,c,&m,&n,&p,p3,p4,&x1);//����ֹͣ����
				if(pd==0)
					continue;//����ѭ����ʣ�µ�����
				fangkuai2(a,b,c,&m,&n,&p,p3,p4);//�ָ�����
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
				}//��ʼ��b,c
				ch=getche();
				fangkuai2(a,b,c,&m,&n,&p,p3,p4);//�ָ�����
				move(a,b,c,&m,&n,&p,&p3,&p4,&x1,&ch);//�ƶ�			
				dayin(a,b,c,&m,&n,&p,p3,p4,&x1);//��ӡ��ͼ
				pd=stop(a,b,c,&m,&n,&p,p3,p4,&x1);//����ֹͣ����
				Sleep(100);
				if(pd==0)
					continue;//����ѭ����ʣ�µ�����
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
	}while(pd2==0);//д����Ϸ����������
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
	printf("  a,b�������ƶ�\n  w:����\n  s:��������\n");
	fangkuai(a,b,c,m,n,p,p1,p2);//��������
	for(i=0;i<*m;i++)
	{
		for(j=0;j<*n;j++)
		{
			if(a[i][j]==0)
			{
				printf("��");
			}
			if(a[i][j]==1)
				printf("��");
			if(a[i][j]==2)
				printf("��");
			if(a[i][j]==3)
				printf("��");
			if(a[i][j]==4)
				printf("��");
			if(a[i][j]==5)
				printf("��");
			if(a[i][j]==6)
				printf("��");
			if(a[i][j]==7)
				printf("��");
			if(a[i][j]==8)
				printf("��");
			if(a[i][j]==9)
				printf("��");
			if(a[i][j]==10)
				printf("��");
			if(a[i][j]==11)
			{
				printf("��");
//				system("color 01");//01��ǰ���Ǳ���ɫ��������ǰ��ɫ
			}
			if(a[i][j]==12)
				printf("��");
			if(a[i][j]==13)
				printf("��");
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
//		printf("%d,%d,%d,%d,%d",p1+1,b[k],c[k],b[k+1],c[k+1]);//������
	}//��
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
	}//��
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
	}//��
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
	}//��
	if(*p==4)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2]=11;
		a[p1+3][p2]=11;
		b[k]=p1+3;
		c[k]=p2;
	}// ��
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
	}// �y
	if(*p==6)
	{
		k=0;
		a[p1][p2]=11;
		a[p1+1][p2]=11;
		a[p1+2][p2]=11;
		a[p1+3][p2]=11;
		b[k]=p1+3;
		c[k]=p2;
	}// ��
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
	}// �y
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
	}//��
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
	}//��
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
	}//��
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
	}//��
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
	}// ����
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
	}// ����
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
	}// ����
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
	}// ����
	


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
	}//��
	if(*p==1)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//��
	if(*p==2)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//��
	if(*p==3)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
	}//��
	if(*p==4)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2]=0;
		a[p1+3][p2]=0;
	}// ��
	if(*p==5)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1][p2+3]=0;
	}// �y
	if(*p==6)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2]=0;
		a[p1+3][p2]=0;
	}// ��
	if(*p==7)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1][p2+3]=0;
	}// �y
	if(*p==8)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1+1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2+2]=0;
	}//��
	if(*p==9)
	{
		k=0;
		a[p1][p2]=0;
		a[p1+1][p2]=0;
		a[p1+1][p2+1]=0;
		a[p1+2][p2]=0;
	}//��
	if(*p==10)
	{
		k=0;
		a[p1][p2]=0;
		a[p1][p2+1]=0;
		a[p1][p2+2]=0;
		a[p1+1][p2+1]=0;	
	}//��
	if(*p==11)
	{
		k=0;
		a[p1][p2+1]=0;
		a[p1+1][p2+1]=0;
		a[p1+1][p2]=0;
		a[p1+2][p2+1]=0;
	}//��
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
	}// ����
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
	}// ����
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
	}// ����
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
	}// ����

}//fangkuai2 end;

int stop(int a[M][N],int b[W],int c[W],int *m,int *n,int *p,int p3,int p4,int *x1)
{
	int i;
	for(i=0;b[i]!='\0';i++)//�ж��Ƿ����
	{
//	    printf("%d,%d,%d\n",b[i],c[i],a[b[i]+1][c[i]]);//������
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
