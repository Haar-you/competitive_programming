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

  int n;
  while(cin >> n){
    vector<LLI> a(n); cin >> a;
    sort(ALL(a));
    vector<LLI> even, odd;
    for(auto x : a){
      if(x % 2 == 0) even.push_back(x);
      else odd.push_back(x);
    }

    LLI ans = LLONG_MAX;
    {
      vector<LLI> e(even), o(odd);
      int p = 0;

      while(1){
	if(p==0){
	  if(not e.empty()) e.pop_back();
	  else break;
	}else{
	  if(not o.empty()) o.pop_back();
	  else break;
	}
	p = (p+1)%2;
      }
      chmin(ans, accumulate(ALL(e),0LL) + accumulate(ALL(o),0LL));
    }
    {
      vector<LLI> e(even), o(odd);
      int p = 1;

      while(1){
	if(p==0){
	  if(not e.empty()) e.pop_back();
	  else break;
	}else{
	  if(not o.empty()) o.pop_back();
	  else break;
	}
	p = (p+1)%2;
      }
      chmin(ans, accumulate(ALL(e),0LL) + accumulate(ALL(o),0LL));
    }

    cout << ans << endl;
  }
  
  return 0;
}
