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

  int N; cin >> N;
  vector<LLI> a(N);
  REP(i,N) cin >> a[i];

  sort(ALL(a));
  reverse(ALL(a));

  unordered_map<LLI,int> umap;

  REP(i,N){
    ++umap[a[i]];
  }

  int ans = 0;
  REP(i,N){
    for(LLI j=(1LL<<32); j>=1; j>>=1){
      if(j <= a[i]) continue;

      if(j-a[i] == a[i]){
	if(umap[a[i]] >= 2){
	  ++ans;
	  umap[a[i]] -= 2;
	  break;
	}
      }else{
	if(umap[a[i]] >= 1 && umap[j-a[i]] >= 1){
	  ++ans;
	  --umap[a[i]];
	  --umap[j-a[i]];
	  break;
	}
      }
    }
  }

  cout << ans << endl;
  
  return 0;
}
