#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long 
#define pb(e) push_back(e)
#define sv(a) sort(a.begin(),a.end())
#define sa(a,n) sort(a,a+n)
#define mp(a,b) make_pair(a,b)
#define vf first
#define vs second
#define ar array
#define all(x) x.begin(),x.end()
const int inf = 0x3f3f3f3f;
const int mod = 1000000007; 
const double PI=3.14159265358979323846264338327950288419716939937510582097494459230;
bool remender(ll a , ll b){return a%b;}
 
const int N = 40004;
const int l = 25;
 
struct Query{
	int idx , l , r , lc1;
};
int cnt;
int b;
int f[N];
int arr[N];
Query que[100003];
vector<int> ft;
vector<int> adj[N];
int timer;
int tin[N], tout[N];
int up[N][l + 5];
int c[N];
 
void dfs(int v, int p){
    tin[v] = ++timer;
    ft.pb(v);
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
 
    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }
	ft.pb(v);
    tout[v] = ++timer;
}
 
bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
 
int lca(int u, int v){
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}
 
bool cmp(Query a , Query b1){
	return (a.l/b < b1.l/b) || (a.l/b == b1.l/b && a.r < b1.r);
}
 
void add(int x){
	x--;
	if(c[x] == 1){
		c[x] = 0;
		f[arr[x]]--;
		if(f[arr[x]] == 0)cnt--;
		return;
	}
	c[x] = 1;
	f[arr[x]]++;
	if(f[arr[x]] == 1)cnt++;
}
 
void rem(int x){
	x--;
	if(c[x] == 0){
		c[x] = 1;
		f[arr[x]]++;
		if(f[arr[x]] == 1)cnt++;
		return;
	}
	c[x] = 0;
	f[arr[x]]--;
	if(f[arr[x]] == 0)cnt--;
}
 
void solve(){
	// input 
	int n,m;
	cin >> n >> m;
	for(int i = 0; i < n; i++)cin >> arr[i];
	for(int i = 1; i < n; i++){
		int u , v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}



	// lca pre-compute
	b = sqrt(n);
	b = max(b , 1);
	timer = 0;
	dfs(1,1);


	// compression


	int cur = 1;
	map<int,int> m1;
	for(int i = 0; i < n; i++)m1[arr[i]]++;
	for(auto it : m1){
		m1[it.vf] = cur;
		cur++;
	}
	for(int i = 0; i < n; i++)arr[i] = m1[arr[i]];



	// input of queries
	for(int i = 0; i < m; i++){
		int u , v;
		cin >> u >> v;
		if(tin[u] > tin[v])swap(u,v);
		int lc = lca(u , v);
		if(u == lc || v == lc){
			que[i] = {i , tin[u] , tin[v] , -1};
		}
		else {
			que[i] = {i , tout[u] , tin[v] , lc};
		}
	}



	// mo's algo


	sort(que , que + m , cmp);
	cnt = 0;
	memset(c,0,sizeof c);
	int curl = que[0].l , curr = que[0].l - 1;
	int ans[m];
	memset(f,0,sizeof f);
	for(int i = 0; i < m; i++){
		while(curr < que[i].r)add(ft[(++curr)-1]);
		while(curl > que[i].l)add(ft[(--curl)-1]);
		while(curl < que[i].l)rem(ft[(curl++)-1]);
		while(curr > que[i].r)rem(ft[(curr--)-1]);
		int res = cnt;
		if(que[i].lc1 != -1 && f[arr[que[i].lc1 - 1]] == 0){
			res++;
		}
		ans[que[i].idx] = res;
	}
	for(int i = 0; i < m; i++){
		cout << ans[i] << '\n';
	}
}
 
int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
	//int t;cin >> t;while(t--)
	solve();
	return 0;
}
 
