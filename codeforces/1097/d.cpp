#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second
#ifdef DEBUG
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T> ostream& operator<<(ostream &os, vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

vector<LLI> divisor_list(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(is_square(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}

vector<LLI> prime_factorize(LLI n){
  vector<LLI> res;
  for(LLI i=2LL; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);
      n/=i;
      --i;
    }
  }
  if(n!=1) res.push_back(n);
  return res;
}

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}

template <typename T> LLI mod_inv(T n, T p){return power(n,p-2,p);}

const LLI mod = 1e9+7;

LLI func(LLI p, LLI a, LLI k){
  vector<vector<LLI>> dp = vector<vector<LLI>>(a+1, vector<LLI>(k+1,0));

  REPE(i,a){
    dp[i][0] = power(p,(LLI)i,mod);
  }

  REP(i,k){
    REPE(j,a){
      LLI m = 0;
      REPE(d,j){
	(dp[j][i+1] += dp[d][i]) %= mod;
	++m;
      }
      (dp[j][i+1] *= mod_inv(m,mod)) %= mod;
    }
  }

  return dp[a][k];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,k; cin >> n >> k;

  auto pfs = prime_factorize(n);

  map<LLI,int> pcount;
  for(auto p : pfs) pcount[p]++;

  LLI ans = 1;

  ITR(it,pcount){
    LLI t = func(it->fst,it->snd,k);
    (ans *= t) %= mod;
  }

  cout << ans << endl;

  return 0;
}
