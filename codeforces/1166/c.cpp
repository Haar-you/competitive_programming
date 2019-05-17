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
#define popcount __builtin_popcount

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
    vector<LLI> a(n); cin >> a;

    vector<LLI> pos, neg;

    REP(i,n){
      if(a[i] >= 0) pos.push_back(a[i]);
      else neg.push_back(-a[i]);
    }

    sort(ALL(pos));
    sort(ALL(neg));

    dump(pos);
    dump(neg);

    LLI ans = 0;

    for(auto x : pos){
      int t = upper_bound(ALL(pos), 2*x) - upper_bound(ALL(pos), x);
      //dump(t);
      ans += t;
    }

    for(auto y : neg){
      int t = upper_bound(ALL(neg), 2*y) - upper_bound(ALL(neg), y);
      //dump(t);
      ans += t;
    }

    for(auto x : neg){
      int t = lower_bound(ALL(pos), x) - lower_bound(ALL(pos), (x+1)/2);
      //dump(t);
      ans += t;
    }

    for(auto y : pos){
      int t = upper_bound(ALL(neg), y) - lower_bound(ALL(neg), (y+1)/2);
      //dump(t);
      ans += t;
    }

    cout << ans << endl;
  }
  
  return 0;
}
