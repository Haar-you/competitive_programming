#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

const LLI mod = 1e9+7;

LLI dp[110][1<<7][8];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int h,w,k; cin >> h >> w >> k;

  vector<int> pattern;

  REP(i,1<<(w-1)){
    bool f = true;
    REP(j,w-2){
      if((1&(i>>j)) && (1&(i>>(j+1)))){
	f = false;
	break;
      }
    }
    if(f) pattern.push_back(i);
  }
  
  dp[0][0][0] = 1;

  FORE(i,1,h){
    for(auto j : pattern){
      REP(p,w){

	int m;
	if(p==0){
	  if(j & 1) m=1;
	  else m=0;
	}else if(p==w-1){
	  if(j & (1<<(w-2))) m=w-2;
	  else m=w-1;
	}else{
	  if(j & (1<<p)) m=p+1;
	  else if(j & (1<<(p-1))) m=p-1;
	  else m=p;
	}

	for(auto l : pattern){
	  (dp[i][j][p] += dp[i-1][l][m]) %= mod;

	}
      }
    }
  }


  LLI ans = 0;
  for(auto i : pattern){
    (ans += dp[h][i][k-1]) %= mod;
  }

  cout << ans << endl;
  
  return 0;
}
