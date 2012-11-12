#ifndef _SOLVER
#define _SOLVER
#include <list>
#include "Zad.h"
class Solver;
typedef void (*cbPtr)(int,int,Solver*s,int,int,int);
class Solver {
    protected:
    public:
    list<Zad> unordered;
    list<Zad> ordered;
    size_t bestTillNow;
    int N;
    size_t visitedVerticles;
    size_t visitedChecked;
    list<Zad> bestSol;
	size_t sequenceLen;
	double time;
//#ifdef _QT
	//void (SimulationViewer::*fun)(int,int);
//#else
	cbPtr fun;
//#endif
    Solver(const list<Zad> &jobs, const list<Zad> &ordered=list<Zad>());
    virtual bool shouldEliminate(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec);
    virtual size_t enterFunction(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec);
    size_t solve(list<Zad> unord, list<Zad> ord, size_t time, size_t extraCost, size_t nthExec, int x, int y, int parentX);
    virtual const char* getAlgoName();
	Solver& solveInterface();
	Solver& printWinningSequence();
	Solver& saveRaportToFile(ostream &cout, const char thisTestName[]);
	void setFun(cbPtr);
};
#endif
