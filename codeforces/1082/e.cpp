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
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

int max_partial_sum(vector<int> &v){
  int t = v[0], ans = t;
  FOR(i,1,v.size()) ans = max(ans, t = max(t+v[i], v[i]));
  return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, c; cin >> n >> c;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  map<int,vector<int>> memo;
  REP(i,n) memo[a[i]].push_back(i);
  
  vector<int> count_c(n+1);
  REP(i,n) count_c[i+1] = count_c[i] + (a[i]==c?1:0);

  int ans = count_c[n];
  
  for(auto &kv : memo){
    if(kv.first == c) continue;
    vector<int> temp;

    auto &v = kv.second;
    REP(i,v.size()-1){
      temp.push_back(1);
      temp.push_back(-(count_c[v[i+1]+1] - count_c[v[i]]));
    }
    temp.push_back(1);

    ans = max(ans, count_c[n] + max_partial_sum(temp));
  }
  cout << ans << endl;
  
  return 0;
}
