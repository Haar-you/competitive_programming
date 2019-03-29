#include <bits/stdc++.h>
#define LLI long long int
using namespace std;

const int MAX = 1000000;
LLI dp[MAX+1][10];
int mod = 1000000007;

int main(){
  int n;
  cin >> n;

  for(int i=0; i<=9; ++i) dp[0][i] = 1;
  for(int i=1; i<=n; ++i){
    dp[i][0] = 1;
    for(int j=1; j<=9; ++j){
      dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mod;
    }
  }

  cout << dp[n][9] << endl;

  return 0;
}
