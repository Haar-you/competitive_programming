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

  int N,Q;
  string s;
  while(cin >> N >> Q >> s){
    vector<char> t(Q), d(Q);
    REP(i,Q) cin >> t[i] >> d[i];

    int ans = N;
    
    {
      auto check =
	[&](int x){
	  --x;
	  REP(i,Q){
	    if(s[x] == t[i]){
	      if(d[i] == 'R') ++x;
	      else --x;
	    }
	    if(x<0) return true;
	  }
	  return false;
	};
      
      int lb=0, ub=N+1, mid;

      while(abs(lb-ub)>1){
	mid = (lb+ub)/2;

	if(check(mid)){
	  lb = mid;
	}else{
	  ub = mid;
	}
      }
      ans -= lb;
    }

    {
      auto check =
	[&](int x){
	  --x;
	  REP(i,Q){
	    if(s[x] == t[i]){
	      if(d[i] == 'R') ++x;
	      else --x;
	    }
	    if(x>=N) return true;
	  }
	  return false;
	};

      int lb=0, ub=N+1, mid;
      while(abs(lb-ub)>1){
	mid = (lb+ub)/2;

	if(check(mid)){
	  ub = mid;
	}else{
	  lb = mid;
	}
      }
      ans -= (N-lb);
    }
    cout << ans << endl;
  }
  
  return 0;
}
