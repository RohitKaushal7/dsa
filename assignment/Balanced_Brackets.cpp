#include <bits/stdc++.h>
using namespace std;


bool is_balanced(string src){

	stack<char> st;
	map<char,char> pairs;
	pairs['{'] = '}';
	pairs['['] = ']';
	pairs['('] = ')';

	for (int i = 0; i < src.size(); ++i)
	{
		char ch = src[i];

		switch(ch){
			case '{':
			case '[':
			case '(':
				st.push(ch);
				break;

			case '}':
			case ']':
			case ')':
				if(st.empty())
					return false; // closing before opening

				char top = st.top();
				st.pop();

				if(pairs[top] != ch)
					return false; // bracket mismatch
		}
	}

	if(!st.empty())
		return false; // uneven brackets

	return true;
}


int main(int argc, char const *argv[])
{
	cout << is_balanced("{{{") << "\n";
	cout << is_balanced("{[()]}") << "\n";
	cout << is_balanced("}}}") << "\n";
	cout << is_balanced("") << "\n";
	return 0;
}