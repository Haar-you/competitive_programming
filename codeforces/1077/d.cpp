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

  int n,k; cin >> n >> k;
  vector<int> s(n);
  REP(i,n) cin >> s[i];

  map<int,int> mp;
  REP(i,n) mp[s[i]]++;

  auto f = [&](int m){
	     int count = 0;
	     for(auto kv : mp){
	       count += (kv.second/m);
	     }
	     return count >= k;
	   };

  int lower=0, upper=n, mid;
  int m;
  
  while(1){
    mid = (lower + upper) / 2;
    if(lower == upper){
      m = lower;
      break;
    }else if(lower+1 == upper){
      if(f(upper)) m = upper;
      else m = lower;
      break;
    }else{
      if(f(mid)){
	lower = mid;
      }else{
	upper = mid;
      }
    }
  }

  vector<int> ans;
  for(auto kv : mp){
    if(kv.second >= m){
      REP(i,kv.second/m){
	ans.push_back(kv.first);
      }
    }
  }

  REP(i,k){
    if(i!=0) cout << " ";
    cout << ans[i];
  }
  cout << endl;
  
  return 0;
}
