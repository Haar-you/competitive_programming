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
  vector<int> a(n-1), b(n-1);
  REP(i,n-1) cin >> a[i];
  REP(i,n-1) cin >> b[i];

  vector<int> t(n);
  bool fail;

  REP(t0, 4){
  
    fail = false;
    t[0] = t0;
    FOR(i,0,n-1){
      int T = -1;
      REP(k,4){
	if((a[i] == (t[i] | k)) && (b[i] == (t[i] & k))){
	  T = k;
	  break;
	}
      }
      if(T == -1){
	fail = true;
	break;
      }
      t[i+1] = T;
    }

    if(!fail){
      cout << "YES" << endl;
      REP(i,n){
	if(i>0) cout << " ";
	cout << t[i];
      }
      cout << endl;
      return 0;
    }
  }

  cout << "NO" << endl;

  return 0;
}
