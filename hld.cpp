#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
#define vf first
#define vs second
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
 
const int N = 200001;
 
vector<int> adj[N];
int heavy[N] , tin[N], timer, depth[N] , head[N] , parent[N];
 
int dfs(int node ,int par){
	depth[node] = depth[par] + 1;
	heavy[node]=-1;
	parent[node] = par;
	int mx = 0;
	int pos = -1;
	int total = 1;
	for(int i : adj[node]){
		if(i!=par){
			int cur = dfs(i , node);
			total += cur;
			if(cur > mx){
				mx = cur;
				pos = i;
			}
		}
	}
	heavy[node] = pos;
	return total;
}
 
void decompose(int node, int heavy_par){
	tin[node] = timer++;
	head[node] = heavy_par;
	if(heavy[node] != -1){
		decompose(heavy[node] , heavy_par);
	}
	
	for(int i : adj[node]){
		if(i != parent[node] && i != heavy[node]){
			decompose(i , i);
		}
	}
}
 
struct Seg {
	
	int siz;
	vector<int> v;
	
	void init(int n){
		siz=1;
		while(siz < n)siz *= 2;
		
		v.assign(siz*2,0);
	}
	
	void build(vector<int>& a , int x , int lx ,int rx){
		if(rx - lx == 1){
			if(lx < (int)a.size())v[x] = a[lx];
			return;
		}
		int m = (lx + rx)/2;
		build(a , 2 * x + 1 , lx , m);
		build(a , 2 * x + 2 , m , rx);
		v[x] = max(v[2 * x + 1] , v[2 * x + 2]);
	}
	
	void build(vector<int>& a){
		build(a , 0 ,  0 , siz);
	}
	
	void set(int pos , int val , int x, int lx ,int rx){
		if(rx - lx == 1){
			v[x] = val;
			return;
		}
		int m = (lx + rx)/2;
		if(pos < m){
			set(pos , val , 2 * x + 1 , lx , m);
		}
		else set(pos , val , 2 * x + 2 , m , rx);
		v[x] = max(v[2 * x + 1] , v[2 * x + 2]);
	}
	
	void set(int pos , int val){
		set(pos, val , 0 , 0 ,  siz);
	}
	
	int range(int l , int r , int x , int lx , int rx){
		if(l >= rx || lx >= r)return 0;
		if(lx >= l && rx <= r)return v[x];
		int m = (lx + rx)/2;
		return max(range(l , r , 2 * x + 1 , lx , m) , range(l , r , 2 * x + 2 , m , rx));
	}
	
	int range(int l , int r){
		return range(l , r , 0 , 0 , siz);
	}
};
 
void solve(){
	int n, q;
	cin >> n >> q;
	int arr[n];
	for(int i = 0; i < n; i++)cin >> arr[i];
	
	for(int i = 0; i < n-1; i++){
		int a , b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	vector<int> v(n);
	depth[0] = 0;
	timer = 0;
	
	dfs(0,0);
	
	decompose(0 , 0);
	
	for(int i = 0; i < n; i++){
		v[tin[i]] = arr[i];
	}
	
	Seg st;
	st.init(n);
	st.build(v);
	
	while(q--){
		int type;
		cin >> type;
		if(type == 1){
			int pos , x;
			cin >> pos >> x;
			pos--;
			st.set(tin[pos] , x);
		}
		else {
			int x , y;
			cin >> x >> y;
			x--;
			y--;
			int res = 0;
			while(head[x] != head[y]){
				//cout << head[x] << ' ' << head[y] << endl;
				if(depth[head[x]] < depth[head[y]]){
					swap(x,y);
				}
				res = max(res , st.range(tin[head[x]] , tin[x] + 1));
				x = head[x];
				x = parent[x];
				//cout << x << ' ' << res << '\n';
			}
			if(depth[x] > depth[y]){
				swap(x,y);
			}
			//cout << x << ' ' << y << ' ' << st.range(tin[x] , tin[y] + 1) << '\n';
			res = max(res , st.range(tin[x] , tin[y] + 1));
			cout << res << ' ';
		}
	}
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//int t;
	//cin >> t;
	//	while(t--)
	solve();
}
