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
template <typename I> void cout_join(I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)cout<<d;cout<<*i;}cout<<endl;}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m; cin >> n >> m;

  vector<int> p(2*n);
  REP(i,2*n){
    cin >> p[i];
  }

  map<int,int> pairs;
  REP(i,m){
    int a,b; cin >> a >> b;
    --a; --b;
    pairs[a] = b;
    pairs[b] = a;
  }

  vector<bool> check(2*n,false);

  int t; cin >> t;

  bool f = false;

  REP(_,2*n){
    if(t == 1){
      if(f){
	f = false;
      }else if(!pairs.empty()){
	int a;
	for(auto kv : pairs){
	  if(p[kv.first] >= p[kv.second]){
	    a = kv.first;
	    break;
	  }
	}
	cout << a+1 << endl << flush;

	pairs.erase(pairs[a]);
	pairs.erase(a);
	
	check[a] = true;
      }else{
	int mx=0,cr=0;
	REP(i,2*n){
	  if(p[i] > mx && !check[i]){
	    mx = p[i];
	    cr = i;
	  }
	}
	cout << cr+1 << endl << flush;

	check[cr] = true;
      }
    }else{
      int a; cin >> a;

      --a;
      check[a] = true;

      if(pairs.find(a) != pairs.end()){

	cout << pairs[a]+1 << endl << flush;
	check[pairs[a]] = true;

	pairs.erase(pairs[a]);
	pairs.erase(a);
        
	f = true;
      }
    }

    t = (t==1) ? 2 : 1;
  }
  
  return 0;
}
