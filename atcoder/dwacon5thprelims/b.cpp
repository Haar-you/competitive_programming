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

void solve(int n, int k, vector<LLI> &b){
  LLI ans = 0;
  REV(i,40,1){
    int count = 0;
    LLI t = ans + (1LL<<(i-1));
    REP(j,b.size()){
      if((t & b[j]) == t) ++count;
    }
    if(count >= k) ans += (1LL<<(i-1));
  }
  cout << ans << endl;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,k; cin >> n >> k;
  vector<LLI> a(n);
  REP(i,n) cin >> a[i];


  vector<LLI> s(n+1,0);
  REP(i,n) s[i+1] = s[i] + a[i];

  vector<LLI> b;
  REP(i,n){
    FORE(j,i+1,n){
      b.push_back(s[j]-s[i]);
    }
  }
  
  solve(n,k,b);

  /* コンテスト中に書いてACしたコード

  int cur = 63;

  REP(_,64){
    LLI ans = (1LL<<63); --ans;
  
    map<int,vector<LLI>> count;
  
    REP(i,b.size()){
      REP(j,64){
	if(b[i] & (1LL<<j)) count[j].push_back(b[i]);
      }
    }

    for(int i=cur; i>=0; --i){
      if(count[i].size() == k){
	for(auto v : count[i]){
	  ans = ans & v;
	}
	cout << ans << endl;
	return 0;
      }else if(count[i].size() > k){
	b = count[i];
	cur = i-1;
	break;
      }
      if(i == 0){
	REP(j,k){
	  ans = ans & b[j];
	}
	cout << ans << endl;
	return 0;
      }
    }
  }
  */
  return 0;
}
