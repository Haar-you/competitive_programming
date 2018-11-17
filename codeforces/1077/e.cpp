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
template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  map<int,int> mp;
  REP(i,n) mp[a[i]]++;

  vector<LLI> v;
  for(auto kv : mp) v.push_back(kv.second);
  sort(ALL(v));

  int mx = *max_element(ALL(v));
  
  int ans = 0;
  FORE(i,1,mx){
    int count = 0;

    auto cur = v.begin();

    FOR(j,0,20){
      if((cur = lower_bound(cur, v.end(), 1LL*i*(1<<j))) != v.end()){
	count += 1LL*i*(1<<j);
	++cur;
      }else{
	break;
      }
    }

    ans = max(ans, count);
  }

  cout << ans << endl;

  return 0;
}
