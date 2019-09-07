#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n1;
double w[11];

double S(double x)
{
	return 1/(1+exp(-x));
}

double d_S(double x)
{
	return x*(1-x);
}

void test()
{
	int i;
	double s,I;
	printf("\nEnter test values\n");
	s=0;
	for (i = 1; i <= n1; i++)
	{
		printf("enter x[%d] : ",i);
		scanf("%lf",&I);
		s=s+(I*w[i]);
	}
	printf("Output : %lf",S(s));
}

void print_weights()
{
	int i;
	for (i = 1; i <= n1; i++)
	{
		printf("w[%d]=%lf",i,w[i]);
	}
}


int main()
{
	int n,i,j,k;
	double I[101][11], O[11], l[101],s,err,alpha=1;
	/*srand(time(NULL));*/
	printf("Enter no of neurons in input layer : ");
	scanf("%d", &n);
	printf("Enter no of enteries : ");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		printf("\nentry %d\n", i);
		for (j = 0; j <= n1; j++)
		{
			printf("enter x[%d] : ",j);
			scanf("%lf", &I[i][j]);
		}
		printf("enter y : ");
		scanf("%lf", &O[i]);
	}
	for (i = 1; i <= n1; ++i)
		w[i]=2.0*rand()/RAND_MAX-1;
	for (i = 1;; i++)
	{
		err=0;
		for (j = 1; j <= n; j++)
		{
			s=0;
			for (k = 1; k <= n1; k++)
			{
				s=s+(I[j][k]*w[k]);
			}
			l[j]=S(s);
			err=err+fabs(l[j]-O[j]);
			l[j]=(l[j]-O[j])*(d_S(l[j]));
		}
		for (j = 1; j <= n1; j++)
		{
			s=0;
			for (k = 1; k <= n; k++)
			{
				s=s+(I[k][j]*l[k]);
			}
			w[j]=w[j]-(alpha*s);
		}
		if (i==1000000)
		{
			i=0;
			printf("\nerror : %lf", err);
		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			s=alpha*10;
			if (fabs(s)<11)
			{
				alpha=s;
			}
			Sleep(100);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			s=alpha/10;
			if (fabs(s)>=pow(10,-15))
			{
				alpha=s;
			}
			Sleep(100);
		}
	}
	printf("\n\n");
	i=0;
	while(i!=6)
	{
		printf("1) Test\n2) See Weight\n3) Continue Training\n4) Retrain\n5) Check learning rate\n6) Exit\n");
		printf("enter choice : ");
		scanf("%d", &i);
		if (GetAsyncKeyState(VK_UP))
		{
			s=alpha*10;
			if (fabs(s)<11)
			{
				alpha=s;
			}
			Sleep(100);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			s=alpha/10;
			if (fabs(s)>=pow(10,-15))
			{
				alpha=s;
			}
			Sleep(100);
		}
	}
	getch();
	return 0;
}