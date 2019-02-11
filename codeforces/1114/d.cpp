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
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;

template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}

template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

template <typename T> void unique(vector<T> &v){
  auto itr = unique(ALL(v));
  v.erase(itr,v.end());
}

int dp[5100][5100];
bool used[5100][5100];

int rec(int l, int r, vector<int> &c){ // [l,r]
  if(used[l][r]) return dp[l][r];
  used[l][r] = true;

  if(l == r) return dp[l][r] = 0;

  if(c[l] == c[r]){
    return dp[l][r] = rec(l+1,r-1,c) + 1;
  }else{
    return dp[l][r] = min(rec(l+1,r,c), rec(l,r-1,c)) + 1;
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> c(n); cin >> c;
    unique(c);

    fill_array(dp, 1e9);
    fill_array(used, false);
    int ans = rec(0, c.size()-1, c);

    cout << ans << endl;
  }
  
  return 0;
}
