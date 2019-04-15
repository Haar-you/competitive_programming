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


int dfs(int cur, const vector<vector<int>> &tree, const vector<int> &m){
  if(tree[cur].size() == 0) return 1;
  if(m[cur] == 1){ //max
    int ret = INT_MAX;
    for(auto next : tree[cur]){
      chmin(ret, dfs(next, tree, m));
    }
    return ret;
  }else{ //min
    int ret = 0;
    for(auto next : tree[cur]){
      ret += dfs(next, tree, m);
    }
    return ret;
  }
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){
    vector<int> m(N); cin >> m;
    vector<vector<int>> tree(N);

    REP(i,N-1){
      int p; cin >> p;
      tree[p-1].push_back(i+1);
    }

    int res = dfs(0, tree, m);
    int leaves = 0;
    REP(i,N) if(tree[i].size() == 0) ++leaves;

    int ans = leaves - res + 1;
    
    cout << ans << endl;
  }
  
  return 0;
}
