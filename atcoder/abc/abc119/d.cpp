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
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}


LLI f(vector<LLI> &s, LLI x){
  auto itr = lower_bound(ALL(s), x);
	
  if(x > s.back()){
    return x - s.back();
  }else if(x < s.front()){
    return s.front() - x;
  }else{
    return min(abs((*itr)-x), abs((*(itr-1)-x)));
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int A,B,Q;
  while(cin >> A >> B >> Q){
    vector<LLI> s(A), t(B); cin >> s >> t;

    REP(i,Q){
      LLI x; cin >> x;

      LLI ans = 1e18;

      {
	auto itr = lower_bound(ALL(s), x);
	LLI temp = 0;
	
	if(x > s.back()){
	  temp = x - s.back() + f(t, s.back());
	}else if(x <= s.front()){
	  temp = s.front() - x + f(t, s.front());
	}else{
	  temp = min(abs((*itr)-x)+f(t,*itr), abs((*(itr-1))-x)+f(t,*(itr-1)));
	}
	chmin(ans, temp);
      }
      
      {
	auto itr = lower_bound(ALL(t), x);
	LLI temp = 0;
	
	if(x > t.back()){
	  temp = x - t.back() + f(s, t.back());
	}else if(x <= t.front()){
	  temp = t.front() - x + f(s, t.front());
	}else{
	  temp = min(abs((*itr)-x)+f(s,*itr), abs((*(itr-1))-x)+f(s,*(itr-1)));
	}
	chmin(ans, temp);
      }


      cout << ans << endl;
    }
    cerr << endl;
  }
  
  return 0;
}
