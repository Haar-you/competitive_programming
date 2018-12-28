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

bool solve(int n, vector<int> &a, vector<int> &b, vector<int> &ans){
  ans[0] = 1;
  ans[1] = a[0];
  ans[2] = b[0];

  FOR(i,1,n-2){
    if(a[ans[i]-1] == ans[i+1]) ans[i+2] = b[ans[i]-1];
    else if(b[ans[i]-1] == ans[i+1]) ans[i+2] = a[ans[i]-1];
    else return false;
  }

  if(a[ans[n-2]-1] == 1) ans[n-1] = b[ans[n-2]-1];
  else if(b[ans[n-2]-1] == 1) ans[n-1] = a[ans[n-2]-1];
  else return false;
  
  if((a[ans[n-1]-1] == 1 && b[ans[n-1]-1] == ans[1]) || (b[ans[n-1]-1] == 1 && a[ans[n-1]-1] == ans[1]))
    return true;
  else
    return false;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n), b(n);
  REP(i,n) cin >> a[i] >> b[i];

  vector<int> ans(n);
  if(!solve(n,a,b,ans)){
    fill(ALL(ans), 0);
    solve(n,b,a,ans);
  }
  
  join(cout, ALL(ans));
  
  return 0;
}
