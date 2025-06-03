struct item {
	ll add;
};
 
struct Seg {
	ll siz = 1; 
	vector<item> val;
	void init(int n){
		while(siz < n)siz*=2;
		
		val.resize(siz * 2);
	}
	
	item NutralElement = {0};
	
	item merge(item a , item b){
		return {
			a.add + b.add,
		};
	}
	
	item single(int v){
		return {v};
	}
	
	void build(vector<int>& arr  , int x , int lx , int rx){
		if(rx-lx==1){
			if(lx < (int)arr.size()){
				val[x] = single(arr[lx]);
			}
			else val[x]=NutralElement;
			return;
		}
		int m = (lx + rx) / 2;
		build(arr , 2 * x + 1 , lx , m);
		build(arr, 2 * x + 2 , m , rx);
    merge(val[2 * x + 1] , val[2 * x + 2]);
	}
	
	void build(vector<int>& arr){
		build(arr , 0 , 0 , siz);
	}
	
	void set(int i , int v , int x , int lx , int rx){
		if(rx - lx == 1){
			val[x] = single(v);
			return;
		}
		int m = (lx + rx) / 2;
		if(i < m){
			set(i , v , 2 * x + 1 , lx , m);
		}
		else {
			set(i , v , 2 * x + 2 , m , rx);
		}
		val[x]=merge(val[2 * x + 1] , val[2 * x + 2]);
	}
	
	void set(int x , int y){
		set(x  ,y , 0 , 0 , siz);
	}
	
	item sum(int l , int r , int x , int lx , int rx){
		if(lx >= r  || l >= rx)return NutralElement;  
		if(lx >= l && rx <= r){
			return val[x];
		}
		int m = (lx + rx) / 2;
		return merge(sum(l , r , 2 * x + 1 ,lx , m) , sum(l , r , 2 * x + 2, m , rx));
	}
	
	item sum(int l , int r){
		return sum(l , r , 0 , 0 , siz);
	}
	
};
