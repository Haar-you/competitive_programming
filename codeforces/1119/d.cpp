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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<LLI> s(n); cin >> s;
    int q; cin >> q;
    vector<LLI> l(q), r(q);
    vector<LLI> d(q); 
    REP(i,q){
      cin >> l[i] >> r[i];
      d[i] = r[i] - l[i];
    }

    sort(ALL(d));
    d.erase(unique(ALL(d)), d.end());

    sort(ALL(s));
    s.erase(unique(ALL(s)), s.end());

    n = s.size();
    vector<LLI> a(n, LLONG_MAX);
    REP(i,n-1) a[i] = s[i+1] - s[i];
    sort(ALL(a));

    map<LLI,LLI> m;
    
    LLI t = 0;
    auto it = a.begin();
    for(auto x : d){
      for(; it!=a.end(); ++it){
	if(*it <= x){
	  t += *it;
	}else{
	  break;
	}
      }
      
      m[x] = t + (x+1)*(a.end()-it);
    }
    
    vector<LLI> ans(q);
    REP(i,q) ans[i] = m[r[i]-l[i]];
    join(cout, ALL(ans));
  }
  
  return 0;
}
