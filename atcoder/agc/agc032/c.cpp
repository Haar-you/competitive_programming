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
    bool is_rev;
  };
  
private:
  int size;

  vector<vector<edge>> graph;
  vector<bool> visit;
  
  T dfs(int from, int to, T flow){
    if(from == to) return flow;
    visit[from] = true;

    for(auto &e : graph[from]){
      if(!visit[e.to] and e.cap > 0){
        T d = dfs(e.to, to, min(flow, e.cap));
	if(d > 0){
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  
public:  
  FordFulkerson(int size): size(size), graph(size), visit(size){}

  void add_edge(int from, int to, const T &cap){
    graph[from].push_back((edge){to, (int)graph[to].size(), cap, false});
    graph[to].push_back((edge){from, (int)graph[from].size()-1, 0, true});
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

  const vector<vector<edge>>& get_graph(){
    return graph;
  }
};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,M;
  while(cin >> N >> M){
    FordFulkerson<int,INT_MAX> g(N);
    vector<int> deg(N);
    REP(i,M){
      int a,b; cin >> a >> b; --a, --b;
      g.add_edge(a,b,1);
      g.add_edge(b,a,1);
      ++deg[a];
      ++deg[b];
    }

    // オイラーグラフの判定
    if(not all_of(ALL(deg), [](int x){return x%2==0;})){
      cout << "No" << endl;
      continue;
    }

    // 次数6以上が存在すれば、解は存在する。
    if(any_of(ALL(deg), [](int x){return x>=6;})){
      cout << "Yes" << endl;
      continue;
    }

    vector<int> deg4;
    REP(i,N) if(deg[i]==4) deg4.push_back(i);
    
    // 次数4以上が3つ以上存在すれば、解は存在する。
    if(deg4.size() >= 3){
      cout << "Yes" << endl;
      continue;
    }

    // 次数4が2つのみの場合、一方から他方へのパスで閉路を含まないものが2本であれば解は存在する。
    if(deg4.size() == 2){
      if(g.max_flow(deg4[0], deg4[1]) == 2){
	cout << "Yes" << endl;
	continue;
      }
    }
    
    cout << "No" << endl;
  }
  
  return 0;
}
