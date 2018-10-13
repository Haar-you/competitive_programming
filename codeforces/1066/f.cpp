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

const LLI inf = LLONG_MAX;

int dist(pair<int,int> &a, pair<int,int> &b){
  return abs(a.first-b.first) + abs(a.second-b.second);
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int n;
  cin >> n;

  map<int,vector<pair<int,int>>> m;
  
  REP(i,n){
    int x,y;
    cin >> x >> y;
    int level = max(x,y);

    if(m.find(level) == m.end()){
      m[level] = {make_pair(x,y)};
    }else{
      m[level].push_back(make_pair(x,y));
    }
  }
  m[0] = {make_pair(0,0)};

  vector<int> levels;
  for(auto a = m.begin(); a != m.end(); ++a){
    sort(a->second.begin(), a->second.end(),
	 [](pair<int,int> &p, pair<int,int> &q){return (p.first < q.first) || (p.first==q.first && p.second > q.second);});
    levels.push_back(a->first);
  }

  vector<vector<LLI>> dp(levels.size(), vector<LLI>(2, inf));

  dp[0][0] = dp[0][1] = 0;
  FOR(i,1,levels.size()){
    dp[i][0] =
      min(
	  dp[i][0],
	  min(dp[i-1][0] + dist(m[levels[i-1]].front(), m[levels[i]].back()) + dist(m[levels[i]].back(), m[levels[i]].front()),
	      dp[i-1][1] + dist(m[levels[i-1]].back(), m[levels[i]].back()) + dist(m[levels[i]].back(), m[levels[i]].front())
	      )
	  );
    dp[i][1] =
      min(
	  dp[i][1],
	  min(dp[i-1][0] + dist(m[levels[i-1]].front(), m[levels[i]].front()) + dist(m[levels[i]].front(), m[levels[i]].back()),
	      dp[i-1][1] + dist(m[levels[i-1]].back(), m[levels[i]].front()) + dist(m[levels[i]].front(), m[levels[i]].back())
	      )
	  );
  }

  cout << min(dp[levels.size()-1][0], dp[levels.size()-1][1]) << endl;
  
  return 0;
}
