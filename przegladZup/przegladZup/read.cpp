#include <fstream>
#include <list>
#include "Zad.h"
using namespace std;
list<Zad> readFromFile(const char *filename) {
    std::ifstream ifs(filename);
    //std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    int p;
    list<Zad> jobs;
    while(ifs>>p) {
        int d;
        ifs>>d;
        int t;
        ifs>>t;
        Zad z(p,d,t);
        jobs.push_back(z);
        //cout<<z<<endl;
    }
    return jobs;
};
