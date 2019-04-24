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

mt19937 r = mt19937(static_cast<unsigned int>(time(nullptr)));


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

const int mod = 1000003;

class interaction{
public:
  int k;
  vector<int> a;
  interaction(){
#ifdef DEBUG
    /*
    k = r() % 10 + 1;
    a = vector<int>(k+1);
    for(auto &x : a) x = r() % mod;
    dump(a);*/
    cin >> k;
    a = vector<int>(k+1); cin >> a;
#endif
  }

  int query(int x){
    cout << "? " << x << endl;
    int ret = 0;
#ifdef DEBUG
    REPE(i,k){
      (ret += a[i] * power(x,i,mod) % mod) %= mod;
    }
#else
    cin >> ret;
#endif

    return ret;
  }

  void answer(int x){
    cout << "! " << x << endl;
    
#ifdef DEBUG
    int t = 0;

    REPE(i,k){
      (t += a[i] * power(x,i,mod) % mod) %= mod;
    }

    dump(t);
#endif
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  interaction inter;

  vector<LLI> x(11);
  vector<LLI> y(11);
  
  FOR(i,0,11){
    x[i] = i;
    y[i] = inter.query(i);
  }

  dump(x);
  dump(y);

  vector<LLI> r(11);
  REPE(i,10){
    r[i] = 1;
    REPE(j,10) if(i!=j) (r[i] *= (x[i]-x[j]+mod)%mod) %= mod;
    r[i] = mod_inv(r[i],mod);
  }
  
  auto check =
    [&](int t){
      LLI ret = 0;
      
      REPE(i,10){
	LLI s = y[i];
	REPE(j,10) if(i!=j) (s *= (t-x[j]+mod)%mod) %= mod;
	(ret += s*r[i]%mod) %= mod;
      }

      return ret == 0;
    };
  
  REP(i,mod){
    if(check(i)){
      inter.answer(i);
      return 0;
    }
  }

  inter.answer(-1);
  
  return 0;
}
