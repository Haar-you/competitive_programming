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

int dp_r[303000];
int dp_b[303000];

int cr, cb;

int rec(int cur, int par, const vector<vector<int>> &tree, const vector<int> &a){
  if(a[cur] == 1) dp_r[cur] = 1;
  if(a[cur] == 2) dp_b[cur] = 1;

  int ret = 0;
  
  for(auto next : tree[cur]){
    if(next == par) continue;

    ret += rec(next, cur, tree, a);

    if((dp_r[next] == cr && dp_b[next] == 0) || (dp_r[next] == 0 && dp_b[next] == cb)) ++ret;
    
    dp_r[cur] += dp_r[next];
    dp_b[cur] += dp_b[next];
  }

  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> a(n); cin >> a;
    vector<vector<int>> tree(n);
    REP(i,n-1){
      int u,v; cin >> u >> v; --u, --v;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }

    cr = count(ALL(a), 1);
    cb = count(ALL(a), 2);

    fill_array(dp_b, 0);
    fill_array(dp_r, 0);

    int ans = rec(0, -1, tree, a);

    cout << ans << endl;
  }
  
  return 0;
}
