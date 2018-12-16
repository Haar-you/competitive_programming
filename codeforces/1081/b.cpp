#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  map<int,vector<int>> m;
  REP(i,n){
    m[a[i]].push_back(i);
  }
  
  vector<int> b(n);
  int k = 1;

  for(auto &kv : m){
    auto &vec = kv.second;
    int d = n - kv.first;

    if(d <= 0 || vec.size() % d != 0){
      cout << "Impossible" << endl;
      return 0;
    }

    REP(i, vec.size()){
      b[vec[i]] = k;
      if(i % d == d - 1) ++k;
    }
  }

  cout << "Possible" << endl;
  join(cout, ALL(b));
  
  return 0;
}
