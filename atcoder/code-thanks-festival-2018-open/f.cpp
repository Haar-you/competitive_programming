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

template <typename Cost = int> class Edge{
public:
  int from,to;
  Cost cost;
  Edge() {}
  Edge(int to, Cost cost): to(to), cost(cost){}
  Edge(int from, int to, Cost cost): from(from), to(to), cost(cost){}

  static bool cmp_to_lt(const Edge &e1, const Edge &e2){return e1.to < e2.to;}
  static bool cmp_cost_lt(const Edge &e1, const Edge &e2){return e1.cost < e2.cost;}
  static bool cmp_to_gt(const Edge &e1, const Edge &e2){return e1.to > e2.to;}
  static bool cmp_cost_gt(const Edge &e1, const Edge &e2){return e1.cost > e2.cost;}
  friend ostream& operator<<(ostream &os, const Edge &e){
    os << "(FROM: " << e.from << "," << "TO: " << e.to << "," << "COST: " << e.cost << ")";
    return os;
  }
};

template <typename T> using Tree = vector<vector<Edge<T>>>;

int size[300];
bool visit[300];
int depth[300];

int N,M,K;
int root;

int rec_pre(const Tree<int> &tree, int cur, int d){
  size[cur] = 1;
  depth[cur] = d;
  for(auto &e : tree[cur]) size[cur] += rec_pre(tree, e.to, d+1);
  return size[cur];
}

void get_not_visited_nodes(const Tree<int> &tree, const int i, int cur, vector<int> &vec){
  if(cur == i || visit[cur]) return;
  vec.push_back(depth[cur]);
  for(auto &e : tree[cur]) get_not_visited_nodes(tree, i, e.to, vec);
}

void dfs(const Tree<int> &tree, int cur){
  if(visit[cur]) return;
  visit[cur] = true;

  for(auto &e : tree[cur]) dfs(tree, e.to);
}

bool solve(const Tree<int> &tree, vector<int> &ans, int &rest_op, int &rest_node){
  if(rest_op <= 0) return false;

  REP(i,N){
    if(visit[i]) continue;

    if(rest_op >= depth[i]){
      vector<int> vec;
      get_not_visited_nodes(tree, i, root, vec);
      if(vec.size() < rest_node-1) continue;
      sort(ALL(vec));

      int min_sum=0, max_sum=0;
      REP(j,rest_node-1) min_sum += vec[j];
      REP(j,rest_node-1) max_sum += vec[vec.size()-1-j];
      if(min_sum <= rest_op-depth[i] and rest_op-depth[i] <= max_sum){
	ans.push_back(i+1);
	rest_op -= depth[i];
	--rest_node;
	dfs(tree, i);
	
	return true;
      }
    }
  }

  return false;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> N >> M >> K){
    vector<int> p(N); cin >> p;

    Tree<int> tree(N);
   
    REP(i,N){
      if(p[i] == 0){
	root = i;
      }else{
	tree[p[i]-1].push_back(Edge<int>(p[i]-1,i,1));
      }
    }

    fill_array(size, 0);
    fill_array(depth, 0);
    rec_pre(tree, root, 1);

    fill_array(visit, false);
    
    vector<int> ans;
    int rest_op = K;
    int rest_node = M;

    while(solve(tree,ans,rest_op,rest_node)){}

    if(ans.size() == M){
      join(cout, ALL(ans));
    }else{
      cout << -1 << endl;
    }
  }
  
  return 0;
}
