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
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())

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
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}


LLI power(LLI n, LLI p, LLI m){
  LLI ret = 1;
  while(p>0){
    if(p&1) (ret *= n) %= m;
    (n *= n) %= m;
    p /= 2;
  }
  return ret;
}

LLI mod_inv(LLI n, LLI p){return power(n,p-2,p);}

template <LLI mod> class Combination{
public:
  vector<LLI> facto = {1};
  vector<LLI> ifacto = {1};

  LLI factorial(LLI i){
    if(i < 0) throw exception();
    if(facto.size() <= i) facto.resize(i+1, -1);
    if(i == 0) return facto[0] = 1;
    LLI j = i;
    for(;j>=0;--j) if(facto[j] != -1) break;
    for(LLI k=j+1; k<=i; ++k) (facto[k] = facto[k-1] * k) %= mod;
    return facto[i];
  }

  LLI factorial_inverse(LLI i){
    if(i < 0) throw exception();
    if(ifacto.size() <= i) ifacto.resize(i+1, -1);
    if(ifacto[i] != -1) return ifacto[i];
    return ifacto[i] = mod_inv(factorial(i), mod);
  }

  LLI P(LLI n, LLI k){
    if(n < k or n < 0 or k < 0) return 0;
    return (factorial(n) * factorial_inverse(n-k)) % mod;
  }

  LLI C(LLI n, LLI k){
    if(n < k or n < 0 or k < 0) return 0;
    return (P(n,k) * factorial_inverse(k)) % mod;
  }

  LLI H(LLI n, LLI k){
    return C(n+k-1, k);
  }
};


const LLI mod = 1e9+7;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  Combination<mod> com;

  LLI N,M,K;
  while(cin >> N >> M >> K){

    LLI ans = 0;

    {
      LLI t = 0;
      FOR(i,1,N){
	(t += (N-i)*M*M*i%mod) %= mod;
      }
      (ans += t * com.C(M*N-2,K-2) % mod) %= mod;
    }

    {
      LLI t = 0;
      FOR(i,1,M){
	(t += (M-i)*N*N*i%mod) %= mod;
      }
      (ans += t * com.C(M*N-2,K-2) % mod) %= mod;
    }

    cout << ans << endl;
  }
  
  return 0;
}
