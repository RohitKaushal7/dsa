//RohitKaushal
#include <bits/stdc++.h>
using namespace std;

template <class T>
class DoubleStack_Queue
{
	stack<T> sta;
	stack<T> stb;
	int size;
	bool state; // 0 : insert [sta] , 1 : remove [stb]

	void _interchange(){
		T x;
		if(state){
			while(!stb.empty()){
				x = stb.top();
				sta.push(x);
				stb.pop();
			}
		}
		else{
			while(!sta.empty()){
				x = sta.top();
				stb.push(x);
				sta.pop();
			}
		}

		state = !state;
	}

public:
	
	DoubleStack_Queue(){
		state = 0;
		size = 0;
	}
	
	void insert(T x){
		if(state)
			_interchange();

		sta.push(x);
		size++;
	}

	T remove(){
		if(!state)
			_interchange();

		if(!size){
			cout<<"Underflow.. \n";
			return T(0);
		}
		T item = stb.top();
		stb.pop();
		size--;
		return item;
	}

	bool empty(){
		return !size;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	DoubleStack_Queue<int> q;
	cout<<"\nEmpty : "<<q.empty()<<"\n";

	q.insert(5);
	q.insert(4);
	q.insert(3);
	q.insert(2);

	cout<<q.remove()<<" ";
	cout<<q.remove()<<" ";
	cout<<q.remove()<<" ";

	q.insert(7);
	q.insert(6);

	cout<<q.remove()<<" ";
	cout<<q.remove()<<" ";

	cout<<"\nEmpty : "<<q.empty()<<"\n";


	return 0;
}