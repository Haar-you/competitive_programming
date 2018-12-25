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

  string s; cin >> s;
  string ans;

  if(s.size()%2==0){
    REP(i,s.size()/2){
      ans.push_back(s[s.size()-i-1]);
      ans.push_back(s[i]);
    }
  }else{
    REP(i,s.size()/2){
      ans.push_back(s[i]);
      ans.push_back(s[s.size()-i-1]);
    }
    ans.push_back(s[s.size()/2]);
  }

  reverse(ALL(ans));

  cout << ans << endl;
  
  return 0;
}
