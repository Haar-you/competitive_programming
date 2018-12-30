#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}

LLI dp[101000][4];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  string s; cin >> s;
  vector<int> a(n); cin >> a;


  REP(i,n){
    switch(s[i]){
    case 'h':
      dp[i+1][0] = dp[i][0] + a[i];
      dp[i+1][1] = dp[i][1];
      dp[i+1][2] = dp[i][2];
      dp[i+1][3] = dp[i][3];
      break;
    case 'a':
      dp[i+1][0] = dp[i][0];
      dp[i+1][1] = min(dp[i][0], dp[i][1] + a[i]);
      dp[i+1][2] = dp[i][2];
      dp[i+1][3] = dp[i][3];
      break;
    case 'r':
      dp[i+1][0] = dp[i][0];
      dp[i+1][1] = dp[i][1];
      dp[i+1][2] = min(dp[i][1], dp[i][2] + a[i]);
      dp[i+1][3] = dp[i][3];
      break;
    case 'd':
      dp[i+1][0] = dp[i][0];
      dp[i+1][1] = dp[i][1];
      dp[i+1][2] = dp[i][2];
      dp[i+1][3] = min(dp[i][2], dp[i][3] + a[i]);
      break;
    default:
      dp[i+1][0] = dp[i][0];
      dp[i+1][1] = dp[i][1];
      dp[i+1][2] = dp[i][2];
      dp[i+1][3] = dp[i][3];      
      break;
    }
  }

  cout << dp[n][3] << endl;
  
  return 0;
}
