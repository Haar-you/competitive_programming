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
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

const LLI inf = 1e15;

template <typename T> class Dinic{
private:
  vector<vector<pair<int,T>>> graph;
  int size, s, t;
  vector<vector<T>> cap;
  vector<int> level;
  
  bool buildLevel(){
    fill(ALL(level), 0);
    level[s] = 1;
    deque<int> deq = {s};
    while(!deq.empty()){
      int cur = deq.front(); deq.pop_front();
      REP(i,size)
	if(level[i]==0 && cap[cur][i]>0){
	  level[i] = level[cur] + 1;
	  deq.push_back(i);
	}
    }
    return level[t] != 0;
  }
  void dfs(vector<int> &path, T &flow){
    if(path.empty()) return;
    int cur = path.back();
    if(cur == t){
      T f = inf;
      FOR(i,1,path.size()) f = min(f, cap[path[i-1]][path[i]]);
      FOR(i,1,path.size()){
	cap[path[i-1]][path[i]] -= f;
	cap[path[i]][path[i-1]] += f;
      }
      flow += f;
    }else{
      REP(i,size){
	if(cap[cur][i]>0 && level[i]>level[cur]){
	  path.push_back(i);
	  dfs(path, flow);
	  path.pop_back();
	}
      }
    }
  }
  T augment(){
    T f = 0;
    vector<int> path = {s};
    dfs(path, f);
    return f;
  }
  T loop(){
    T f = 0;
    while(buildLevel()) f += augment();
    return f;
  }

public:
  Dinic(vector<vector<pair<int,T>>> &_graph): graph(_graph), size(graph.size()) {}

  T query(int _s, int _t){
    cap = vector<vector<T>>(size, vector<T>(size, 0));
    level = vector<int>(size, 0);

    REP(i,size)
      for(auto &p : graph[i]){
	int j = p.first;
	T d = p.second;
	cap[i][j] += d;
      }

    s = _s;
    t = _t;

    return loop();
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,M;
  while(cin >> N >> M){
    vector<LLI> c(N-2); cin >> c;

    vector<vector<pair<int,LLI>>> graph(2*N);

    FORE(i,2,N-1){
      if(c[i-2] == -1){
	graph[0].push_back({2*i+1,inf});
	graph[2*i].push_back({1,inf});
      }else{
	graph[2*i].push_back({2*i+1,c[i-2]});
      }
    }
    
    REP(i,M){
      int a,b; cin >> a >> b;

      if(a == 1){
	graph[2].push_back({2*b,inf});
      }else if(b == N){
	graph[2*a+1].push_back({3,inf});
      }else{
	graph[2*a+1].push_back({2*b,inf});
      }
    }

    Dinic<LLI> dinic(graph);

    LLI ans = dinic.query(0,1);
    if(ans >= inf) cout << -1 << endl;
    else cout << ans << endl;
  }
  
  return 0;
}
