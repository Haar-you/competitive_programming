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

LLI mod_inv(LLI n, LLI p){return power(n,p-2,p);}

bool is_prime[100010];

vector<int> mobius(int n){
  vector<int> ret(n+1);
  vector<int> ps;
  ret[1] = 1;
  FORE(i,2,n){
    if(is_prime[i]){
      ps.push_back(i);
      ret[i] = -1;
    }
    for(auto &j : ps){
      if(i*j > n) break;
      if(i % j == 0) ret[i*j] = 0;
      else ret[i*j] = ret[i] * ret[j];
    }
  }
  
  return ret;
}

void solve(LLI m){
  auto mob = mobius(m);
  dump(mob);

  LLI ans = 1;

  FORE(i,2,m){
    LLI t = m/i;
    (ans += ((t*mod_inv(m-t,mod)%mod)*(-mob[i]) + mod)%mod) %= mod;
  }
  
  cout << ans << endl;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  {
    // 素数判定
    fill_array(is_prime, true);
    is_prime[0] = is_prime[1] = false;
    FORE(i,2,100000) if(is_prime[i]) for(int j=2*i; j<=100000; j+=i) is_prime[j] = false;
  }

  LLI m;
  while(cin >> m){
    solve(m);
  }
  
  return 0;
}



/*
vector<int> primes[100010];
vector<int> factors[100010];

LLI count_cop(int n, int m){
  LLI ret = 0;
  int k = primes[n].size();
  FOR(i,1,1<<k){
    int d = 1;
    REP(j,k) if(i&(1<<j)) d *= primes[n][j];
    ret += (m/d) * (__builtin_parity(i) ? 1 : -1);
  }
  ret = m - ret;
  return ret;
}

void solve(LLI m){
  vector<LLI> dp(m+1);

  dp[1] = 1;
  FORE(i,2,m){
    LLI t = 1;
    for(auto y : factors[i]){
      LLI c = count_cop(i/y,m/y);
      t += dp[y] * c % mod * mod_inv(m,mod) % mod;
    }
    // 両辺にdp[i]が来るので、移行して整理すると dp[i] = (m/(m-(m/i))) * (~~~)になる。
    dp[i] = t * m % mod * mod_inv(m-(m/i),mod) % mod;
  }

  LLI ans = 0;
  FORE(i,1,m) (ans += dp[i] * mod_inv(m,mod) % mod) %= mod;
  cout << ans << endl;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  {
    // 素数判定
    fill_array(is_prime, true);
    is_prime[0] = is_prime[1] = false;
    FORE(i,2,100000) if(is_prime[i]) for(int j=2*i; j<=100000; j+=i) is_prime[j] = false;

    // 素数列挙
    REPE(i,100000) if(is_prime[i]) for(int j=i; j<=100000; j+=i) primes[j].push_back(i);

    // 約数列挙
    FOR(i,1,100000) for(int j=i*2; j<=100000; j+=i) factors[j].push_back(i);
  }

  LLI m;
  while(cin >> m){
    solve(m);
  }
  
  return 0;
}
*/
