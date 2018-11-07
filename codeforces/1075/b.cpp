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
template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m; cin >> n >> m;
  vector<int> riders, drivers;
  vector<int> temp(n+m);
  vector<int> count(m,0);
  
  REP(i,n+m) cin >> temp[i];
  REP(i,n+m){
    int t; cin >> t;
    if(t == 1){
      drivers.push_back(temp[i]);
    }else{
      riders.push_back(temp[i]);
    }
  }

  sort(ALL(drivers));
  sort(ALL(riders));

  REP(i,n){
    int r = riders[i];
    auto s = upper_bound(ALL(drivers), r);

    if(s == drivers.begin()){
      count[0]++;
    }else if(s == drivers.end()){
      count[m-1]++;
    }else{
      if(r-*(s-1) <= *s-r){
	count[s-drivers.begin()-1]++;
      }else{
	count[s-drivers.begin()]++;
      }
    }
  }

  cout_join(count);
  
  return 0;
}
