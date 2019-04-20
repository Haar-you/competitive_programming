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

LLI dp[301][90010];
LLI dp2[301][90010];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){
    vector<int> a(N); cin >> a;
    sort(ALL(a));

    int sum = accumulate(ALL(a), 0);

    LLI ans = power(3,N,mod);

    fill_array(dp, 0);
    dp[0][0] = 1;

    fill_array(dp2, 0);
    dp2[0][0] = 1;

    REP(i,N){
      REP(j,sum){
	(dp[i+1][j] += dp[i][j]*2) %= mod;
	if(j+a[i] <= sum) (dp[i+1][j+a[i]] += dp[i][j]) %= mod;

	(dp2[i+1][j] += dp2[i][j]) %= mod;
	if(j+a[i] <= sum) (dp2[i+1][j+a[i]] += dp2[i][j]) %= mod;
      }
    }

    REPE(j,sum){
      if(j >= (sum+1)/2){
	ans -= dp[N][j] * 3;
	(ans += mod) %= mod;
      }
    }

    if(sum % 2 == 0){
      ans += dp2[N][sum/2] * 3;
      (ans += mod) %= mod;
    }

    cout << ans << endl;
  }
  
  return 0;
}
