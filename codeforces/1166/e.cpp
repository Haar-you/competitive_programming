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

template <typename T> vector<pair<T,int>> group(const vector<T> &v){
  vector<pair<T,int>> ret;

  for(auto &x : v){
    if(ret.empty()) ret.push_back({x,1});
    else if(ret.back().fst == x) ++ret.back().snd;
    else ret.push_back({x,1});
  }

  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int m,n;
  while(cin >> m >> n){
    map<LLI,int> mp;

    vector<bitset<10000>> a(m);

    REP(i,m){
      int s; cin >> s;
      REP(j,s){
	int k; cin >> k;
	--k;
	a[i].set(k);
      }
    }

    bool ans = true;

    REP(i,m){
      REP(j,m){
	if((a[i] & a[j]).none()){
	  ans = false;
	}
      }
    }
    
    cout << (ans ? "possible" : "impossible") << endl;
  }
  
  return 0;
}
