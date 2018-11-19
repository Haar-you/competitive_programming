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

  int n; cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  vector<int> b(n);

  FORE(k,1,5){
    bool possible = true;
    b[0] = k;
    
    FOR(i,0,n-1){
      if(a[i] < a[i+1]){
	if(i<n-2 && a[i+1] > a[i+2]) b[i+1] = max(b[i]+1, 5);
	else b[i+1] = b[i]+1;
      }else if(a[i] > a[i+1]){
	if(i<n-2 && a[i+1] < a[i+2]) b[i+1] = min(b[i]-1, 1);
	else b[i+1] = b[i]-1;
      }else{
	if(i<n-2){
	  if(a[i+1] < a[i+2]){
	    b[i+1] = (b[i] == 1 ? 2 : 1);
	  }else if(a[i+1] > a[i+2]){
	    b[i+1] = (b[i] == 5 ? 4 : 5);
	  }else{
	    b[i+1] = (b[i] == 2 ? 3 : 2);
	  }
	}else{
	  b[i+1] = (b[i] == 2 ? 3 : 2);
	}
      }
      
      if(b[i+1] > 5 || b[i+1] < 1){
	possible = false;
	break;
      }
    }

    if(possible){
      cout_join(b);
      return 0;
    }
  }
  
  cout << -1 << endl;

  return 0;
}
