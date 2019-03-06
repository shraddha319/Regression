#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Linear regression using Ordinary Least Squares(OLS) method 

float date[22],close[22];

void main()
{
	char record[200];
	int i=0,j,n;
	float b0, b1, ex=0, ey=0, ssxx=0, ssyy=0, spxy=0,cov_xy, varx, predict[22], error=0,residue[22],max=0,min=999 ;
	float p,q;

	//data file contains comma separated values of the form (index,close)
	FILE * fp = fopen("data.txt","r");
	if(fp==NULL)
	{
		printf("Error!\n");
		exit(0);
	}

	//Reading index and close values into date and close arrays
	while(fgets(record,200,fp)!=NULL)
	{
		date[i] = atof(strtok(record,","));
		close[i] = atof(strtok(NULL,","));
		i++;
	}
	n = i-1; //Number of records

	//Mean of index and close values
	for(i=0;i<n;i++)
	{
		ex += date[i];
		ey += close[i];
	}
	ex /= n;
	ey /= n;

	//ssxx: sum of squares of x, ssyy:sum of squares of y, spxy:sum of product of x and y
	for(i=0;i<n;i++)
	{
		ssxx += (date[i]-ex)*(date[i]-ex);
		ssyy += (close[i]-ey)*(close[i]-ey);
		spxy += (date[i]-ex)*(close[i]-ey);
	}

	//cov_xy:Covariance of x and y, varx: Variance of x
	cov_xy = spxy/(n-1);
	varx = ssxx/(n-1);

	//Pamareters: b0 and b1
	//b0: y intercept, b1: slope of the linear equation to be predicted 
	b1 = cov_xy/varx;
	b0 = ey - b1*ex;

	for(i=0;i<n;i++)
	{
		predict[i] = b1*date[i] + b0;	//Values predicted by predicted equation
		residue[i] = abs(predict[i]-close[i]); //Absolute error between predicted and observed values
		min = (min>residue[i]? residue[i]:min);
		max = (max<residue[i]? residue[i]:max);
	}

	//Normalized error
	for(i=0;i<n;i++)
		error += (residue[i]-min)/(max-min);	
	error /= n;
	
	
	for(i=0;i<n;i++)
	{
		printf("%0.3f\t%0.3f\t%0.3f\n",date[i],close[i],predict[i]);
	} 
	printf("Parameters: slope=%0.3f, intercept=%0.3f\nError=%f\n",b1,b0,error);	
}