#include <bits/stdc++.h>
using namespace std;
const int N=500;

void dfs(int node,vector<vector<pair<int,int>>> &adj,vector<int> &vis,vector<int> &component){
    
    vis[node]=1;
    component.push_back(node);
    
    for(auto it: adj[node]){
        if(!vis[it.first]){
            dfs(it.first,adj,vis,component);
        }
    }
    return;
}


int main() {
    //TASK A
	vector<vector<pair<int,int>>> adj(N);
	srand(time(0));
	for(int i=0;i<N;i++){
	    int numconnections=rand()%1+1;
	    for(int j=0;j<numconnections;j++){
	        int v=rand()%N;
	        if(v==i)continue;
	        int wt=rand()%46+5;
	        adj[i].push_back({v,wt});
	        adj[v].push_back({i,wt});
	    }
	}
	cout<<"Total Cities: "<<N<<endl;
	int E=0;
	for(int i=0;i<N;i++){
	    E+=adj[i].size();
	}
	cout<<"Total number of Edges: "<<E/2<<endl;

    cout<<"Adjacency List Representation:"<<endl;

    for(int i=0;i<N;i++){
        cout<<"City_id_"<<i<<" = [";
        for(int j=0;j<adj[i].size();j++){
            cout<<"("<<adj[i][j].first<<","<<adj[i][j].second<<")";
            if(j != adj[i].size()-1){
                cout<<",";
        }
    }
    cout<<"]"<<endl;
    }
	//TASK A COMPLETED
	
	//TASK B
	vector<int> vis(N,0);
    vector<int> LargestC;
    for(int i=0;i<N;i++){
        if(!vis[i]){
            vector<int> component;
            dfs(i,adj,vis,component);
            if(component.size()>LargestC.size()){
                LargestC=component;
            }
        }
    }
    cout<<"Largest Connected Component Size: ";

    cout<<LargestC.size()<<endl;

    cout<<"Cities: "<<endl;

    for(auto x : LargestC) {
    cout<<x<<" ";
    }
    cout<<endl;
    //TASK B COMPLETED
    
    //TASK C
    vis.assign(N,0);
    vector<vector<int>>components;
    for(int i=0;i<N;i++){
        if(!vis[i]){
            vector<int> component;
            dfs(i,adj,vis,component);
            components.push_back(component);
        }
    }
    int Largest=0;
    int smallest=1e9;
    for(int i=0;i<components.size();i++){
        int sze=components[i].size();
        Largest=max(Largest,sze);
        smallest=min(smallest,sze);
    }
    cout<<"Total number of connected components: "<<components.size()<<endl;
    for(auto it:components){
        cout<<it.size()<<" ";
    }
    cout<<endl;
    cout<<"Largest Cluster size: "<<Largest<<endl;
    cout<<"Smallest Cluster size: "<<smallest<<endl;
    //TASK C COMPLETED
    
    //TASK D 
    vector<int> dist(N,1e9);
    int src=0;
    dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,src});
    while(!pq.empty()){
        auto it=pq.top();
        int dis=it.first;
        int node=it.second;
        pq.pop();
        for(auto it:adj[node]){
            if(dis+it.second<dist[it.first]){
                dist[it.first]=dis+it.second;
                pq.push({dis+it.second,it.first});
            }
        }
    }
    for(int i=0;i<N;i++){
        cout<<"City_id_"<<i<<" dist="<<dist[i]<<endl;
    }
    int flag=0;
    cout<<"Unreachable cities: ";
    for(int i=0;i<N;i++){
        if(dist[i]==1e9){
            flag=1;
            cout<<i<<" ";
        }
    }
    if(flag==0)cout<<"NONE"<<endl;
    else cout<<endl;
    int city=0;
    int maxi=0;
    for(int i=0;i<N;i++){
        if(dist[i]!=1e9){
            if(dist[i]>maxi){
                city=i;
                maxi=dist[i];
            }
        }
    }
    cout<<"City with maximum shortest-path distance from the source: city_id_"<<city<<" with a distance of "<<maxi<<" from Source"<<endl;
    //TASK D COMPLETED
    
}
