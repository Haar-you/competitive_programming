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
template <typename T> void cout_join(vector<T> &v,string d=" "){REP(i,v.size()){if(i>0)cout<<d;cout<<v[i];}cout<<endl;}

vector<int> prime_factorize(int n){
  vector<int> res;
  for(int i=2; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);
      n/=i;
      --i;
    }
  }
  if(n!=1) res.push_back(n);
  return res;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;

  vector<int> pf = prime_factorize(n);

  map<int,int> m;

  for(auto p : pf){
    m[p]++;
  }

  int mx = 0;
  for(auto kv : m){
    mx = max(mx, kv.second);
  }

  int b = 1;
  int i = 0;
  while(1){
    if(mx <= b) break;
    b *= 2;
    ++i;
  }

  bool p = true;
  for(auto kv : m){
    if(kv.second != b){p = false; break;}
  }

  int cnt = 0;
  
  if(!p){
    ++cnt;
  }

  cnt += i;

  int ans = 1;
  for(auto kv : m){
    ans *= kv.first;
  }
  
  cout << ans << " " << cnt << endl;
  
  return 0;
}
