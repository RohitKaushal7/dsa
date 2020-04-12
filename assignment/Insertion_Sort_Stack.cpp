#include <bits/stdc++.h>
using namespace std;

template <class T> 
stack<T> inserion_sort_stack(stack<T> src){
	stack<T> ans,aux;
	while(!src.empty()){
		T el = src.top(); src.pop();

		while(!ans.empty() && el > ans.top()){
			T greater = ans.top(); ans.pop();
			aux.push(greater);
		}

		ans.push(el);

		while(!aux.empty()){
			T aux_el = aux.top(); aux.pop();
			ans.push(aux_el);
		}
	}

	return ans;
}



int main(){
	stack <int> s;

	int n,el;

	n = 10;
	int test[n] = { 3,4,5,6,2,1,8,7,3,5}; // #test

	// cout << "Number of Elements? : ";
	// cin >> n;

	for (int i = 0; i < n; ++i)
	{
		// cin >> el;
		el = test[i]; // #test
		s.push(el);
	}


	s = inserion_sort_stack(s);

	for (int i = 0; i < n; ++i)
	{
		cout << s.top() << " ";
		s.pop();
	}
}