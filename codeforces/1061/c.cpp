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

const LLI mod = 1e9+7;

template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

vector<LLI> divisor_list(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(is_square(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<LLI> a(n);
  REP(i,n) cin >> a[i];

  vector<LLI> dp(n, 0);
  vector<LLI> memo(1e6+1, 0);

  REP(i,n){
    vector<LLI> ps = divisor_list(a[i]);
    dp[i] = 1;
    if(a[i] == 1){
      memo[1] ++;
    }else{
      reverse(ALL(ps));
      REP(j,ps.size()){
	(dp[i] += memo[ps[j]-1]) %= mod;
	(memo[ps[j]] += memo[ps[j]-1]) %= mod;
      }
      memo[1] ++;
    }
  }

  LLI count = 0;

  REP(i,n){
    (count += dp[i]) %= mod;
  }

  cout << count << endl;
  
  return 0;
}
