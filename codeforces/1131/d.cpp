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

class TopologicalSort{
public:
  static bool tsort_priority_queue(vector<vector<int>> graph, vector<int> &ret){
    int n = graph.size();
    vector<int> indeg(n);
    REP(i,n){
      for(auto j : graph[i]){
	++indeg[j];
      }
    }
    priority_queue<int,vector<int>,greater<int>> q;
    REV(i,n-1,0){
      if(indeg[i]==0) q.push(i);
    }

    while(!q.empty()){
      int cur = q.top(); q.pop();
      ret.push_back(cur);
      for(auto next : graph[cur]){
	--indeg[next];
	if(indeg[next]==0){
	  q.push(next);
	}
      }
    }
    
    return ret.size()==n;
  }
};

class UnionFind{
  vector<int> _parent, _depth, _size;
public:
  UnionFind(int n): _parent(n), _depth(n,1), _size(n,1){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else return _parent[i] = root(_parent[i]);
  }
  bool same(int i, int j){return root(i) == root(j);}
  void merge(int i, int j){
    int ri = root(i), rj = root(j);
    if(ri != rj){
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri];
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
      }
    }
  }
  int size(int i){return _size[root(i)];}
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m;
  while(cin >> n >> m){
    vector<string> a(n); cin >> a;

    vector<vector<int>> graph(n+m);

    UnionFind uf(n+m);
    REP(i,n){
      REP(j,m){
	if(a[i][j] == '=') uf.merge(i,n+j);
      }
    }

    bool no_ans = false;

    vector<int> in(n+m);
    
    REP(i,n){
      REP(j,m){
	if(a[i][j] != '=' && uf.same(i,n+j)){
	  no_ans = true;
	}
	if(a[i][j] == '<'){
	  graph[uf.root(i)].push_back(uf.root(n+j));
	  ++in[uf.root(n+j)];
	}else if(a[i][j] == '>'){
	  graph[uf.root(n+j)].push_back(uf.root(i));
	  ++in[uf.root(i)];
	}
      }
    }

    if(no_ans){
      cout << "No" << endl;
      continue;
    }

    vector<int> ret;
    if(!TopologicalSort::tsort_priority_queue(graph, ret)){
      cout << "No" << endl;
      continue;      
    }

    vector<int> d(n+m);
    vector<bool> visit(n+m);
    deque<int> dq;

    REP(i,n+m) if(in[i] == 0) dq.push_back(i);

    while(!dq.empty()){
      auto cur = dq.front(); dq.pop_front();

      if(visit[cur]) continue;
      
      if(in[cur] != 0){
	continue;
      }

      visit[cur] = true;

      for(auto next : graph[cur]){
	--in[next];
	chmax(d[next], d[cur]+1);
	dq.push_back(next);
      }
    }

    vector<int> x(n), y(m);

    REP(i,n) x[i] = d[uf.root(i)]+1;
    REP(i,m) y[i] = d[uf.root(n+i)]+1;

    cout << "Yes" << endl;
    join(cout, ALL(x));
    join(cout, ALL(y));    
  }
  
  return 0;
}
