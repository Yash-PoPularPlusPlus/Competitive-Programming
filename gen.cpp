	#include <bits/stdc++.h>
	using namespace std;

	#define ll long long
	#define all(x) x.begin(),x.end()
	#define pb(x) push_back(x)
	#define mp(x,y) make_pair(x,y)
	#define vf first
	#define vs second

	int rand(int a , int b){
		return a + (rand() % (b - a + 1));
	}

	int main(int argc , char *argv[]){
		srand(atoi(argv[1]));
		int x = rand(0,20);
		cout << x << '\n';
		return 0;
	}