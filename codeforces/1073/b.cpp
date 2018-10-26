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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n), b(n);
  REP(i,n) cin >> a[i];
  REP(i,n) cin >> b[i];

  vector<int> check(n, false);
  vector<int> count;

  int cur=0;

  REP(i,n){
    if(check[b[i]-1]){
      count.push_back(0);
    }else{
      int p = cur;
      while(1){
	if(a[cur] == b[i]) break;
	check[a[cur]-1] = true;
	++cur;
      }
      count.push_back(cur-p+1);
      ++cur;
    }
  }

  REP(i,n) {if(i!=0) cout << " "; cout << count[i];}
  cout << endl;
  
  
  return 0;
}
