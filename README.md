# PSO
    program it in C++. using the original method proposed by James Kennedy &amp; Russell Eberhart(1995)

    AS FOLLOWING:
    [x*] = PSO()
    P = Particle_Initialization();
    For i=1 to it_max
    For each particle p in P do
    fp = f(p);
    If fp is better than f(pBest)
    pBest = p;
    end
    end
    gBest = best p in P;
    For each particle p in P do
    v = v + c1*rand*(pBest – p) + c2*rand*(gBest – p);
    p = p + v;
    end
    end
