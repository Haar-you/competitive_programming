#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

class Undirected_eulerian_path{
  int n; // node count
  int edges = 0; // edge count
  vector<unordered_map<int,int>> graph;
  vector<int> degree;

  void del(int i, int j){
    if(graph[i][j] == 1) graph[i].erase(j);
    else --graph[i][j];

    if(graph[j][i] == 1) graph[j].erase(i);
    else --graph[j][i];
  }

  void dfs(int cur, deque<int> &path){
    if(not graph[cur].empty()){
      int next = graph[cur].begin()->fst;
      del(cur, next);
      dfs(next, path);
    }

    while(not graph[cur].empty()){
      int next = graph[cur].begin()->fst;
      del(cur, next);
      deque<int> temp;
      dfs(next, temp);
      for(auto x : temp) path.push_back(x);
    }

    path.push_back(cur);
  }

public:
  Undirected_eulerian_path(int n): n(n), graph(n), degree(n){}

  void add(int i, int j){
    ++graph[i][j];
    ++graph[j][i];

    ++degree[i];
    ++degree[j];

    ++edges;
  }

  bool construct(vector<int> &ret){
    int odd = 0;
    int start = 0;
    REP(i,n){
      if(degree[i]%2==1){
	++odd;
	start = i;
      }
    }

    if(odd != 0 and odd != 2) return false;

    deque<int> temp;
    dfs(start, temp);

    ret = vector<int>(temp.begin(), temp.end());

    return (int)ret.size() == edges+1;
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> b(n-1), c(n-1); cin >> b >> c;

    bool no = false;

    REP(i,n-1){
      if(b[i] > c[i]){
	no = true;
	break;
      }
    }

    vector<int> ans;

    if(!no){
      vector<int> v;
      for(auto x : b) v.push_back(x);
      for(auto x : c) v.push_back(x);
      sort(ALL(v));
      v.erase(unique(ALL(v)), v.end());

      int k = v.size();
      Undirected_eulerian_path ep(k);
    
      REP(i,n-1){
	int x = lower_bound(ALL(v), b[i]) - v.begin();
	int y = lower_bound(ALL(v), c[i]) - v.begin();

	ep.add(x,y);
      }

      if(ep.construct(ans)){
	for(auto &x : ans) x = v[x];
      }else{
	no = true;
      }
    }
    
    if(no){
      cout << -1 << endl;
    }else{
      join(cout, ALL(ans));
    }
  }
  
  return 0;
}
