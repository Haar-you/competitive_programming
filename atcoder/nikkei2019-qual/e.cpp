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
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m*n/gcd(m,n);}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename Iter> ostream& out_container(ostream &os, Iter first, Iter last){
  os << "{"; auto itr = first; while(itr != last){if(itr != first) os << ","; os << *itr; ++itr;} os << "}"; return os;
}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const deque<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const set<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const unordered_set<T> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const unordered_map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

template <typename Cost = int> class Edge{
public:
  int from,to;
  Cost cost;
  Edge() {}
  Edge(int to, Cost cost): to(to), cost(cost){}
  Edge(int from, int to, Cost cost): from(from), to(to), cost(cost){}

  Edge rev(){return Edge(to,from,cost);}
  
  static bool cmp_to_lt(const Edge &e1, const Edge &e2){return e1.to < e2.to;}
  static bool cmp_cost_lt(const Edge &e1, const Edge &e2){return e1.cost < e2.cost;}
  static bool cmp_to_gt(const Edge &e1, const Edge &e2){return e1.to > e2.to;}
  static bool cmp_cost_gt(const Edge &e1, const Edge &e2){return e1.cost > e2.cost;}
  friend ostream& operator<<(ostream &os, const Edge &e){
    os << "(FROM: " << e.from << "," << "TO: " << e.to << "," << "COST: " << e.cost << ")";
    return os;
  }
};

template <typename T> using Graph = vector<vector<Edge<T>>>;

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

int rec(Graph<LLI> &graph, map<pair<int,int>,int> &m, unordered_set<int> &s, LLI cost, int cur){
  for(auto &e : graph[cur]){
    int t = m[{e.from,e.to}];
    if(EXIST(s, t) || e.cost>cost) continue;
    s.insert(t);
    rec(graph,m,s,cost,e.to);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,M;
  while(cin >> N >> M){
    vector<LLI> X(N); cin >> X;
    vector<Edge<LLI>> es;
    Graph<LLI> graph(N);
    map<pair<int,int>,int> edge_num;
    REP(i,M){
      int a,b,y; cin >> a >> b >> y;
      --a, --b;
      es.push_back(Edge<LLI>(a,b,y));
      graph[a].push_back(Edge<LLI>(a,b,y));
      graph[b].push_back(Edge<LLI>(b,a,y));
      edge_num[{a,b}] = edge_num[{b,a}] = i;
    }

    sort(ALL(es),Edge<LLI>::cmp_cost_lt);

    UnionFind uf(N);
    vector<LLI> sum_nodes(X);
    vector<Edge<LLI>> cand;

    for(auto &e : es){
      int a = uf.root(e.from), b = uf.root(e.to);
      
      uf.merge(e.from, e.to);
      if(a != b) sum_nodes[uf.root(e.from)] = sum_nodes[a] + sum_nodes[b];

      if(sum_nodes[uf.root(e.from)] >= e.cost){
	cand.push_back(e);
      }
    }

    unordered_set<int> ans;
    reverse(ALL(cand));

    for(auto &e : cand){
      ans.insert(edge_num[{e.from, e.to}]);
      rec(graph,edge_num,ans,e.cost,e.from);
      rec(graph,edge_num,ans,e.cost,e.to);
    }

    cout << M-ans.size() << endl;
  }
  
  return 0;
}
