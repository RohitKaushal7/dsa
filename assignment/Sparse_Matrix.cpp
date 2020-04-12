//RohitKaushal

/* 1. A matrix is sparse if most elements of the matrix are zero. We might store a large sparse
matrix (to save space) as a list of triples (i, j, value) where (i, j) is a position and value is
a non-zero value. We may represent the list in an array A[t, 3], where t is an upper bound
on the number of non-zero elements. Further, we may maintain the list sorted so that the
row numbers are increasing and within a row the column numbers are increasing. Design
algorithms to i) transpose a sparse matrix ii) add two sparse matrices and iii) multiply
two sparse matrices. */

#include <bits/stdc++.h>
using namespace std;


class Matrix
{
	int T;
	int **arr;
	int K=0;

	void free(int **arr){
		for (int i = 0; i < T; ++i)
		{
			delete[] arr[i];
		}
		delete [] arr;
	}

	void init(){
		for (int i = 0; i < T; ++i)
		{
			arr[i][0]=arr[i][1]=arr[i][2]=-1;
		}
	}

	void _put(int a,int i,int j,int v){
		arr[a][0] = i;
		arr[a][1] = j;
		arr[a][2] = v;
	}


public:

	Matrix(int size=100){
		T = size;
		arr = new int*[T];
		for (int i = 0; i < T; ++i)
		{
			arr[i] = new int[3];
		}
		init();
	}

	// ~Matrix(){
	// 	for (int i = 0; i < T; ++i)
	// 	{
	// 		delete[] arr[i];
	// 	}
	// 	delete [] arr;
	// }

	static Matrix _addE(Matrix &a,Matrix &b){
		int sz = a.K+b.K;
		Matrix c(sz);
		int ai,bi;
		for (ai = 0, bi=0; ai < a.K && bi < b.K;){
			if(a[ai][0]==b[bi][0]){

				if(a[ai][1]==b[bi][1]){
					c.insert(a[ai][0],a[ai][1],a[ai][2] + b[bi][2]);
					ai++; bi++;
				}

				else if(a[ai][1]<b[bi][1]){
					c.insert(a[ai][0],a[ai][1],a[ai][2]);
					ai++;
				}
				else{
					c.insert(b[bi][0],b[bi][1],b[bi][2]);
					bi++;
				}
			}
			else{
				if(a[ai][0]<b[bi][0]){
					c.insert(a[ai][0],a[ai][1],a[ai][2]);
					ai++;
				}
				else{
					c.insert(b[bi][0],b[bi][1],b[bi][2]);
					bi++;
				}
			}
		}

		while(ai<a.K){
			c.insert(a[ai][0],a[ai][1],a[ai][2]);
			ai++;
		}

		while(bi<b.K){
			c.insert(b[bi][0],b[bi][1],b[bi][2]);
			bi++;
		}
		return c;
	}
	static Matrix & _add(Matrix &a, Matrix &b){
		int sz = a.K+b.K;
		Matrix c(sz);
		for (int i = 0; i < a.K; ++i){
			c.insert(a[i][0],a[i][1],a[i][2]);
		}
		for (int i = 0; i < b.K; ++i){
			c.insert(b[i][0],b[i][1],b[i][2], [&](int a,int i,int j,int v,int &K){
				c.arr[a][2] += v;
				K--;
			});
		}
		return c;
	}
	static Matrix _mult(Matrix x,Matrix y){
		int xmi,xmj,ymi,ymj;
		xmi = x.arr[x.K-1][0];
		ymi = y.arr[y.K-1][0];
		xmj=ymj=0;

		Matrix c;

		for (int i = 0; i < x.K; ++i)
			xmj = max(xmj,x[i][1]);
		for (int i = 0; i < y.K; ++i)
			ymj = max(ymj,y[i][1]);

		int mi = max(xmi,ymi);
		int mj = max(xmj,ymj);
		int m = max(mj,mi)+1;

		// cerr<<"multiplying";
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				int v = 0;
				// cerr<<".";
				for (int k = 0; k < m; ++k)
				{
					v+=x.get(i,k)*y.get(k,j);
				}
				if(v){
					// cerr<<"inserting "<<i<<" "<<j<<" "<<v<<"\n";
					c.insert(i,j,v);
				}
			}
		}

		return c;
	}


	void transpose(){
		Matrix tmp;
		for (int a = 0; a < K; a++)
		{
			tmp.insert(arr[a][1],arr[a][0],arr[a][2]);
		}
		free(arr);

		arr = tmp.arr;
		
	}

	int* & operator [](int i) {
		return arr[i];
		}
	friend Matrix operator +(Matrix &x,Matrix &y) {
		return _addE(x,y);
	}
	friend Matrix operator *(Matrix &x,Matrix &y) {
		return _mult(x,y);
	}

	Matrix & operator=(const Matrix &x){ 
		T = x.T;
		K = x.K;
		// free(arr);
		// arr = x.arr;
		if(this != &x){
			for (int i = 0; i < x.K; i++)
				{
					arr[i][0]=x.arr[i][0];
					arr[i][1]=x.arr[i][1];
					arr[i][2]=x.arr[i][2];
				}
		}
		return *this;
	}



	int get(int i,int j){
		for (int a = 0; a < K; ++a)
		{
			if(arr[a][0]==i && arr[a][1]==j){
				return arr[a][2];
			}
		}
		return 0;
	}

	void insert(int i,int j,int v,function<void(int a,int i,int j,int v,int &K)> same = NULL){
		// cerr<<"inserting "<<i<<" "<<j<<" "<<v<<"\n";
		if(!same){
			same = [&](int a,int i,int j,int v,int &K){_put(a,i,j,v);K--;};
		}

		auto _shiftAndInsert = [&](int a, int i,int j, int v){
			for (int p = K; p > a; --p)
			{
				arr[p][0] = arr[p-1][0];
				arr[p][1] = arr[p-1][1];
				arr[p][2] = arr[p-1][2];
			}
			_put(a,i,j,v);
		};

		if(i<0 || j<0){
			cerr<<"Segmentation Fault"<<i<<" "<<j<<"\n";
			return;
		}

		if(K+1==T){
			cerr<<"Overflow.\n";
			return;
		}

		for (int a = 0; a <= K; ++a)
		{
			if(arr[a][0] < 0){
				_put(a,i,j,v);
				break;
			}
			else{
				if(arr[a][0] == i && arr[a][1] == j){
					same(a,i,j,v,K);
					break;
				}
				else if(arr[a][0] == i && arr[a][1] > j){
					_shiftAndInsert(a,i,j,v);
					break;
				}
				else if(arr[a][0] > i){
					_shiftAndInsert(a,i,j,v);
					break;
				}
			}
		}

		K++;
	}

	void remove(int i,int j){

		auto _shiftAndRemove = [&](int a){
			for (int p = a; p < K-1; ++p)
			{
				arr[p][0] = arr[p+1][0];
				arr[p][1] = arr[p+1][1];
				arr[p][2] = arr[p+1][2];
			}

			arr[K-1][0] = -1;
			arr[K-1][1] = -1;
			arr[K-1][2] = -1;
		};

		for (int a = 0; a < K; ++a)
		{
			if(arr[a][0] == i && arr[a][1] == j){
				_shiftAndRemove(a);
				K--;
				break;
			}
			else if(arr[a][0]==i && arr[a][1]>j || arr[a][0] > i ){
				cerr<<"["<<i<<"]["<<j<<"] NOT Found.\n";
				break;
			}
		}
		
	}

	void show(){
		for (int i = 0; i < K; ++i)
		{
			cout<<"["<<arr[i][0]<<" "<<arr[i][1]<<"]  "<<arr[i][2]<<"\n";
		}
	}

	void showMatrix(){
		int mi,mj;
		mi = arr[K-1][0];
		mj=0;
		for (int i = 0; i < K; ++i)
			mj = max(mj,arr[i][1]);

		for (int i = 0; i <= mi; ++i)
		{
			for (int j = 0; j <= mj; ++j)
			{
				cout<<get(i,j)<<" ";
			}
			cout<<"\n";
		}
	}

};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int test[9] = {1,2,3,4,5,6,7,8,9}; // 3x3 matrix for test

	Matrix m;
	cout<<"Enter Matrix 3x3\n";
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int v;
			// cin>>v;
			v = test[3*i+j];
			m.insert(i,j,v);
		}
	}
	// m.insert(3,3,10);
	cout<<"Matrix M\n";
	
	// m.show();
	m.showMatrix();


	Matrix n;
	cout<<"\nMatrix N = M'\n";
	n=m;
	n.transpose();
	// n.show();
	n.showMatrix();

	Matrix c;

	cout<<"\nMatrix C = M+N\n";
	c = m+n;
	// c.show();
	c.showMatrix();

	cout<<"\nMatrix C = M*N\n";
	c = m*n;
	// c.show();
	c.showMatrix();



	return 0;
}

// Issues ... 
/* 
 - there are memory leaks in _add() and _mult() functions >> c.arr 
 - also cant free memory in destructor as some functions return objects.

*/