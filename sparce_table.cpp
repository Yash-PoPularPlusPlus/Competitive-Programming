struct SparseTable {
	vector<vector<ll>> st;
	int n;
	vector<int> LOG;
	void buildTable(vector<ll> &raw) {
		int k = LOG[n]+1;
		st.resize(k , vector<ll>(n));
		for(int i = 0; i < n; i++) st[0][i] = raw[i];
		for(int p = 1; p < k+1; p++)for(int i = 0; i + (1LL<<(p))-1 < n; i++) st[p][i] = max(st[p-1][i], st[p-1][i + (1LL << (p-1))]);
	}
 	void build(vector<ll> &nums) {
		n = nums.size();
		LOG.resize(n+1,0);
		for(int i = 2; i <= n; i++){
			LOG[i] = (LOG[(i/2)]+1);
		}
		buildTable(nums);
	}
	
	ll fun(int l, int r) {
		if (l > r) assert(false);
		int p = LOG[r-l+1];
		//cout << r - (1LL<<p) + 1 << ' ' << l << endl;
		return max(st[p][l], st[p][r - (1LL<<p)+1]);
	}
};
