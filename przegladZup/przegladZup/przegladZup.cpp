// przegladZup.cpp : Defines the entry point for the console application.
//
#ifndef __CB
#include "stdafx.h"
#else
#define _tmain main
//#define _TCHAR char
#endif
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

using namespace std;
#include "Zad.h"


#define PRINT if(0)

#include "Solvers.h"


extern list<Zad> readFromFile(const char *filename);

#include <memory>
#include <cstring>

int main(int argc, char* argv[]) {
    string s;
    ofstream("testWorkingDir.txt");
    system("cd");
    std::cout<<endl<<"podaj numer pliku"<<endl;
    stringstream ss(stringstream::in | stringstream::out);

    if(argc==1) {
        std::cin>>s;
        //else
        //s="6";
        ss<<
        //".\\"<<
        s<<".txt";
    } else {
        ss<<argv[1];
    }
    cout<<"wczytywanie pwd="<<string(argv[0])<<": "<<ss.str()<<endl;
    //const char *fname=ss.str().c_str();
    list<Zad> jobs=readFromFile(ss.str().c_str());
    //Solver sol=SolverRemoveActualIfWorseThan(jobs);
    //SolverRemoveActualIfWorseThan sol(jobs);
    //sol=Solver(jobs);
    ofstream fle("outputs.txt", fstream::app|fstream::out);
    auto_ptr<Solver> sol;
    if(argc>=3 && strcmp(argv[2],"swap")==0) sol=auto_ptr<Solver>(new SolverRemoveIfSwappingMakesBetter(jobs));
    else if(argc>=3 && strcmp(argv[2],"worse")==0) sol=auto_ptr<Solver>(new SolverRemoveActualIfWorseThan(jobs));
    else if(argc>=3 && strcmp(argv[2],"LB")==0) sol=auto_ptr<Solver>(new SolverLBcriterion(jobs));
    else if(argc>2 && strcmp(argv[2],"all")==0)
        sol=auto_ptr<Solver>(new Solver(jobs));
    else {
        SolverLBcriterion(jobs).solveInterface().saveRaportToFile(fle,ss.str().c_str()).printWinningSequence();
        fle.close();
        return 1;
    }
    sol->solveInterface().saveRaportToFile(fle,ss.str().c_str()).printWinningSequence();
    fle.close();

    //glut
    //int n;cin>>n;

    return 0;
}

