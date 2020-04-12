//RohitKaushal

/* Design an array based data structure for three stacks as done for two stacks in the tutorials.
The three stacks should share the same array in an efficient manner. If there are MaxSize
entries in the array then the IsFull/overflow function should only return true if all the
entries in the array are occupied. */

#include <bits/stdc++.h>
using namespace std;

template <class Tm>
class TrippleStack {
public:
	int T;
	int sz;
	Tm *ss;
	int Atop;
	int Btop;
	int Ctop,Cbase;
	TrippleStack(int t=10){
		T = t;
		ss = new Tm[T+1];
		sz = 0;
		Atop = -1;
		Btop = T+1;
		Ctop=T/2,Cbase=T/2;
	}

	void shiftRight(){
		for (int i = Ctop+1; i >Cbase; --i)
		{
			ss[i]=ss[i-1];
		}
		Cbase++; Ctop++;
	}
	void shiftLeft(){
		for (int i = Cbase-1; i < Ctop; ++i)
		{
			ss[i]=ss[i+1];
		}
		Cbase--; Ctop--;
	}

	void pushA(Tm x){
		if(sz==T){
			cerr<<"Overflow..\n";
			return;
		}

		else if(Atop == Cbase)
			shiftRight();
		
		ss[++Atop]=x;
		sz++;
	}

	void pushB(Tm x){
		if(sz==T){
			cerr<<"Overflow..\n";
			return;
		}

		if(Btop-1 == Ctop)
			shiftLeft();
		
		ss[--Btop]=x;
		sz++;
	}

	void pushC(Tm x){
		if(sz==T){
			cerr<<"Overflow..\n";
			return;
		}

		if(Ctop+1 == Btop)
			shiftLeft();

		ss[++Ctop]=x;
		sz++;
	}

	Tm popA(){
		if(Atop == -1){
			cout<<"Underflow..\n";
			return 0;
		}
		Atop--; sz--;
		return ss[Atop+1];
	}

	Tm popB(){
		if(Btop == T+1){
			cout<<"Underflow..\n";
			return 0;
		}
		Btop++; sz--;
		return ss[Btop-1];
	}

	Tm popC(){
		if(Ctop == Cbase){
			cout<<"Underflow..\n";
			return 0;
		}
		Ctop--; sz--;
		return ss[Ctop+1];
	}

	Tm topA(){ return ss[Atop]; }
	Tm topB(){ return ss[Btop]; }
	Tm topC(){ return ss[Ctop]; }

	void showAll(){
		for (int i = 0; i < T+1; ++i)
		{
			cout<<" "<<ss[i];
			if(i==Atop) cout<<"A";
			if(i==Btop) cout<<"B";
			if(i==Cbase) cout<<"Cb";
			if(i==Ctop) cout<<"Ct";
		}
		cout<<"\n";
	}

	void showA(){
		for (int i = 0; i <= Atop; ++i)
		{
			cout<<" "<<ss[i];
		}
		cout<<" A\n";
	}

	void showB(){
		for (int i = T; i >= Btop; --i)
		{
			cout<<" "<<ss[i];
		}
		cout<<" B\n";
	}

	void showC(){
		for (int i = Cbase+1; i <= Ctop; ++i)
		{
			cout<<" "<<ss[i];
		}
		cout<<" C\n";
	}

	bool isFull(){
		return sz==T;
	}
	bool isEmpty(){
		return !sz;
	}
	
};
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	TrippleStack<int> st(10);

	cout<<"Empty : "<<st.isEmpty()<<" Full : "<<st.isFull()<<"\n\n";
	cout<<" Push \n";
	st.pushA(1);
	st.pushA(2);
	st.pushA(3);
	st.pushB(4);
	st.pushB(5);
	st.pushB(6);
	st.pushB(7);
	st.pushC(8);
	st.pushC(9);
	st.pushC(10);

	st.showAll();
	cout<<"\nEmpty : "<<st.isEmpty()<<" Full : "<<st.isFull()<<"\n\n";

	st.showA();
	st.showB();
	st.showC();
	

	cout<<"\n Pop \n";
	st.popA();
	st.popB();
	st.popB();
	st.popC();
	st.popC();

	st.showAll();

	cout<<"\nEmpty : "<<st.isEmpty()<<" Full : "<<st.isFull()<<"\n\n";

	st.showA();
	st.showB();
	st.showC();
	

	return 0;
}