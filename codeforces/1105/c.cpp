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
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
#define pln(x) cout << (x) << endl
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename Iter> ostream& out_container(ostream &os, Iter first, Iter last){
  os << "{"; auto itr = first; while(itr != last){if(itr != first) os << ","; os << *itr; ++itr;} os << "}"; return os;
}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const deque<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const set<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const unordered_set<T> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const unordered_map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

const LLI mod = 1e9+7;


template <int M> class mod_int_64{
public:
  int64_t val;
  mod_int_64(): val(0){}
  mod_int_64(int64_t n): val(n){}
  mod_int_64(int32_t n): val(n){}
  
  const mod_int_64 operator+(const mod_int_64 &a) const {return mod_int_64((val+a.val)%M);}
  const mod_int_64 operator-(const mod_int_64 &a) const {return mod_int_64((val-a.val+M)%M);}
  const mod_int_64 operator*(const mod_int_64 &a) const {return mod_int_64((val*a.val)%M);}
  const mod_int_64 operator/(const mod_int_64 &a) const {return mod_int_64((val*mod_int_64::mod_inv(a))%M);}
  
  const mod_int_64& operator=(const mod_int_64 &a){val = a.val; return *this;}
  const mod_int_64& operator+=(const mod_int_64 &a){(val += a.val) %= M; return *this;}
  const mod_int_64& operator-=(const mod_int_64 &a){((val -= a.val) += M) %= M; return *this;}
  const mod_int_64& operator*=(const mod_int_64 &a){(val *= a.val) %= M; return *this;}
  const mod_int_64& operator/=(const mod_int_64 &a){(val *= mod_int_64::mod_inv(a)) %= M; return *this;}

  const bool operator==(const mod_int_64 &a) const {return val==a.val;}

  static mod_int_64 power(const mod_int_64 &a, const int64_t p){
    if(p == 0) return 1;
    if(p == 1) return a;
    mod_int_64 t = mod_int_64::power(a, p/2);
    return t*t*(p%2?a:1);
  }

  static mod_int_64 mod_inv(const mod_int_64 &a){
    return mod_int_64::power(a,M-2);
  }
};

template <int M> istream& operator>>(istream &is, mod_int_64<M> &a){is >> a.val; return is;}
template <int M> ostream& operator<<(ostream &os, const mod_int_64<M> &a){ os << a.val; return os;}

using mint = mod_int_64<mod>;


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,l,r;

  while(cin >> n >> l >> r){
    vector<vector<mint>> dp(n+1, vector<mint>(3));

    mint count_mod[3] = {r/3 - (l-1)/3, (r+2)/3 - (l+1)/3,(r+1)/3 - l/3};

    dp[0][0] = 1;

    REP(i,n){
      REP(j,3){
	REP(k,3){
	  REP(l,3){
	    if((k+l)%3==j)
	      dp[i+1][j] += dp[i][k]*count_mod[l];
	  }
	}
      }
    }

    pln(dp[n][0]);
  }
  
  return 0;
}
