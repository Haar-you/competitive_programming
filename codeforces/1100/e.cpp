#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second
#ifdef DEBUG
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

LLI my_binary_search(LLI lower, LLI upper, function<bool(LLI)> f, bool tf=true){
  LLI mid;
  while(abs(upper-lower)>1){
    mid = (lower+upper)/2;
    
    if(f(mid)^(!tf)) lower = mid;
    else upper = mid;
  }
  return upper;
}

bool dfs(vector<vector<pair<int,int>>> &graph, vector<int> &visit, vector<int> &ret, int cur){
  if(visit[cur] == -1){
    return false;
  }

  if(visit[cur] == 0){
    visit[cur] = -1;
    
    for(auto &next : graph[cur]){
      if(!dfs(graph, visit, ret, next.fst)) return false;
    }
    visit[cur] = 1;
    ret.push_back(cur);
  }

  return true;
}

bool tsort(vector<vector<pair<int,int>>> &graph, vector<int> &ret){
  int n = graph.size();
  vector<int> visit(n, 0);
  REP(i,n) if(visit[i] == 0) if(!dfs(graph,visit,ret,i)) return false;
  reverse(ALL(ret));
  return true;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m; cin >> n >> m;
  vector<vector<pair<int,int>>> graph(n);
  vector<pair<int,int>> edges(m);
  REP(i,m){
    int u,v,c; cin >> u >> v >> c;
    --u, --v;
    graph[u].push_back(make_pair(v,c));
    edges[i] = {u,v};
  }
  
  vector<int> ret;
  auto f = [&](LLI c){
	     vector<vector<pair<int,int>>> g(n);
	     REP(i,n){
	       for(auto &p : graph[i]){
		 if(p.snd > c){
		   g[i].push_back(p);
		 }
	       }
	     }
	     ret.clear();
	     bool a = tsort(g,ret);
	     return a;
	   };
  
  int min_cost = my_binary_search(-1,1e9,f,false);
  
  f(min_cost);

  vector<int> ts(n);
  REP(i,n) ts[ret[i]] = i;

  vector<int> ans;
  REP(i,m){
    if(ts[edges[i].fst] > ts[edges[i].snd]){
      ans.push_back(i+1);
    }
  }

  cout << min_cost << " " << ans.size() << endl;
  join(cout, ALL(ans));

  return 0;
}
