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

  int n; cin >> n;

  vector<string> a(2*n-2);
  map<string, int> m;
  REP(i,2*n-2){
    cin >> a[i];
    m[a[i]] = i;
  }

  sort(ALL(a), [](string &x, string &y){return x.length() < y.length();});
  string s1=a[0], s2=a[1], l1=a[2*n-4], l2=a[2*n-3];

  vector<string> s = {s1+l1, s1+l2, s2+l1, s2+l2, l1+s1, l1+s2, l2+s1, l2+s2};

  sort(ALL(a));

  REP(i,8){
    vector<string> ps, sfs;
    REP(j,n-1) ps.push_back(s[i].substr(0,j+1));
    REP(j,n-1){
      ps.push_back(s[i].substr(j+1,n));
      sfs.push_back(s[i].substr(j+1,n));
    }
    sort(ALL(ps));

    if(ps != a) continue;

    string ans(2*n-2, 'P');

    REP(j,n-1){
      ans[m[sfs[j]]] = 'S'; 
    }
    
    cout << ans << endl;
    break;
  }
  
  return 0;
}
