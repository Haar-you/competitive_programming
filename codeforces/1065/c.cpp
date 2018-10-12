#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define RS resize
#define CLR clear
#define PB push_back
#define ALL(x) (x).begin(), (x).end()
using namespace std;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, k;
  cin >> n >> k;

  vector<int> hs(n);
  REP(i, n) cin >> hs[i];
  
  vector<int> c(200001, 0);
  REP(i, n) c[hs[i]]++;

  for(int i=200000-1; i>=1; --i) c[i] += c[i+1];
  
  int h=200000;
  int count=0;

  while(c[h] == 0) --h;
 
  while(h > 0 && c[h] < n){
    int sum=0;
    while(h > 0 && c[h] < n && sum + c[h] <= k){
      sum += c[h];
      --h;
    }
    count++;
  }

  cout << count << endl;
  
  return 0;
}
