#include "Solver.h"
#include <iterator>

#include <windows.h>
#ifdef __WIN32
class Timer {
	 __int64 t1,t2,freq;
	 public:
    Timer() {
        QueryPerformanceCounter( (LARGE_INTEGER*)&t1 );
    }
    double stop() {
        QueryPerformanceCounter( (LARGE_INTEGER*)&t2 );
        QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );
        double time = (double)( t2 - t1 ) / freq;
        return time;
    }
};
#endif


#ifdef _QT
#include "SimulationViewer.h"
#endif

ostream &operator<<(ostream &cout, const list<Zad> &l) {
    for(list<Zad>::const_iterator it=l.begin(); it!=l.end(); ++it) {
        cout<<char('A'+it->nr)<<" ";
    }
    //cout<<"\n";
    return cout;
}

    Solver::Solver(const list<Zad> &jobs, const list<Zad> &ordered): unordered(jobs.begin(), jobs.end()), ordered(ordered) {
        //time=0;
        //cost=0;
        //bestTillNow=std::numeric_limits<size_t>().max();
        bestTillNow=100000000ULL;
        visitedVerticles=0;
        visitedChecked=0;
        fun=0;
        N=unordered.size();
    }
#ifdef _QT
    void Solver::setFun(cbPtr f)
    {
	//void (*fun)(int,int);
        fun=f;
        //fun(0,0);
    }
#else
    void Solver::setFun(cbPtr f)
    {
	//void (*fun)(int,int);
        fun=f;
        //fun(0,0);
    }
#endif
    bool Solver::shouldEliminate(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
        return false;
    }
    //this function can be overwritten to handle GUI drawing
    size_t Solver::enterFunction(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
			//cout<<".";
            return 0;
			cout<<"wywolywanie funkcji z argumentami: nieuporzadkowana: \n";
			std::copy(unord.begin(), unord.end(), ostream_iterator<Zad>(cout));
			cout<<"\n uporzadkowana: \n";
			std::copy(ord.begin(), ord.end(), ostream_iterator<Zad>(cout));
			return 0;
    }
    size_t factorial(int n) {
        size_t fact=1;
        for(int i=2; i<=n; ++i) fact*=i;
        return fact;
    }
    size_t Solver::solve(list<Zad> unord, list<Zad> ord, size_t time, size_t extraCost, size_t nthExec, int xMin=0, int xMax=2200, int parentX=1100) {
        //while(tick());
        enterFunction(unord, ord, time, extraCost, nthExec);
        int xThis=(xMin+xMax)/2;
        ++visitedVerticles;
        if(unord.size()==0) {
			//cout<<"Congratulations! Solved in "<<time<<" time units and extra costs (delay costs) of "<<extraCost<<" time units."<<endl;
			if(extraCost<bestTillNow) {
				bestTillNow=extraCost;
				bestSol=list<Zad>(ord.begin(), ord.end());
			}
			return bestTillNow;
		} else { //tozsame z if(unord.size()!=0)
			int ile=unord.size();
			for(int i=0; i<ile; ++i) {
				/*
				Zejœcie stopieñ ni¿ej to zdjêcie elementu z POCZ¥TKU listy nieuporz¹dkowanej i
				dodanie na KONIEC listy uporz¹dkowanej. (czyli de facto dodanie kolejnego
				mo¿liwego elementu na koniec permutacji).
				*/
				Zad z=unord.front();
				unord.pop_front();
				ord.push_back(z);
				int newC=extraCost+z.costIfEndsAt(time+z.p);
				//newC=std::accumulate(ord);
				int delta=(xMax-xMin)/ile;
                int xmin=xMin+i*delta;
                visitedChecked++;
                if(fun)
                    fun(nthExec*ile+i, ord.size(), this, xmin-delta*ile/2, xmin+delta-delta*ile/2, xThis);
				if(!shouldEliminate(unord, ord, time+z.p, newC, i)) {
				    solve(unord, ord, time+z.p, newC, i, xmin, xmin+delta, xThis);
				}
				//Wejœcie stopieñ wy¿ej to zdjêcie ostatniego elementu z KOÑCA listy uporz¹dkowanej i dodanie do na KONIEC listy nieuporz¹dkowanej.
				Zad w=ord.back();
				ord.pop_back();
				unord.push_back(w);
			}
		}
		return bestTillNow;
    }
    const char* Solver::getAlgoName() {
        return "AllCheck";
    }
	Solver& Solver::solveInterface() {
		cout<<"wywolanie interafece'u"<<endl;
		Timer timer;

        //Zad rem[20];
        //copy(unordered.begin(),unordered.end(), rem);
        //Zad ordere[20];
        //copy(ordered.begin(),ordered.end(), ordere);

		solve(unordered, ordered, 0, 0, 0);
        cout<<"trawlo: "<<(time=timer.stop())<<"s\n";
		return *this;
	}
	Solver& Solver::printWinningSequence() {
		cout<<"Pierwsze miejsce, z wynikiem "<<bestTillNow<<", odwiedzajac "<<visitedVerticles<<" wierzcholkow (wywolania funkcji)/"<<visitedChecked<<" (sprawdzone wierzchołki), wedruje dla sekwencji: "<<endl;
		//std::copy(bestSol.begin(), bestSol.end(), ostream_iterator<Zad>(cout));
		cout<<bestSol<<endl;
		cout<<"KONIEC DZIALANIA ALGORYTMU "<<getAlgoName()<<"\n";
		return *this;
	}
	Solver& Solver::saveRaportToFile(ostream &cOut, const char thisTestName[]) {
	    #ifdef _DEBUG
	    ostream &cout=::cout;
	    #else
	    ostream &cout=cOut;
	    #endif
		cout<<thisTestName<<"\t"<<time<<"\t"<<visitedVerticles<<"\t"<<visitedChecked<<"\t"<<bestSol.size()<<"\t"<<bestTillNow<<"\t"<<getAlgoName()<<"\t"<<bestSol<<endl;
		return *this;
	}
