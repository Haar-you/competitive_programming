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


vector<bool> prime_table(int n){
  vector<bool> res(n+1, true);
  res[0] = res[1] = false;
  FOR(i,2,n) if(res[i]) for(int j=2*i; j<=n; j+=i) res[j] = false;
  return res;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  auto primes = prime_table(10000);

  int N;
  while(cin >> N){
    vector<int> a(N+1); cin >> a;
    reverse(ALL(a));

    vector<int> ans;

    int g = 0;
    for(auto x : a) g = gcd(g, abs(x));

    for(LLI i=2; i*i<=g; ++i){
      if(g % i == 0){
	ans.push_back(i);
	while(g % i == 0) g /= i;
      }
    }
    if(g != 1) ans.push_back(g);


    FORE(i,2,N){
      if(not primes[i]) continue;

      vector<int> b(i);

      REP(j,i) b[j] = a[j] % i;

      FORE(j,i,N){
	int t = j%(i-1);
	(b[t?t:i-1] += a[j]) %= i;
      }

      if(all_of(ALL(b), [&i](int x){return x == 0;})) ans.push_back(i);
    }

    sort(ALL(ans));
    ans.erase(unique(ALL(ans)), ans.end());
    
    
    join(cout, ALL(ans), "\n");
  }
  
  return 0;
}
