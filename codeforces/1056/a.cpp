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

  int n;
  cin >> n;

  vector<int> m(110,0);

  REP(i,n){
    int r; cin >> r;
    REP(j,r){
      int a; cin >> a;
      m[a]++;
    }
  }

  vector<int> ans;
  FORE(i,1,100) if(m[i] == n) ans.push_back(i);

  cout_join(ALL(ans));
  
  return 0;
}
