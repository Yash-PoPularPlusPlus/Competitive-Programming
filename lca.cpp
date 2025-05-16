const int N = 200005;
const int L = 25;
vector<int> adj[N];
int timer;
int tin[N], tout[N];
int up[N][L];
vector<int> ft;
 
void dfs(int v, int p){
    tin[v] = timer++;
    ft.pb(v);
    up[v][0] = p;
    for (int i = 1; i <= L; i++)
        up[v][i] = up[up[v][i-1]][i-1];
 
    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }
	  ft.pb(v);
    tout[v] = timer++;
}
 
bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
 
int lca(int u, int v){
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = L-1; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}
