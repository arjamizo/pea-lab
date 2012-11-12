#ifndef SIMULATIONVIEWER_H
#define SIMULATIONVIEWER_H

#include "../Solver.h"
#include <QThread>
#include "GraphWidget.h"


class SimulationViewer : public QThread
{
    Q_OBJECT
    public:
    Solver *sol;
    static int cnt;
    SimulationViewer();
    ~SimulationViewer();
    GraphWidget *widget;
    int modY;
    int i;
    SimulationViewer(Solver *s, GraphWidget *widget, int modY);
    void run();
    friend void callback(int x, int y, Solver *solver, int xm, int xM, int parentX);
};

#endif // SIMULATIONVIEWER_H
