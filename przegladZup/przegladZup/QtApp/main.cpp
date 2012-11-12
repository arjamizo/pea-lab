#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QtGui/QApplication>
#include <QtGui/QTextEdit>
#include <QMainWindow>
#include <utility>
#include <list>
#include <QtCore/QMutexLocker>
#include <QtCore/QRunnable>
#include <QtCore/QThreadPool>
#include <QtCore/QMutex>
//#include "GraphWidget.hmoc.h"
#include "SimulationViewer.h"
#include "Zad.h"
#include "Solvers.h"

QMutex mutex;
QMutexLocker locker(&mutex);
extern list<Zad> readFromFile(const char *filename);
int main(int argc, char **argv)
 {
     QApplication app(argc, argv);
     QMainWindow mainWindow;
     GraphWidget *widget = new GraphWidget(32);
     mainWindow.setCentralWidget(widget);
     mainWindow.show();
     list<Zad> jobs;
     if(argc==2)
        jobs=readFromFile(argv[1]);
    else {
        cout<<"use: "<<argv[0]<<" filename of text file containig tasks in each line, 3 integers meaning sequentially: price, deadline, weight\n";
        cout<<"what each graph (counting from top) means: first - full search\n\tsecond - remove if extra cos higher than best one till now\n\tthird - try swapping last element moving it to the left\n\tfourth - calculate criterium after each reached solution and do not let worse than the best criterium value are checked\n";
        cout<<"loading ..\\5.txt as example";
        FILE *fp = fopen("..\\5.txt","r");
        if(fp) {
            fclose(fp);
            jobs=readFromFile("..\\5.txt");
        } else {
            mainWindow.setWindowTitle("example file ..\\5.txt probably does not exists.");
        }
    }
     int dy=jobs.size()+1;
     SimulationViewer method0(new Solver(jobs), widget, -dy);
     method0.start();
     SimulationViewer method1(new SolverLBcriterion(jobs), widget, 0);
     method1.start();
     SimulationViewer method2(new SolverRemoveActualIfWorseThan(jobs), widget, dy);
     method2.start();
     SimulationViewer method3(new SolverRemoveIfSwappingMakesBetter(jobs), widget, 2*dy);
     method3.start();
	 /*
     //QTextEdit text;
     //text.show();
     //QMainWindow mainWindow;;

     //QThreadPool *threadPool = QThreadPool::globalInstance();
     //SimulationWrapper method1(new SolverRemoveIfSwappingMakesBetter(jobs));
     //SimulationWrapper method2(new SolverRemoveActualIfWorseThan(jobs));
     //SimulationWrapper method3(new SolverLBcriterion(jobs));
     list<pair<int,int> > exchange;
     //locker.
     GraphWidget *widget = new GraphWidget(exchange);
     mainWindow.setCentralWidget(widget);
     list<Zad> jobs=readFromFile("5.txt");
     SimulationWrapper method0(new Solver(jobs), widget);
     //

     //threadPool->start(&wt);
     //threadPool->start(&method0);
     //threadPool->start(&method1);
     //threadPool->start(&method2);
     //threadPool->start(&method3);*/
     return app.exec();
 }
