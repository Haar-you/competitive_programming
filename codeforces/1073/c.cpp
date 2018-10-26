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
  string ops; cin >> ops;
  int x,y; cin >> x >> y;

  if(abs(x)+abs(y)>n || (n-abs(x)-abs(y))%2){
    cout << -1 << endl;
    return 0;
  }

  vector<int> X(n+1), Y(n+1);
  X[0] = Y[0] = 0;
  FOR(i,0,n){
    if(ops[i] == 'L'){X[i+1] = X[i] - 1; Y[i+1] = Y[i];}
    if(ops[i] == 'R'){X[i+1] = X[i] + 1; Y[i+1] = Y[i];}
    if(ops[i] == 'D'){X[i+1] = X[i]; Y[i+1] = Y[i] - 1;}
    if(ops[i] == 'U'){X[i+1] = X[i]; Y[i+1] = Y[i] + 1;}
  }

  int l=0,r=0,m=1e9;

  while(l<=n && r<=n){
    int d = abs(x-(X[l]+X[n]-X[r])) + abs(y-(Y[l]+Y[n]-Y[r]));
    
    if(d <= r-l){
      m = min(m,r-l);
      ++l;
    }else{
      ++r;
    }
  }

  cout << m << endl;
  
  return 0;
}
