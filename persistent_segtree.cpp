struct Node {
	int pos , left , right;
	ll val;
};
 
struct Seg {
	int siz;
	vector<vector<Node>> v;
	
	void init(int n){
		siz = 1;
		while(siz < n)siz *= 2;
		
		v.resize(siz * 2);
	}
	
	Node single(ll x , int p){
		Node val;
		val.pos = p;
		val.val=x;
		val.left = -1;
		val.right=-1;
		return val;
	}
	
	Node merge(Node a , Node b , int p){
		Node res;
		res.pos = p;
		res.left = a.pos;
		res.right = b.pos;
		res.val = a.val + b.val;
		return res;
	}
	
	int build(vector<int>& a , int x , int lx , int rx){
		if(rx - lx == 1){
			if(lx < a.size()){
				v[x].pb(single(a[lx] , 0));
			}
			else v[x].pb(single(0 , 0));
			return v[x].size()-1;
		}
		int m = (lx + rx)/2;
		int left = build(a , 2 * x + 1 , lx , m);
		int right = build(a , 2 * x + 2 , m , rx);
		v[x].pb(merge(v[2*x+1][left] , v[2*x+2][right] , v[x].size()));
		return v[x].size()-1;
	}
	
	int build(vector<int>& a){
		return build(a , 0 , 0 , siz);
	}
	
	int set(int i , ll val , int p , int x , int lx , int rx){
		if(rx - lx == 1){
			v[x].pb(single(val , v[x].size()));
			return v[x].size()-1;
		}
		int m = (lx + rx)/2;
		Node tp = v[x][p];
		if(i < m){
			tp.left = set(i , val , tp.left , 2 * x + 1 , lx , m);
		}
		else {
			tp.right = set(i , val , tp.right , 2 * x + 2 , m , rx);
		}
		v[x].pb(merge(v[2*x+1][tp.left] , v[2*x+2][tp.right] , v[x].size()));
		return v[x].size()-1;
	}
	
	int set(int i , ll val , int p){
		return set(i , val , p , 0 , 0 , siz);
	}
	
	ll range_sum(int l , int r , int p , int x , int lx , int rx){
		if(l >= rx || lx >= r)return 0;
		if(lx >= l && rx <= r)return v[x][p].val;
		int m = (lx + rx)/2;
		return range_sum(l , r , v[x][p].left , 2 *x + 1 , lx , m) + range_sum(l , r , v[x][p].right , 2 *x + 2 , m , rx);
	}
	
	ll range_sum(int l , int r , int p){
		return range_sum(l , r , p , 0 , 0 , siz);
	}
	
	int make_new(int pos){
		v[0].pb(v[0][pos]);
		return v[0].size()-1;
	}
};
