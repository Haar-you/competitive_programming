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
template <typename T> bool isSquare(T n){T rt = sqrt(n); return rt*rt == n;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;

  if(!isSquare(1+8*n)){
    cout << "No" << endl;
    return 0;
  }

  int k = ((int)sqrt(1+8*n)+1)/2;

  cout << "Yes" << endl;
  cout << k << endl;

  vector<vector<int>> s(k);

  int t = 1;
  
  FOR(i,0,k){
    FOR(j,t,t+k-1-i){
      s[i].push_back(j);
    }
    FOR(j,0,k-1-i){
      s[i+j+1].push_back(t+j);
    }
    t += k-1-i;
  }
  
  REP(i,k){
    cout << k-1 << " ";
    REP(j,s[i].size()){
      if(j!=0) cout << " ";
      cout << s[i][j];
    }
    cout << endl;
  }
    
  return 0;
}
