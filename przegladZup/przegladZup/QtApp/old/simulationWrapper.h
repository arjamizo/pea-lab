#include <QtCore/QThread>
#include <QtCore/QMutex>
extern QMutex mutex;
#include <QtCore/QMutexLocker>
#include <QtCore/QMutexLocker>
#include "vertex.h"
#include "Solver.h"
#include "graphicView.h_moc.h"
#include <iostream>

 //extern   void callback(int x, int y);
class SimulationWrapper: public QThread {
    Q_OBJECT
public:
    Solver *sol;
    GraphWidget *widget;
    int i;
    SimulationWrapper(Solver *s, GraphWidget *widget);
    void run();
    //void callback(int x, int y);
};
/*
    void SimulationWrapper::callback(int x, int y) {
    {
        cout<<x<<" "<<y<<endl;
    };*/
    SimulationWrapper::SimulationWrapper(Solver *AAAA, GraphWidget *widget):widget(widget) {
        //sol=s;
        i=-100;
        //sol->setFun(callback);
    };
    void SimulationWrapper::run() {
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

