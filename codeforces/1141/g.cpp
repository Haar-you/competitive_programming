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
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

int n,k;

void dfs(int cur, int par, int r, const vector<vector<int>> &graph, map<pair<int,int>,int> &edges, vector<int> &ans){
  if(graph[cur].size() > r){
    if(par == -1){
      for(auto &next : graph[cur]){
	ans[edges[{cur,next}]] = 1;
      }
    }else{
      for(auto &next : graph[cur]){
	ans[edges[{cur,next}]] = ans[edges[{cur,par}]];
      }
    }
  }else{
    int i = 1;
    for(auto &next : graph[cur]){
      if(next == par) continue;
      if(i == ans[edges[{cur,par}]]) ++i;
      ans[edges[{cur,next}]] = i;
      ++i;
    }
  }
  
  for(auto &next : graph[cur]){
    if(next == par) continue;
    dfs(next,cur,r,graph,edges,ans);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> n >> k){
    vector<vector<int>> graph(n);
    vector<int> deg(n);
    map<pair<int,int>,int> edges;
    REP(i,n-1){
      int x,y; cin >> x >> y; --x, --y;
      graph[x].push_back(y);
      graph[y].push_back(x);
      ++deg[x];
      ++deg[y];
      edges[{x,y}] = i;
      edges[{y,x}] = i;
    }

    int lb=0, ub=n, mid;
    while(abs(lb-ub)>1){
      mid = (lb+ub)/2;

      if(count_if(ALL(deg), [&](int x){return x>mid;}) <= k){
	ub = mid;
      }else{
	lb = mid;
      }
    }

    int r = ub;
    cout << r << endl;

    vector<int> ans(n-1);
    dfs(0,-1,r,graph,edges,ans);

    join(cout, ALL(ans)); 
  }
  
  return 0;
}
