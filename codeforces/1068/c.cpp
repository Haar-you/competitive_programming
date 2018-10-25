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

  int n,m; cin >> n >> m;
  V<V<bool>> table(n, V<bool>(n, false));
  V<V<P<int,int>>> rooks(n);

  REP(i,n) rooks[i].push_back(make_pair(i,i));

  REP(i,m){
    int x,y; cin >> x >> y;
    rooks[x-1].push_back(make_pair(i+n,x-1));
    rooks[y-1].push_back(make_pair(i+n,y-1));
  }

  REP(i,n){
    cout << rooks[i].size() << endl;
    for(auto a : rooks[i]) cout << a.first + 1 << " " << a.second + 1 << endl;
  }
  
  return 0;
}
