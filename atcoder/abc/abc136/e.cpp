#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

// 二乗判定
template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

// 約数列挙
vector<LLI> divisor_list(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(is_square(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,k;
  while(cin >> n >> k){
    vector<LLI> a(n); cin >> a;
    sort(ALL(a));

    LLI s = accumulate(ALL(a), 0LL);

    auto divs = divisor_list(s);

    LLI ans = 0;

    for(auto d : divs){
      vector<LLI> b(n);
      REP(i,n) b[i] = a[i] % d;
      sort(ALL(b));

      LLI s = 0;
      LLI t = d * n - accumulate(ALL(b), 0LL);

      bool yes = false;

      if(s <= k and t <= k and (s-t)%d == 0){
        yes = true;
      }
      
      REP(i,n){
        s += b[i];
        t -= (d-b[i]);
        
        if(s <= k and t <= k and (s-t)%d == 0){
          yes = true;
        }
      }

      if(yes){
        chmax(ans, d);
      }
    }

    cout << ans << endl;
  }
  
  return 0;
}
