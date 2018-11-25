#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void cout_join(I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)cout<<d;cout<<*i;}cout<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,m; cin >> n >> m;
  LLI ans = 0;

  if(n <= m){
    FORE(i,1,n) FORE(j,1,n) if((i*i+j*j) % m == 0) ++ans;
    cout << ans << endl;
  }else{
    LLI t = 0;
    FORE(i,1,m) FORE(j,1,m) if((i*i+j*j) % m == 0) ++t;

    LLI t2 = 0;
    FORE(i,1,m) FORE(j,1,n%m) if((i*i+j*j) % m == 0) ++t2;
    
    LLI t3 = 0;
    FORE(i,1,n%m) FORE(j,1,n%m) if((i*i+j*j) % m == 0) ++t3;

    ans = t*(n/m)*(n/m) + t2*(n/m)*2 + t3;
    cout << ans << endl;
  }
  
  return 0;
}
