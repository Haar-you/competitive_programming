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

int n,k;
vector<int> a;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> n >> k;
  a.resize(n);
  REP(i,n) cin >> a[i];

  map<int,int> mm;
  mm[0] = 1;
  
  LLI count = 0;
  vector<int> s(n+1);
  s[0] = 0;
  
  FORE(i,1,n){
    if(mm[s[i-1] ^ a[i-1]] >  mm[s[i-1] ^ (((1<<k)-1) ^ a[i-1])])
      a[i-1] = ((1<<k)-1) ^ a[i-1];

    s[i] = s[i-1] ^ a[i-1];

    count += i - mm[s[i]];
    ++mm[s[i]];
  }

  cout << count << endl;
  
  return 0;
}
