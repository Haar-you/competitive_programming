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
template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,s; cin >> n >> s;
  vector<int> a(n), b(n);

  REP(i,n) cin >> a[i];
  REP(i,n) cin >> b[i];

  if(a[0] == 0){
    cout << "NO" << endl;
    return 0;
  }

  if(a[s-1] == 1){
    cout << "YES" << endl;
    return 0;
  }
  
  if(b[s-1] == 1){
    FOR(i,s,n){
      if(a[i] == 1 && b[i] == 1){
	cout << "YES" << endl;
	return 0;
      }
    }
  }

  cout << "NO" << endl;
  
  return 0;
}
