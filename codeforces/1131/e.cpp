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

LLI samelen[26];
bool exist[26];

vector<pair<char,int>> group(string s){
  vector<pair<char,int>> ret;

  for(auto c : s){
    if(ret.empty()){
      ret.push_back({c,1});
    }else{
      if(ret.back().fst == c){
	++ret.back().snd;
      }else{
	ret.push_back({c,1});
      }
    }
  }
  
  return ret;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<string> p(n); cin >> p;

    fill_array(samelen, 0);
    fill_array(exist, false);

    {
      auto g = group(p[0]);
      for(auto &pr : g) chmax(samelen[pr.fst-'a'], pr.snd);
      REP(i,p[0].size()) exist[p[0][i]-'a'] = true;
    }
    
    FOR(i,1,n){
      auto g = group(p[i]);

      LLI len[26];
      fill_array(len, 0);

      if(g.size() == 1){
	auto &g0 = g[0];

	len[g0.fst-'a'] = samelen[g0.fst-'a'] + (samelen[g0.fst-'a']+1) * g0.snd;
	REP(x,26) if(exist[x] && x != g0.fst-'a') len[x] = 1;
      }else{
	for(auto &pr : g) chmax(len[pr.fst-'a'], pr.snd);

	if(g.front().fst == g.back().fst){
	  if(exist[g.front().fst-'a']) chmax(len[g.front().fst-'a'], g.front().snd + g.back().snd + 1);
	}else{
	  if(exist[g.front().fst-'a']) chmax(len[g.front().fst-'a'], g.front().snd + 1);
	  if(exist[g.back().fst-'a']) chmax(len[g.back().fst-'a'], g.back().snd + 1);
	}
      }

      REP(x,26) samelen[x] = len[x];
      for(auto c : p[i]) exist[c-'a'] = true;
    }
    
    LLI ans = 0;
    REP(i,26) chmax(ans, samelen[i]);
    cout << ans << endl;
  }
  
  return 0;
}
