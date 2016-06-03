#include<Ctime>
#include<Cstdlib>
#include<iostream>
#include<fstream>
#include<iomanip>
#include"Swarm.h"
using namespace std;

void random(int start,int end,int n,double *p);
void copyarr(double *arr1,double *arr2,int n);
void constraintvalue(double *p,double lower,double upper);

//define it as needed,this is just an EXAMPLE
double Swarm::fitness(double *p)
{
	return p[0]*p[0]+p[1]*p[1];
}

Swarm::Swarm(int d,int n,int max):D(d),N(n),MAX_actionNUM(max)
{
	srand((unsigned)time(NULL));
	cout<<"please set initial number of [c1 c2] sequentially:\n";
	cin>>c1>>c2;
	//-----initialize every dimension's coordinate of all particles in swarm---
	cout<<"please set lower bounds of every dimension's coordinate sequentially:\n";
	bound_location[0]=new double[D];
	for(int i=0;i<D;i++)
		cin>>bound_location[0][i];
	cout<<"please set upper bounds of every dimension's coordinate sequentially:\n";
	bound_location[1]=new double[D];
	for(i=0;i<D;i++)
		cin>>bound_location[1][i];
	//-----initialize every dimension's velocity of all particles in swarm---
	cout<<"please set lower bounds of every dimension's velocity sequentially:\n";
	bound_velocity[0]=new double[D];
	for(i=0;i<D;i++)
		cin>>bound_velocity[0][i];
	cout<<"please set upper bounds of every dimension's velocity sequentially:\n";
	bound_velocity[1]=new double[D];
	for(i=0;i<D;i++)
		cin>>bound_velocity[1][i];
	//------allocate storage----------------------------------
	loca_swarm=new double *[N];
	for(i=0;i<N;i++)
		loca_swarm[i]=new double[D];
	//---
	pbest_loca_swarm=new double *[N];
	for(i=0;i<N;i++)
		pbest_loca_swarm[i]=new double[D+1];//NOTE:pbest_loca_swarm[i][0]
	//---
	vel_swarm=new double *[N];
	for(i=0;i<N;i++)
		vel_swarm[i]=new double[D];
	//---
	gbest=new double[D+1];
	int gbestno=searchBest();
	copyarr(gbest,pbest_loca_swarm[gbestno],D+1);	
	//---initialize values
	void random(int start,int end,int n,double *p);
	double *temp=new double[N];
	for(int j=0;j<D;j++)
	{
		//initialize loca_swarm[][]
		random(bound_location[0][j],bound_location[1][j],N,temp);
		for(i=0;i<N;i++)
			loca_swarm[i][j]=temp[j];
		//initialize vel_swarm[][]
		random(bound_velocity[0][j],bound_velocity[1][j],N,temp);
		for(i=0;i<N;i++)
			vel_swarm[i][j]=temp[j];	
	}
	//initialize pbest_loca_swarm[][]
	for(i=0;i<N;i++)
	{
		for(j=0;j<D;j++)
			pbest_loca_swarm[i][j]=loca_swarm[i][j];
		pbest_loca_swarm[i][D]=fitness(loca_swarm[i]);//
	}	
}
int Swarm::searchBest()
{
	double temp=pbest_loca_swarm[0][D];
	int bestno=0;
	for(int i=0;i<N;i++)
		if(pbest_loca_swarm[i][D]>temp)
		{
			temp=pbest_loca_swarm[i][D];
			bestno=i;		
		}
	return bestno;
}
void Swarm::update_loca()
{
	for(int i=0;i<N;i++)
	  for(int j=0;j<D;j++)
		{
			loca_swarm[i][j]=loca_swarm[i][j]+vel_swarm[i][j];
			constraintvalue(&loca_swarm[i][j],bound_location[0][j],bound_location[1][j]);		
		}
}

void Swarm::update_vel()
{
	double r1,r2;
	int temp;
	for(int i=0;i<N;i++)
	  for(int j=0;j<D;j++)
		{
		    temp=rand()%2;
			r1=temp/(temp+1.0);
			temp=rand()%2;
			r2=temp/(temp+1.0);
			vel_swarm[i][j]=vel_swarm[i][j]+c1*r1*(pbest_loca_swarm[i][j]-loca_swarm[i][j])+c2*r2*(gbest[j]-loca_swarm[i][j]);
			constraintvalue(&vel_swarm[i][j],bound_velocity[0][j],bound_velocity[1][j]);		
		}
}

void Swarm::moveon()
{
	int m=1;
	int i;
	int gbestno;
	double temp;
	while(m++<MAX_actionNUM)
	{		
		//
		ofstream saved("data.txt",ios::app);
		int t1,t2;
		saved<<"loca_swarm:\n";
		for(t1=0;t1<N;t1++)
		{
			for(t2=0;t2<D;t2++)
				saved<<loca_swarm[t1][t2]<<"     ";
			saved<<endl;		
		}
		saved<<"loca_swarm:\n";
		for(t1=0;t1<N;t1++)
		{
			for(t2=0;t2<=D;t2++)
				saved<<pbest_loca_swarm[t1][t2]<<"     ";
			saved<<endl;		
		}
		saved<<"gbest:\n";
		for(t2=0;t2<=D;t2++)
			saved<<gbest[t2]<<"     ";
		saved<<endl;
		saved<<"vel_swarm:\n";
		for(t1=0;t1<N;t1++)
		{
			for(t2=0;t2<D;t2++)
				saved<<vel_swarm[t1][t2]<<"     ";
			saved<<endl;		
		}
		saved.close();
		//-----------------------------------------------
		update_loca();
		for(i=0;i<N;i++)
		{
			temp=fitness(loca_swarm[i]);
			if(temp>pbest_loca_swarm[i][D])
			{
				copyarr(pbest_loca_swarm[i],loca_swarm[i],D);
				pbest_loca_swarm[i][D]=temp;			
			}		
		}
		gbestno=searchBest();
		copyarr(gbest,pbest_loca_swarm[gbestno],D+1);
		update_vel();
	}
}

Swarm::~Swarm()
{
	cout<<"THE BEST COORDINATES:\n";
	cout.precision(3);
	for(int i=0;i<D;i++)
		cout<<setw(5)<<gbest[i];
	cout<<endl;
	cout<<"THE OBJECTIVE FUNCTION VALUE CORRESPONDINGLY:\n";
	cout<<gbest[D]<<endl;

	for(i=0;i<2;i++)
	{
		delete[] bound_location[i];
		delete[] bound_velocity[i];
	}
	//----------------------------------------------------------------------
	for(i=0;i<N;i++)
		delete[] loca_swarm[i];
	delete[] loca_swarm;

	for(i=0;i<N;i++)
		delete[] pbest_loca_swarm[i];
	delete[] pbest_loca_swarm;
	//----------------------------------------------------------------------
	for(i=0;i<N;i++)
		delete[] vel_swarm[i];
	delete[] vel_swarm;
}
