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
  vector<int> vert(n+1);
  vector<int> hor;

  REP(i,n) cin >> vert[i];
  REP(i,m){
    int x1,x2,y; cin >> x1 >> x2 >> y;
    if(x1 == 1) hor.push_back(x2);
  }
  
  vert[n] = 1e9;

  sort(ALL(vert));
  sort(ALL(hor));

  
  int k = 1e9;
  
  REP(i,n+1){
    int c = i;

    if(!hor.empty()){
      if(hor.back() >= vert[i]){
	c += hor.end() - lower_bound(ALL(hor),vert[i]);
      }
    }
    k = min(k,c);
  }

  cout << k << endl;
  
  return 0;
}
