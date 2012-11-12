#include <QtCore/QThread>

class WindowThread:public QThread {
    Q_OBJECT
    public:
    list<pair<int,int> > &exchange;
    WindowThread(list<pair<int,int> > &exchange):exchange(exchange) {

    };
    void run() {
     GraphWidget *widget = new GraphWidget(exchange);
     QMainWindow mainWindow;
     mainWindow.setCentralWidget(widget);
     mainWindow.show();
    }
};
