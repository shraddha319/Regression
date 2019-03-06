#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Linear regression using Gradient Descent algorithm

float date[22],close[22];

float derv_0(float b0,float b1,int n)
{
	//Returns derivative of cost function with respect to b0
	int i;
	float derv=0;
	for(i=0;i<n;i++)
		derv += (close[i]-b1*date[i]-b0)*-1;
	return derv/n;
}

float derv_1(float b0, float b1, int n)
{
	//Returns derivative of cost function with respect to b1
	int i;
	float derv=0;
	for(i=0;i<n;i++)
		derv += ((close[i]-b1*date[i]-b0)*date[i])*-1;
	return derv/n;
}

void main()
{
	char record[200];
	int i=0,j,n, epoch=0;
	double b0,b1,temp0,temp1,r=0.014, precision = 0.1, init0=0, init1=0;
	double x[5000],y[5000];
	float p,q;

	//File contains data as comma separated values: (index,close)
	FILE * fp = fopen("data.txt","r");
	if(fp==NULL)
	{
		printf("Error!\n");
		exit(0);
	}
	while(fgets(record,200,fp)!=NULL)
	{
		date[i] = atof(strtok(record,","));
		close[i] = atof(strtok(NULL,","));
		i++;
	}
	n = i-1; //Number of records

	//Inital parameter values
	temp0 = init0;
	temp1 = init1;
	do
	{
		b0 = temp0;
		b1 = temp1;
		temp0 = b0 - r*derv_0(b0,b1,n);
		x[epoch] = temp0;
		temp1 = b1 - r*derv_1(b0,b1,n);
		y[epoch] = temp1;
		epoch++;
	}while(epoch<5000);//abs(b0-temp0)>precision || abs(b1-temp0)>precision);
	
	for(i=0;i<epoch;i++)
	{
		printf("epoch:%d\t%f\t%f\n",i+1,x[i],y[i]);
	}
	printf("Parameters:%f\t%f\nNumber of iterations=%d",b0,b1,epoch);
}