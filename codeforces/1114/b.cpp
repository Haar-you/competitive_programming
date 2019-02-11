#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

using namespace std;

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m,k;
  while(cin >> n >> m >> k){
    vector<int> a(n); cin >> a;

    vector<int> b(a);
    sort(ALL(b), greater<int>());

    map<int,int> mp;
    LLI s = 0;
    REP(i,k*m){
      ++mp[b[i]];
      s += b[i];
    }

    cout << s << endl;

    vector<int> p;
    int c = 0;
    REP(i,n){
      if(mp[a[i]] > 0){
	++c;
	--mp[a[i]];
      }

      if(c == m){
	p.push_back(i+1);
	c = 0;
      }
    }
    p.pop_back();
    join(cout, ALL(p));
  }
  
  return 0;
}
