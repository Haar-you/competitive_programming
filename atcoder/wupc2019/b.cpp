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

int memo[10] = {0,0,0,0,0,0,1,1,2,3};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int H,W;
  while(cin >> H >> W){
    vector<vector<int>> a(H, vector<int>(W)); cin >> a;

    bool all_zero = true;
    bool any_five = false;
    REP(i,H) REP(j,W){
      if(a[i][j] != 0) all_zero = false;
      if(a[i][j] == 5) any_five = true;
    }
    
    if(all_zero){
      cout << "Yes 0" << endl;
      continue;
    }

    if(!any_five){
      cout << "No" << endl;
      continue;
    }

    if(H == 1 || W == 1){
      vector<int> v;
      REP(i,H) REP(j,W) v.push_back(a[i][j]);

      int mn = 100;
      REP(i,v.size()){
	if(v[i] == 5){
	  chmin(mn, memo[*max_element(v.begin(),v.begin()+i)] + memo[*max_element(v.begin()+i+1,v.end())]);
	}
      }
      int ans = mn + 1;
      cout << "YES " << ans << endl;
    }else{
      int m=0;
      REP(i,H) REP(j,W) chmax(m, a[i][j]);

      int ans = memo[m] + 1;
      cout << "Yes " << ans << endl;
    }
  }
  
  return 0;
}