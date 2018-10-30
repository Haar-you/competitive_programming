#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename T> T gcd(T a, T b){a = abs(a); b = abs(b); if(a<b) swap(a,b); while(b>0){a %= b; swap(a,b);} return a;}
template <typename T> T lcm(T a, T b){return (1LL * a * b) / gcd(a,b);}
template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m; cin >> n >> m;
  vector<vector<int>> a(m, vector<int>(n));
  REP(i,m) REP(j,n) cin >> a[i][j];

  vector<vector<int>> next(m, vector<int>(n+1,0));
  REP(i,m) REP(j,n-1) next[i][a[i][j]] = a[i][j+1];

  LLI count = 0;
  REP(i,n){
    LLI c = 1;
    while(1){
      if(i+1>=n) break;
      bool f = false;
      REP(j,m){
	if(next[j][a[0][i]] != a[0][i+1]){
	  f = true;
	  break;
	}
      }
      if(f) break;
      ++i;
      ++c;
    }
    count += c*(c+1)/2;
  }

  
  cout << count << endl;
  
  return 0;
}
