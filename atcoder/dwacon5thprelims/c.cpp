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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI N,Q;
  string S;
  cin >> N >> S >> Q;

  REP(_,Q){
    LLI k; cin >> k;

    LLI sum_m = count(ALL(S), 'M');

    vector<LLI> count_m(N+1, 0);
    REP(i,N) if(S[i] == 'M') count_m[i+1]++;
    REP(i,N) count_m[i+1] += count_m[i];

    vector<LLI> count_d(N+1, 0);
    REP(i,N) if(S[i] == 'D') count_d[i+1]++;
    REP(i,N) count_d[i+1] += count_d[i];

    vector<LLI> count_dm(N+1, 0);
    REP(i,N){
      if(S[i] == 'D'){
	count_dm[i] = sum_m - count_m[i];
      }
    }
    REV(i,N-1,0) count_dm[i] += count_dm[i+1];
    
    LLI ans = 0;
    REP(i,N){
      if(S[i] == 'C'){
	LLI temp = count_dm[max(0LL,i-k+1)] - count_dm[i] - (sum_m - count_m[i]) * (count_d[i] - count_d[max(0LL,i-k+1)]);
	ans += temp;
      }
    }
    
    cout << ans << endl;
  }
  
  return 0;
}
