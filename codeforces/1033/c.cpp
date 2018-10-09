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

vector<int> a, check;
int n;

int solve(int i){
  if(check[i] == -1){
    vector<int> temp;
    
    for(int k=i+a[i]; k<n; k+=a[i])
      if(a[k] > a[i])
	temp.push_back(solve(k));
    for(int k=i-a[i]; k>=0; k-=a[i])
      if(a[k] > a[i])
	temp.push_back(solve(k));
    sort(temp.begin(), temp.end());
    int g=0;
    for(auto v: temp){
      if(v > g) break;
      ++g;
    }
    check[i] = g;
  }
  return check[i];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> n;
  a.resize(n);
  check.resize(n);
  REP(i,n){
    cin >> a[i];
    check[i] = -1;
  }
  
  REP(i,n) solve(i);
  
  REP(i, n) cout << (check[i]>0 ? 'A' : 'B') ;
  cout << endl;
  
  return 0;
}
