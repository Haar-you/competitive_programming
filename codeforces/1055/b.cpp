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

  LLI n,m,l; cin >> n >> m >> l;
  vector<LLI> a(n);
  REP(i,n) cin >> a[i];

  LLI count = 0;

  REP(i,n){
    if(a[i] > l){
      if(i==0){
	++count;
      }else{
	if(a[i-1] <= l) ++count;
      }
    }
  }

  REP(i,m){
    LLI t; cin >> t;
    
    if(t == 0){
      cout << count << endl;
    }else{
      LLI p,d; cin >> p >> d;
      --p;

      if(a[p]+d <= l) a[p] += d;
      else if(a[p] <= l){
	if(p == 0){
	  if(n==1 || (n>=2 && a[1]<=l)) ++count;
	}else if(p == n-1){
	  if(n==1 || (n>=2 && a[n-2]<=l)) ++count;
	}else{
	  if(a[p-1]<=l && a[p+1]<=l) ++count;
	  else if(a[p-1]>l && a[p+1]>l) --count;
	}
	a[p] += d;
      }
    }
  }

  return 0;
}
