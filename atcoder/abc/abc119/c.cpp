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

LLI N,A,B,C;

LLI f(vector<LLI> &l){
  LLI ret = 1e9;
  int n = l.size();
  REP(i,n){
    FOR(j,i+1,n){
      FOR(k,j+1,n){
	chmin(ret, abs(l[i]-A) + abs(l[j]-B) + abs(l[k]-C));
	chmin(ret, abs(l[i]-A) + abs(l[j]-C) + abs(l[k]-B));
	chmin(ret, abs(l[i]-B) + abs(l[j]-A) + abs(l[k]-C));
	chmin(ret, abs(l[i]-B) + abs(l[j]-C) + abs(l[k]-A));
	chmin(ret, abs(l[i]-C) + abs(l[j]-B) + abs(l[k]-A));
	chmin(ret, abs(l[i]-C) + abs(l[j]-A) + abs(l[k]-B));
      }
    }
  }
  return ret;
}

map<vector<LLI>, LLI> dp;

LLI rec(vector<LLI> l){
  if(EXIST(dp,l)) return dp[l];
  
  LLI ret = 1e9;
  
  if(l.size() > 3){
    REP(i,l.size()){
      FOR(j,i+1,l.size()){
	vector<LLI> t;

	REP(k,l.size()){
	  if(k==i) t.push_back(l[i]+l[j]);
	  else if(k!=j) t.push_back(l[k]);
	}
	
	sort(ALL(t));
	
	chmin(ret, rec(t)+10);
      }
    }
  }

  chmin(ret, f(l));
  
  return dp[l] = ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  while(cin >> N >> A >> B >> C){
    vector<LLI> l(N); cin >> l;
    sort(ALL(l));
    
    LLI ans = rec(l);
    cout << ans << endl;
  }
  
  return 0;
}
