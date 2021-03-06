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

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}

template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> a(n); cin >> a;

    bool no = false;
    vector<int> ans(n);

    int dp[200100][2];
    int restore[200100][2];
    fill_array(dp, 0);
    fill_array(restore, 0);

    REP(i,n){
      dp[i][0] = INT_MIN;
      dp[i][1] = INT_MAX;
    }

    dp[0][0] = INT_MAX;
    dp[0][1] = INT_MIN;

    FORE(i,1,n){
      if(a[i] > a[i-1]) if(chmax(dp[i][0], dp[i-1][0])) restore[i][0] = 0;
      if(a[i] < dp[i-1][0]) if(chmin(dp[i][1], a[i-1])) restore[i][1] = 0;
      if(a[i] < a[i-1]) if(chmin(dp[i][1], dp[i-1][1])) restore[i][1] = 1;
      if(a[i] > dp[i-1][1]) if(chmax(dp[i][0], a[i-1])) restore[i][0] = 1;
    }

    if(dp[n-1][0] == INT_MIN and dp[n-1][1] == INT_MAX) no = true;
    else{
      int p = (dp[n-1][0] != INT_MIN ? 0 : 1);
      REV(i,n-1,0){
	ans[i] = p;
	p = restore[i][p];
      }
    }

    if(no){
      cout << "NO" << endl;
    }else{
      cout << "YES" << endl;
      join(cout, ALL(ans));
    }
  }
  
  return 0;
}
