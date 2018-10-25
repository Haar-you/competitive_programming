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


bool isSquare(LLI n){
  LLI rt = sqrt(n);
  return rt*rt == n;
}

int countDivisor(LLI n){
  int count = 1;
  for(LLI i=2LL; i<min((LLI)sqrt(n)+1,n); ++i){
    if(n % i == 0) ++count;
  }
  count *= 2;
  if(isSquare(n)) --count;
  return count;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI b; cin >> b;

  cout << countDivisor(b) << endl;

  return 0;
}
