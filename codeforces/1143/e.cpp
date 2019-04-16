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

template <typename T> class SparseTable{
  using Op = function<T(T,T)>;
  Op f;
  vector<vector<T>> a;
  vector<int> log_table;
public:
  SparseTable(const vector<T> &v, const Op &f): f(f){
    int n = v.size();
    int logn = 0;
    while((1<<logn) <= n) ++logn;
    
    a = vector<vector<T>>(n, vector<T>(logn));
    REP(i,n) a[i][0] = v[i];
    FOR(j,1,logn) REP(i,n) a[i][j] = f(a[i][j-1], a[min(n-1, i+(1<<(j-1)))][j-1]);

    log_table = vector<int>(n+1);
    FOR(i,2,n+1) log_table[i] = log_table[i>>1] + 1;
  }
  
  T query(int s, int t){
    int k = log_table[t-s+1];
    return f(a[s][k], a[t-(1<<k)+1][k]);
  }
};


const int inf = INT_MAX;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m,q;
  while(cin >> n >> m >> q){
    vector<int> p(n); cin >> p;
    vector<int> a(m); cin >> a;

    for(auto &x : p) --x;
    for(auto &x : a) --x;

    vector<vector<int>> next(20, vector<int>(m));
    
    vector<int> r(n);
    REP(i,n) r[p[i]] = i;
    
    vector<int> b(n, inf);
    REV(i,m-1,0){
      next[0][i] = b[(r[a[i]]+1)%n];
      b[r[a[i]]] = i;
    }

    FOR(j,1,20){
      REP(i,m){
	next[j][i] = next[j-1][min(m-1,next[j-1][i])];
      }
    }

    vector<int> end(m);
    REP(i,m){
      int k = i;
      REP(j,20){
	if(((n-1)>>j) & 1){
	  k = next[j][min(m-1,k)];
	}
      }
      end[i] = k;
    }

    vector<bool> ans(q);

    SparseTable<int> st(end, [](int a, int b){return min(a,b);});
    
    REP(i,q){
      int l, r; cin >> l >> r; --l, --r;

      ans[i] = st.query(l,r) <= r;
    }
    
    join(cout, ALL(ans), "");
  }
  
  return 0;
}
