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

LLI lb(LLI a, LLI b){
  if(a % b) return a/b+1;
  return a/b;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,m,k,l; cin >> n >> m >> k >> l;
  LLI x = lb(l+k,m);

  if(x*m > n)
    cout << -1 << endl;
  else
    cout << x << endl;
  
  return 0;
}
