void Dijkstra(ll e){
	 priority_queue< pair<ll,ll>, vector <pair<ll,ll>> , greater<pair<ll,ll>> > pq; 
	 dis[e]=0;
	 pq.push({0,e});
	 while(!pq.empty()){
		 ll node = pq.top().second,ww=pq.top().first;
		 pq.pop();
		 if(dis[node] < ww)continue;
		 for(auto i : adj[node]){
			 ll w = i.second;
			 if(dis[i.first] > dis[node] + w){
				 dis[i.first] = dis[node] + w;
				 pq.push({dis[i.first],i.first});
			 }
		 }
	 }
}
