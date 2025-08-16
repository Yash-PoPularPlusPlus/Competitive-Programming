#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
 
const int INF = 1e18;
 
struct line {
    int m,k;
    line(int m,int k):m(m),k(k){}
    int operator()(const int x) const {
        return x*m+k;
    }
};
 
struct node {
    int L,R;
    node *left,*right;
    line best;
    node(int L,int R):L(L),R(R),left(nullptr),right(nullptr),best(0,INF){}
};
 
void update(node *curr,line x) {
    int mid = (curr->L + curr->R)/2;
    bool betterMid = x(mid)<curr->best(mid);
    bool betterL = x(curr->L)<curr->best(curr->L);
    bool betterR = x(curr->R)<curr->best(curr->R);
    if(betterMid) {
        swap(curr->best,x);
        update(curr,x);
    } else if(betterR) {
        if(curr->right==nullptr)curr->right = new node(mid+1,curr->R);
        update(curr->right,x);
    } else if(betterL) {
        if(curr->left==nullptr)curr->left = new node(curr->L,mid);
        update(curr->left,x);
    }
}
 
int get(node *curr,int x) {
    if(curr==nullptr)return INF;
    int mid = (curr->L + curr->R)/2;
    if(x<=mid)return min(curr->best(x),get(curr->left,x));
    return min(curr->best(x),get(curr->right,x));
}
 
int s[200001];
int f[200001];
int DP[200001];
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,x;
    cin >> n >> x;
    for(int i=1;i<=n;i++)cin>>s[i];
    for(int i=1;i<=n;i++)cin>>f[i];
    node *head = new node(1,1000000);
    update(head,{x,0});
    for(int i=1;i<=n;i++){
        DP[i] = get(head,s[i]);
        update(head,{f[i],DP[i]});
    }
    cout << DP[n] << '\n';
}
