#ifndef _ZAD
#define _ZAD
#include <iostream>
#include <istream>
#include <ostream>
using namespace std;
class Zad{
public:
	int p, d, w, nr;
	static int nr_all;
public:
	friend istream &operator>>(istream &cin, Zad &z);
	friend ostream &operator<<(ostream &cout, const Zad &z);
	Zad(int p, int d, int w);
	Zad();
	int costIfEndsAt(int C) const;
};
#endif
