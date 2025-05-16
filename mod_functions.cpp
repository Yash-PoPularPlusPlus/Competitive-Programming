vector<ll> fact;
 
ll add(ll x, ll y){
	return (x+y)%mod;
}
 
ll multi(ll x , ll y){
	return (x*y)%mod;
}
 
void fac(int n){
	fact.pb(1);
	for(ll i = 1; i <= n; i++){
		fact.pb(multi(i,fact.back()));
	}
}
 
ll power(ll x , ll y){
	x %= mod;
	ll res = 1;
	while(y > 0){
		if(y&1)res=multi(res,x);
		y=y>>1;
		x = multi(x,x);
	}
	return res;
}
 
ll inverse(ll n){
	return power(n,mod-2);
}
 
ll nCr(int n , int r){
	if(r < 0 || n < 0)return 1;
	if(n<r)return 1;
	if(r==0)return 1;
	return (multi(fact[n],multi(inverse(fact[r]),inverse(fact[n-r]))))%mod;
}
