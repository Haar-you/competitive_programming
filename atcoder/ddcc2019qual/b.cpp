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

  int n; cin >> n;

  int count = 0;

  FORE(i,1,n){
    FORE(j,1,n){
      if(2*j>=n-2*i && 2*j>=-n+2*(i+1) && 2*(j+1)<=n+2*i && 2*(j+1)<=3*n-2*(i+1)) ++count;
    }
  }
  
  cout << count << endl;
  
  return 0;
}
