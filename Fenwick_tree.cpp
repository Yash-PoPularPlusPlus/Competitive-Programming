struct Fen {
	
	vector<ll> tree;
  int siz;
	
	void init(int n){
		tree.assign(n + 1 , 0LL);	
    siz = n;
	}
	
	void set(int i , ll val){
		i++;
		while(i <= siz){
			tree[i] += val;
			i += (i & (-i));
		}
	}
	
	ll sum(int i){
		i++;
		ll ans = 0;
		while(i > 0){
			ans += tree[i];
			i -= (i & (-i));
		}
		return ans;
	}
	
};
