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
template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}

LLI mod = 998244353;


bool search(vector<vector<int>> &graph, vector<bool> &visit, unordered_map<int,int> &memo, int cur, int p, int &c){
  visit[cur] = true;
  memo[cur] = p;

  if(p == 1) ++c;

  for(auto &next : graph[cur]){
    if(!visit[next]){
      if(!search(graph, visit, memo, next, !p, c)) return false;
    }

    if(memo[next] == p) return false;
  }
  return true;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int t; cin >> t;

  REP(_,t){
    int n,m; cin >> n >> m;
    vector<vector<int>> graph(n);
    REP(i,m){
      int u,v; cin >> u >> v;
      --u; --v;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    LLI ans = 1;

    vector<bool> visit(n, false);
    vector<bool> visit2(n, false);
    unordered_map<int, int> memo, memo2;
    
    REP(i,n){
      if(!visit[i]){
	
	LLI t = 0;

	int c = 0;
	if(search(graph, visit, memo, i, 0, c)){
	  (t += power(2LL, (LLI)c, mod)) %= mod;
	}

	c = 0;
	if(search(graph, visit2, memo2, i, 1, c)){
	  (t += power(2LL, (LLI)c, mod)) %= mod;
	}
	
	(ans *= t) %= mod;
      }
    }

    cout << ans << endl;
  }
  
  return 0;
}
