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

const LLI mod = 998244353;


LLI power(LLI n, LLI p, LLI m){
  LLI ret = 1;
  while(p>0){
    if(p&1) (ret *= n) %= m;
    (n *= n) %= m;
    p /= 2;
  }
  return ret;
}

template <typename T> vector<pair<T,int>> group(const vector<T> &vec){
  vector<pair<T,int>> ret;
  for(auto &x : vec){
    if(ret.empty()) ret.push_back({x,1});
    else{
      if(ret.back().fst == x) ++ret.back().snd;
      else ret.push_back({x,1});
    }
  }
  return ret;
}

LLI dp1[200010];
LLI dp2[200010];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,k;
  while(cin >> n >> k){
    vector<int> a(n); cin >> a;

    fill_array(dp1,0);
    fill_array(dp2,0);
    dp1[0] = 1;
    REP(i,200000){
      (dp1[i+1] = dp2[i] + dp1[i]*(k-2)%mod) %= mod;
      dp2[i+1] = dp1[i]*(k-1)%mod;
    }

    vector<int> a1, a2;
    REP(i,n){
      if(i%2) a1.push_back(a[i]);
      else a2.push_back(a[i]);
    }

    LLI ans = 1;

    REP(i,a1.size()-1){
      if(a1[i]!=-1 and a1[i]==a1[i+1]) ans = 0;
    }

    REP(i,a2.size()-1){
      if(a2[i]!=-1 and a2[i]==a2[i+1]) ans = 0;
    }

    auto g1 = group(a1);

    if(g1.size()==1){
      if(g1[0].fst == -1) (ans *= power(k-1,g1[0].snd-1,mod) * k) %= mod;
    }else{
      if(g1.front().fst == -1) (ans *= power(k-1,g1.front().snd,mod)) %= mod;
      if(g1.back().fst == -1) (ans *= power(k-1,g1.back().snd,mod)) %= mod;

      FOR(i,1,g1.size()-1){
	if(g1[i].fst == -1){
	  if(g1[i-1].fst == g1[i+1].fst) (ans *= dp2[g1[i].snd]) %= mod;
	  else (ans *= dp1[g1[i].snd]) %= mod;
	}
      }
    }
    
    auto g2 = group(a2);

    if(g2.size()==1){
      if(g2[0].fst == -1) (ans *= power(k-1,g2[0].snd-1,mod) * k) %= mod;
    }else{
      if(g2.front().fst == -1) (ans *= power(k-1,g2.front().snd,mod)) %= mod;
      if(g2.back().fst == -1) (ans *= power(k-1,g2.back().snd,mod)) %= mod;

      FOR(i,1,g2.size()-1){
	if(g2[i].fst == -1){
	  if(g2[i-1].fst == g2[i+1].fst) (ans *= dp2[g2[i].snd]) %= mod;
	  else (ans *= dp1[g2[i].snd]) %= mod;
	}
      }
    }

    cout << ans << endl;
  }
  
  return 0;
}
