class Swarm{
public:
	Swarm(int d,int n,int max);//construtor funtion
	void update_loca();//update the every dimension's coordinate of all particles in swarm
	void update_vel();//update the every dimension's velocity of all particles in swarm
	double fitness(double*);//Objective function
	void moveon();
	int searchBest();
	~Swarm();//desconstructor function
	
private:
	const int D;//dimension number of space
	const int N;//particle number in the swarm
	const int MAX_actionNUM;//total times of particle move
	double c1;//selfcognition coefficient,generally 0.14995,or just 2
	double c2;//sociocognition coefficient,generally 0.14995,or just 2//////Usually c1+c2=4(empirically chosen value)
	double *bound_location[2];//[0][]means lower bound,[1][] means upper bound
	double *bound_velocity[2];//[0][]means lower bound,[1][] means upper bound; generally [-1,1]
	double **loca_swarm;//every dimension's coordinate of all particles in swarm
	double **pbest_loca_swarm;//every dimension's coordinate of all particles in swarm
	double **vel_swarm;//every dimension's velocity of all particles in swarm
	double *gbest;//global best
};
