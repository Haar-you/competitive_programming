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


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,Q;

  while(cin >> N >> Q){
    vector<LLI> a(N); cin >> a;
    vector<LLI> xs(Q); cin >> xs;

    vector<LLI> sum_odd(N+2);
    vector<LLI> sum_even(N+2);

    REP(i,N) sum_even[i+1] += sum_even[i] + (i%2==1?a[i]:0);
    REP(i,N) sum_odd[i+1] += sum_odd[i] + (i%2==0?a[i]:0);

    vector<LLI> sum(N+1);
    REP(i,N) sum[i+1] += sum[i] + a[i];

    for(auto x : xs){
      auto f = [&](LLI k){return abs(a[N-(k+1)/2-1]-x) < abs(a[N-k-1]-x);};

      int lb=0, ub=N, mid;
      while(abs(lb-ub) > 1){
	mid = (lb+ub)/2;

	if(f(mid)){
	  ub = mid;
	}else{
	  lb = mid;
	}
      }

      int t = ub;
      
      LLI ans = sum[N]-sum[N-(t+1)/2];
      if(N%2==0) ans += sum_even[N-t] - sum_even[0];
      else ans += sum_odd[N-t] - sum_odd[0];
	
      cout << ans << endl;
    }
  }
  
  return 0;
}
