#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

template <typename T, typename U> ostream& operator<<(ostream& os, pair<T,U> &p){
  os << p.first << "," << p.second;
  return os;
}

namespace std {
  template <>
  class hash<pair<int,int>>{
  public:
    size_t operator()(const pair<int,int> &x) const{
      return hash<int>()(x.first) ^ hash<int>()(x.second);
    }
  };
}

bool dfs(vector<unordered_set<int>> &graph, vector<int> &in, vector<int> &out, vector<bool> &visit,
	 unordered_map<pair<int,int>,int> &edges, unordered_map<pair<int,int>,int> &used, int cur){

  visit[cur] = true;
  
  for(auto next : graph[cur]){
    if(visit[next] && used[{cur,next}]) continue;

    bool f = false;
    if(visit[next] && !used[{cur,next}]) f = true;

    used[{cur,next}] = true;
    used[{next,cur}] = true;

    if(in[cur] % 2 == 0){
      if(graph[cur].size() - in[cur] - out[cur] == 1){
	out[cur]++;
	in[next]++;
	edges[{cur,next}] = 0;
	edges[{next,cur}] = 1;
        bool r = true;
	if(f){
	  if(graph[next].size() - in[next] - out[next] == 0 && in[next] % 2 != 0){
	    r = false;
	  }
	}else{
	  r = dfs(graph,in,out,visit,edges,used,next);
	}
	
	if(!r){
	  out[cur]--;
	  in[next]--;
	  
	  out[next]++;
	  in[cur]++;

	  edges[{next,cur}] = 0;
	  edges[{cur,next}] = 1;
	}
      }else{
	out[next]++;
	in[cur]++;
	edges[{next,cur}] = 0;
	edges[{cur,next}] = 1;
        bool r = true;
	if(f){
	  if(graph[next].size() - in[next] - out[next] == 0 && in[next] % 2 != 0){
	    r = false;
	  }
	}else{
	  r = dfs(graph,in,out,visit,edges,used,next);
	}

	if(!r){
	  out[next]--;
	  in[cur]--;

	  out[cur]++;
	  in[next]++;
	  edges[{cur,next}] = 0;
	  edges[{next,cur}] = 1;
	}
      }
    }else{
      out[cur]++;
      in[next]++;
      edges[{cur,next}] = 0;
      edges[{next,cur}] = 1;
      bool r = true;
      if(f){
	if(graph[next].size() - in[next] - out[next] == 0 && in[next] % 2 != 0){
	  r = false;
	}
      }else{
	r = dfs(graph,in,out,visit,edges,used,next);
      }

      if(!r){
	out[cur]--;
	in[next]--;
	  
	out[next]++;
	in[cur]++;

	edges[{next,cur}] = 0;
	edges[{cur,next}] = 1;
      }

    }
  }

  if(in[cur] % 2 != 0) return false;
  return true;
}

int main(){

  int T; cin >> T;
  REP(_,T){
    int N,M; cin >> N >> M;

    vector<unordered_set<int>> graph(N);
    unordered_map<pair<int,int>,int> edges;

    REP(i,M){
      int u,v; cin >> u >> v;
      --u; --v;
      
      graph[u].insert(v);
      graph[v].insert(u);
      edges[{u,v}] = i;
    }
    
    if(M % 2 == 1){
      cout << -1 << endl;
      continue;
    }

    unordered_map<pair<int,int>,int> es;
    unordered_map<pair<int,int>,int> used;
    vector<int> indg(N), outdg(N);
    vector<bool> visit(N,false);

    dfs(graph,indg,outdg,visit,es,used,0);

    
    vector<int> ans(M);

    for(auto &kv : edges){
      ans[kv.second] = es[kv.first];
    }
    
    join(cout, ALL(ans));
  }
  
  return 0;
}
