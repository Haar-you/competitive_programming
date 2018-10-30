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

template <typename T>
void cout_join(vector<T> &v, string delim = " "){
  REP(i,v.size()){if(i>0) cout << delim; cout << v[i];}
  cout << endl;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n+1);
  a[0] = 0;
  REP(i,n) cin >> a[i+1];

  vector<int> b(n);
  REP(i,n) b[i] = a[i+1] - a[i];

  vector<int> res;
  FORE(k,1,n){
    vector<int> temp(k);
    vector<bool> check(k,false);
    bool fail = false;
    REP(i,n){
      if(check[i%k]){
	if(temp[i%k] != b[i]){
	  fail = true;
	  break;
	}
      }else{
	temp[i%k] = b[i];
	check[i%k] = true;
      }
    }
    if(!fail) res.push_back(k);
  }

  cout << res.size() << endl;
  cout_join(res);

  return 0;
}
