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
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

void print_edges(vector<vector<int>> &tree, int cur, int par){
  for(auto &next : tree[cur]){
    if(next == par) continue;
    cout << cur+1 << " " << next+1 << endl;
    print_edges(tree, next, cur);
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; cin >> n;
  vector<int> a(n);
  REP(i,n) cin >> a[i];

  if(n == 2){
    cout << "YES" << " " << 2 << endl;
    cout << 1 << endl;
    cout << 1 << " " << 2 << endl;
  }else{

    int t = 0, c = 0;
    vector<int> v;
    REP(i,n) if(a[i] >= 2){
      t += a[i];
      ++c;
      v.push_back(i);
    }
    
    if(c == 0 || t-2*c+2 < n-c){
      cout << "NO" << endl;
      return 0;
    }

    vector<vector<int>> g(n);

    REP(i,v.size()-1){
      g[v[i]].push_back(v[i+1]);
      g[v[i+1]].push_back(v[i]);
    }

    int k = n-c;
    if(k == 0){
      cout << "YES" << " " << c-1 << endl;
    }else if(k == 1){
      cout << "YES" << " " << c << endl;
    }else{
      cout << "YES" << " " << c+1 << endl;
    }

    
    int cur = 0;
    while(cur<n){
      if(a[cur] == 1){
	g[v.back()].push_back(cur);
	g[cur].push_back(v.back());
	break;
      }
      ++cur;
    }

    int vcur = 0;
    FOR(i,cur+1,n){
      if(a[i] == 1){
	while(g[v[vcur]].size() >= a[v[vcur]]) ++vcur;

	g[v[vcur]].push_back(i);
	g[i].push_back(v[vcur]);
      }
    }
    
    cout << n-1 << endl;
    print_edges(g, 0, -1);
  }
  
  return 0;
}
