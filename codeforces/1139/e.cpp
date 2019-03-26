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


template <typename T, T INF> class FordFulkerson{ 
public:
  struct edge{
    int to, rev;
    T cap;
  };

  int size;

  vector<vector<edge>> graph;
  vector<bool> visit;
  
  FordFulkerson(int size): size(size), graph(size), visit(size){}

  void add_edge(int from, int to, const T &cap){
    graph[from].push_back((edge){to, (int)graph[to].size(), cap});
    graph[to].push_back((edge){from, (int)graph[from].size()-1, 0});
  }

  T dfs(int from, int to, T flow){
    if(from == to) return flow;
    visit[from] = true;

    for(auto &e : graph[from]){
      if(!visit[e.to] and e.cap > 0){
	int d = dfs(e.to, to, min(flow, e.cap));
	if(d > 0){
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  
  T max_flow(int s, int t){
    T ret = 0;

    while(1){
      visit.assign(size,false);
      T flow = dfs(s,t,INF);
      if(flow == 0) return ret;
      ret += flow;
    }
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m;
  while(cin >> n >> m){
    vector<int> p(n), c(n); cin >> p >> c;
    int d; cin >> d;
    vector<int> k(d); cin >> k;


    vector<int> ans(d);

    int s = 0, t = 5000+m+1;
    FordFulkerson<int, INT_MAX> ff(5000+m+2);

    FORE(i,1,m) ff.add_edge(s,i,1);

    REP(i,n){
      if(find(ALL(k), i+1) == k.end()){
	ff.add_edge(c[i],p[i]+m+1,1);
      }
    }

    reverse(ALL(k));

    ff.add_edge(m+1,t,1);

    int x = 0;
    REP(i,d){
      while(ff.max_flow(s,t)){ // 前回との流量の差分は0,1のどちらかなので、1になるまで繰り返す。
	++x;
	ff.add_edge(x+m+1,t,1);
      }
      ans[i] = x;
      ff.add_edge(c[k[i]-1], p[k[i]-1]+m+1, 1);
    }

    reverse(ALL(ans));

    join(cout, ALL(ans), "\n");
  }
  
  return 0;
}
