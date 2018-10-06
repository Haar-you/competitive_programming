#include <bits/stdc++.h>

using namespace std;

int main(){
  int n, m;
  cin >> n >> m;

  vector<string> s(n);
  for(int i=0; i<n; ++i) cin >> s[i];

  vector<string> f(n, string(m, '.'));

  int d[8][2] = {{0,0},{1,0},{2,0},{2,1},{2,2},{1,2},{0,2},{0,1}};
  
  for(int i=0; i<=n-3; ++i){
    for(int j=0; j<=m-3; ++j){
      bool check = true;
      for(int k=0; k<8; ++k) if(s[i+d[k][0]][j+d[k][1]] != '#') {check = false; break;}
      if(check) for(int k=0; k<8; ++k) f[i+d[k][0]][j+d[k][1]] = '#';
    }
  }

  bool ans = true;
  for(int i=0; i<n; ++i){
    for(int j=0; j<m; ++j){
      if(s[i][j] != f[i][j]) {ans = false; break;}
    }
    if(!ans) break;
  }

  cout << (ans ? "YES" : "NO") << endl;
  
  return 0; 
}
