#include "SimulationViewer.h"
#include "Solver.h"
#include "Vertex.h"
#include <iostream>
#include <QThread>
int SimulationViewer::cnt=0;
SimulationViewer::SimulationViewer() {
    cnt++;
}
SimulationViewer::~SimulationViewer() {
}
#ifdef _QT
using namespace std;

SimulationViewer *ref[10];
Solver *refs[10];

SimulationViewer *findBySolver(Solver *s) {
    int i=&*std::find(refs,refs+10,s)-refs;
    return ref[i];
}

void callback(int x, int y, Solver *solver, int xm, int xM, int parentX) {
    cout<<x<<" "<<y<<endl;
    SimulationViewer *sv=findBySolver(solver);
    int maxDepth=(solver->N);
    int maxLeaves=1;
    y+=1;
    for(int i=1;i<=maxDepth;++i) maxLeaves*=i;

    int maxWidth=maxLeaves*22;
    int maxLeavesOnCurrentLevel=1;
    for(int i=y-1;i>1;--i) maxLeavesOnCurrentLevel*=i;
    int newx=maxWidth*(x+1)/maxLeavesOnCurrentLevel-maxWidth/2;
    cout<<maxWidth<<"*"<<(x+1)<<"*"<<maxLeavesOnCurrentLevel<<"/"<<maxLeaves<<endl;
    int xThis=(xm+xM)/2;
    sv->widget->add(new QGraphicsLineItem(parentX,15*(y-1+sv->modY),xThis,(y+sv->modY)*15));
    sv->widget->add(new Vertex(xThis, 15*(y+sv->modY)));
    sv->widget->viewport()->update();
    //sv->wait((maxDepth-y)*120/maxDepth);
    //sv->wait(10000000UL);
    sv->msleep(33);
    //cin.get();
}
#endif
#include <QGraphicsLineItem>
SimulationViewer::SimulationViewer(Solver *s, GraphWidget *widget, int modY=0)
    :sol(s),widget(widget),modY(modY) {
    //sol=s;
    i=-100;
    cout<<".."<<cnt<<endl;
    ref[cnt]=this;
    refs[cnt]=s;
    cnt++;
    sol->setFun(callback);
    //widget->add(new QGraphicsLineItem(0,0,100,100));
};

void SimulationViewer::run() {
    sol->solveInterface();
    if(0)while(true) {
            //QMutexLocker locker(&mutex);
            //for(int i=-100; i<100; ++i)
            //widget->add(new Vertex(11*i,0));
            //widget->viewport()->update();
            //i++;
            //cout<<i<<endl;
            widget->timerEvent(NULL);
            //widget->update=true;
        }
};
