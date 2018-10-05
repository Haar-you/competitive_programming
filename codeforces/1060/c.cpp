#include <bits/stdc++.h>
#define LLI long long int
using namespace std;

int main(){
  int n, m;
  cin >> n >> m;

  vector<int> as(n), bs(m);

  for(int i=0; i<n; ++i) cin >> as[i];
  for(int i=0; i<m; ++i) cin >> bs[i];

  LLI x;
  cin >> x;

  vector<int> asum(n+1, 0);
  vector<int> bsum(m+1, 0);

  for(int i=1; i<=n; ++i) asum[i] = asum[i-1] + as[i-1];
  for(int i=1; i<=m; ++i) bsum[i] = bsum[i-1] + bs[i-1];

  map<int,int> amap, bmap;

  for(int i=0; i<=n; ++i)
    for(int j=i+1; j<=n; ++j)
      if(amap.find(j-i) == amap.end())
	amap[j-i] = asum[j]-asum[i];
      else
	amap[j-i] = min(amap[j-i], asum[j]-asum[i]);

  for(int i=0; i<=m; ++i)
    for(int j=i+1; j<=m; ++j)
      if(bmap.find(j-i) == bmap.end())
	bmap[j-i] = bsum[j]-bsum[i];
      else
	bmap[j-i] = min(bmap[j-i], bsum[j]-bsum[i]);

  int ans = 0;
  
  for(auto a : amap)
    for(auto b : bmap)
      if((1LL * a.second * b.second) <= x)
	ans = max(ans, a.first*b.first);
      
  cout << ans << endl;

  return 0;
}
