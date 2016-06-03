#include<iostream>
#include"Swarm.h"
using namespace std;

//NOTE:
//creat an object according to the construct function: 
//Swarm::Swarm(int d,int n,int max):D(d),N(n),MAX_actionNUM(max)
//as the definition in class.they are 
//"dimension number of space","particle number in the swarm" and "total times of particle move"
//AND
//there should be a txt file "data.txt" in current path
int main()
{
	Swarm s(2,20,50);
	s.moveon();
	return 0;
}
