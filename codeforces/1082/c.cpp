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

  int n,m; cin >> n >> m;

  vector<int> s(n), r(n);
  REP(i,n) cin >> s[i] >> r[i];

  unordered_map<int,vector<LLI>> sp;

  if(all_of(ALL(r), [](int x){return x<0;})){
    cout << 0 << endl;
  }else{
    REP(i,n) sp[s[i]].push_back(r[i]);

    ITR(it,sp){
      auto &v = it->second;
      sort(ALL(v), greater<LLI>());
      FOR(i,1,v.size()) v[i] += v[i-1];
    }

    LLI ans = 0;

    REP(i,n){
      LLI t = 0;
      for(auto it=sp.begin(); it!=sp.end();){
	auto &v = it->second;
	if(v.size() < i+1 || v[i] < 0){
	  it = sp.erase(it);
	  continue;
	}
	t += v[i];
	++it;
      }
      ans = max(ans, t);
    }

    cout << ans << endl;
  }
  
  return 0;
}
