#include "Zad.h"

	istream &operator>>(istream &cin, Zad &z) {
		cin>>z.p>>z.d>>z.w;
		return cin;
	};
	ostream &operator<<(ostream &cout, const Zad &z) {
		cout<<z.nr<<" koszt="<<z.p<<" deadline="<<z.d<<" waga="<<z.w<<endl;
		return cout;
	};
	Zad::Zad(int p, int d, int w):p(p),d(d),w(w),nr(nr_all) {
		cout<<"stworzono nowe zadanie, INFO: ";
		cout<<(*this)<<endl;
		nr_all++;
	};
	Zad::Zad() {
	};
	int Zad::costIfEndsAt(int C) const {
	    return max(0, C-d)*w;
	};
int Zad::nr_all=0;

