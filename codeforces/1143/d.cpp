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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n, k, a, b;
  while(cin >> n >> k >> a >> b){
    LLI ans_min = LLONG_MAX;
    LLI ans_max = 0;

    vector<LLI> S = {a+1,k+1-a};
    vector<LLI> T = {b+1,k+1-b};
    vector<LLI> L;
    
    for(auto s : S){
      for(auto t : T){
	if(s < t){
	  L.push_back(t-s);
	}
	
	if(t <= s and n*k-(s-t) != 0){
	  L.push_back(n*k-(s-t));
	}

	FOR(i,1,n){
	  if(i*k+t-s != 0) L.push_back(i*k+t-s);
	}
      }
    }

    for(auto l : L){
      LLI p = (n*k) / gcd(l,n*k);
      chmax(ans_max, p);
      chmin(ans_min, p);
    }

    cout << ans_min << " " << ans_max << endl;
  }
  
  return 0;
}
