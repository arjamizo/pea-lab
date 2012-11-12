
#include <fstream>
#include <list>
#include <sstream>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <string>
#include <iterator>
#include <vector>
#include "Zad.h"

#include "Solver.h"

#ifndef PRINT
#define PRINT if(0)
#endif



//calculates the total cost of given jobs sequence
size_t extraCostCalc(const vector<Zad> &ord) {
    size_t time=0;
    size_t extraCost=0;
    //Zad tab[ord.size()];
    //std::copy(ord.begin(), ord.end(), std::ostream_iterator<Zad>(cout, "\n"));
    for(vector<Zad>::const_iterator it=ord.begin(); it!=ord.end(); it++) {
        time+=it->p;
        extraCost+=it->costIfEndsAt(time+it->p);
    }
    return extraCost;
}

class SolverRemoveActualIfWorseThan:public Solver {
public:
    const char* getAlgoName() {
        return "CutIfActualWorseThanBestTillNow";
    }
    SolverRemoveActualIfWorseThan(const list<Zad> &jobs, const list<Zad> &ordered=list<Zad>()):Solver(jobs, ordered) {
    }
    virtual bool shouldEliminate(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
        if(extraCost>Solver::bestTillNow) return true;
        return false;
    }
    virtual size_t enterFunction(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
        //Solver::enterFunction(unord, ord, time, extraCost, nthExec);
        //cout<<".";
        return 0;
    }
};

class SolverRemoveIfSwappingMakesBetter:public Solver {
public:
    const char* getAlgoName() {
        return "CutIfSwappingMakesBetter";
    }
    SolverRemoveIfSwappingMakesBetter(const list<Zad> &jobs, const list<Zad> &ordered=list<Zad>()):Solver(jobs, ordered) {
    }
    virtual bool shouldEliminate(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
        vector<Zad> jobs(ord.begin(),ord.end());
        vector<Zad> origin(jobs);
        for(size_t i=jobs.size()-1; i>=1; --i) {
            std::swap(jobs[i],jobs[i-1]);
            //PRINT cout<<"amhere, calculated: "<<extraCostCalc(jobs)<<" and best is "<<bestTillNow<<" len="<<bestSol.size()<<"\t"<<list<Zad>(jobs.begin(),jobs.end());
            if(extraCostCalc(jobs)<extraCostCalc(vector<Zad>(origin.begin(),origin.begin()+jobs.size())) && bestSol.size()) {
                PRINT cout<<"but: skipping this because better in another branch"<<endl;
                return true;
            }
            PRINT cout<<endl;
        }
        return false;
    }
    virtual size_t enterFunction(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
        //cout<<".";
        return 0;
    }
};

class SolverLBcriterion:public Solver {
public:
    const char* getAlgoName() {
        return "CutIfGreaterThanCriterionLB";
    }
    int bestCrit;
    SolverLBcriterion(const list<Zad> &jobs, const list<Zad> &ordered=list<Zad>()):Solver(jobs, ordered) {
        bestCrit=-1;
    }
    int calcCriteriumLB(list<Zad> &unord, list<Zad> &ord) {

        vector<Zad> remaining(unord.begin(),unord.end());
        /*Zad rem[60];
        copy(remaining.begin(),remaining.end(), rem);
        Zad ordere[60];
        copy(ord.begin(),ord.end(), ordere);*/
        int sum=0;
        int k=0;
        //if(ord.size()!=0)
        {
            sum+=extraCostCalc(vector<Zad>(ord.begin(),ord.end()));
            {
                for(list<Zad>::iterator it=ord.begin(); it!=ord.end(); ++it) {
                    k+=it->p;
                }
            }
        }
        //if(remaining.size()!=0)
        for(size_t i=0; i<remaining.size(); ++i) {
            Zad &a=remaining[i];
            sum+=a.w*(a.costIfEndsAt(k)+a.p);
        }
        return sum;
    }
    virtual bool shouldEliminate(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
        int criterium;
        criterium=calcCriteriumLB(unord, ord);
        //cout<<"bestcrit="<<bestCrit<<" curr crit="<<criterium<<" list: "<<ord<<" unord: "<<unord<<endl;
        int orderedLength=ord.size();
        int unorderedLength=unord.size();
        if(ord.size()==0) return false;
        if (bestCrit>=0 && criterium>bestCrit) return true;
        vector<Zad> zadania(ord.begin(),ord.end());
        Zad tab[zadania.size()];
        copy(zadania.begin(),zadania.end(), tab);
        if((extraCost<Solver::bestTillNow || criterium<bestCrit) && unord.size()==0) {
            bestCrit=criterium;
        }
        return false;
    }
    virtual size_t enterFunction(list<Zad> &unord, list<Zad> &ord, size_t time, size_t extraCost, size_t nthExec) {
        //cout<<".";
        return 0;
    }
};
