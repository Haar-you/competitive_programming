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

const LLI mod = 1e9+7;

LLI power(LLI n, LLI p, LLI m){
  LLI ret = 1;
  while(p>0){
    if(p&1) (ret *= n) %= m;
    (n *= n) %= m;
    p /= 2;
  }
  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){
    vector<int> A(N); cin >> A;

    vector<int> s(N+1);
    REP(i,N) s[i+1] = s[i] ^ A[i];

    vector<int> zero(N+2);
    REPE(i,N) zero[i+1] = zero[i] + (s[i] == 0 ? 1 : 0);

    map<int, vector<int>> ps;
    REPE(i,N){
      if(s[i] != 0) ps[s[i]].push_back(i);
    }

    LLI ans = 0;

    if(s.back() == 0){
      {
	int c0 = count(ALL(s), 0);
	(ans += power(2,c0-2,mod)) %= mod;
      }
      
      for(auto &kv : ps){
	auto &v = kv.snd;

        LLI c0 = 1, cx = 1;

	FOR(i,1,(int)v.size()){
	  (c0 += (zero[v[i]+1]-zero[v[i-1]])*cx%mod) %= mod;
	  (cx += c0) %= mod;
	}
	(ans += cx) %= mod;
      }
      
    }else{
      int x = s.back();

      LLI c0 = 1, cx = 0;

      FOR(i,1,N){
	if(s[i] == 0){
	  (c0 += cx) %= mod;
	}else if(s[i] == x){
	  (cx += c0) %= mod;
	}
      }
      
      ans = c0;
    }

    cout << ans << endl;
  }
  
  return 0;
}
