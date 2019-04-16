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

void rec(const vector<vector<int>> &tree, const vector<int> &c, int cur, vector<int> &ans){
  bool t = c[cur];

  for(auto next : tree[cur]){
    t = t && c[next];
    rec(tree, c, next, ans);
  }

  if(t) ans.push_back(cur);
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){

    vector<vector<int>> tree(n);
    vector<int> c(n);
    int root;
      
    REP(i,n){
      int p; cin >> p >> c[i];

      if(p!=-1){
	tree[p-1].push_back(i);
      }else{
	root = i;
      }
    }

    vector<int> ans;
    rec(tree, c, root, ans);
    
    sort(ALL(ans));
    for(auto &x : ans) ++x;

    if(ans.size()){
      join(cout, ALL(ans));
    }else{
      cout << -1 << endl;
    }
  }
  
  return 0;
}
