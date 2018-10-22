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

string join(vector<int> &xs, const char *delim){
  string str = "";
  REP(i,xs.size()){
    if(i > 0) str += delim;
    str += to_string(xs[i]);
  }
  return str;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI a, b; cin >> a >> b;

  LLI s=0;
  int x;
  for(x=1;x<=1e5;++x){
    if(s+x > a+b){--x; break;}
    s += x;
  }
  vector<bool> used(x, false);
  vector<int> A,B;

  int sum = 0;
  for(int i=x; i>=1; --i){
    if(!used[i] && sum+i <= a){
      sum += i;
      A.push_back(i);
      used[i] = true;
    }
  }

  sum = 0;
  for(int i=1; i<=x; ++i){
    if(!used[i] && sum+i <= b){
      sum += i;
      B.push_back(i);
      used[i] = true;
    }
  }

  cout << A.size() << endl;
  cout << join(A, " ") << endl;

  cout << B.size() << endl;
  cout << join(B, " ") << endl;
  
  return 0;
}
