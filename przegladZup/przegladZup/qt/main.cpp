#include <QApplication>
#include <QMainWindow>
int main(int argc, char **argv)
 {
     QApplication app(argc, argv);
     QMainWindow mainWindow;
     mainWindow.show();
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
     //SimulationWrapper method0(0, widget);
     method0.start();

     //threadPool->start(&wt);
     //threadPool->start(&method0);
     //threadPool->start(&method1);
     //threadPool->start(&method2);
     //threadPool->start(&method3);*/
     return app.exec();
 }