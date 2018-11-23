#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void cout_join(I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)cout<<d;cout<<*i;}cout<<endl;}

template <typename T> T ceilGE(T a, T b){if(a % b) return a/b+1-(sign(a)*sign(b)<0?1:0); return a/b;}

const LLI mod = 1e9+7;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n, x, y; cin >> n >> x >> y;
  vector<pair<int,int>> p(n);
  REP(i,n){
    int l,r;
    cin >> l >> r;
    p[i] = make_pair(l,r);
  }

  sort(ALL(p));

  LLI cost = 0;
  map<int,int> m;
  
  REP(i,n){
    double t = p[i].first - x/y;
    auto itr = m.lower_bound(p[i].first);
    auto prv = itr != m.begin() ? prev(itr) : m.begin();
    
    if(itr != m.begin() && prv->first < p[i].first && prv->first >= t){
      (cost += (y*(p[i].second-prv->first)) % mod) %= mod;

      (prv->second)--;
      m[p[i].second]++;

      if(prv->second == 0) m.erase(prv);

    }else{
      (cost += (x+y*(p[i].second-p[i].first)) % mod) %= mod;
      m[p[i].second]++;
    }
  }

  cout << cost << endl;
  
  return 0;
}
