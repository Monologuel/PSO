#include<Ctime>
#include<Cstdlib>

//generate n double numbers between start and end, and store them in p
void random(int start,int end,int n,double *p)
{
	//srand((unsigned)time(NULL));//set seed
	int temp;
	double dt;
	 for(int cn=0;cn<n;cn++)
	 {
	 temp=start+rand()%(end-start+1);//note:rand() return a value belonging [0,RAND_MAX]。
	 dt=temp*(temp/(temp+1.0));
	 if(dt<start)
		 dt=start;
	 if(dt>end)
		 dt=end;
	 p[cn]=dt;
	 }
}

//
void copyarr(double *arr1,double *arr2,int n)
{
	for(int i=0;i<n;i++)
		arr1[i]=arr2[i];
}
//
void constraintvalue(double *p,double lower,double upper)
{
	if(*p<lower)
	{
		*p=lower;
		return;
	}
	if(*p>upper)
		*p=upper;
}
