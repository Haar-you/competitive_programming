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

  LLI n,t; cin >> n >> t;
  vector<int> a(n);
  REP(i,n) cin >> a[i];
  
  LLI sum = 0; REP(i,n) sum += a[i];
  LLI count = 0;
  int len = a.size();

  while(1){
    if(t == 0 || sum == 0) break;
    if(t >= sum){
      count += (t/sum) * len;
      t %= sum;
    }else{
      LLI s = 0;
      for(auto itr = a.begin(); itr != a.end(); ++itr){
	if(s + *itr > t){
	  --len;
	  sum -= *itr;
	  *itr = 0;
	}else{
	  s += *itr;
	}
      }
    }
  }

  cout << count << endl;
  
  return 0;
}
