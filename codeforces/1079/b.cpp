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

void solve(string s){
  int l = s.size();

  FORE(a,1,5){
    if(l > a*20) continue;

    FORE(b,1,20){
      if(l <= a*b){
	vector<string> ans(a);

	REP(i,a*b-l) ans[i%a].push_back('*');

	int r=0;
	REP(i,l){
	  ans[r].push_back(s[i]);
	  if(ans[r].size() == b) ++r;
	}

	cout << a << " " << b << endl;
	REP(i,a){
	  cout << ans[i] << endl;
	}

	return;
      }
    }    
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  string s; cin >> s;

  solve(s);

  return 0;
}
