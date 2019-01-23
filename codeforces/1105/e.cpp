#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif
#ifdef DEBUG
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
#define pln(x) cout << (x) << endl
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename Iter> ostream& out_container(ostream &os, Iter first, Iter last){
  os << "{"; auto itr = first; while(itr != last){if(itr != first) os << ","; os << *itr; ++itr;} os << "}"; return os;
}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const deque<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const set<T> &c){return out_container(os,ALL(c));}
template <typename T> ostream& operator<<(ostream &os, const unordered_set<T> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream &os, const unordered_map<T,U> &c){return out_container(os,ALL(c));}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

int maximum_independent_set(vector<vector<int>> &graph){
  int n = graph.size();
  int h1 = n/2; //V1
  int h2 = n-h1; //V2

  vector<bool> dp1(1<<h1, true); // dp1[S] := Sが独立集合か?
  REP(i,h1) for(auto j : graph[i]) if(j<h1) dp1[(1<<i)|(1<<j)] = false;
  REP(i,1<<h1) if(!dp1[i]) REP(j,h1) dp1[i|(1<<j)] = false;

  vector<bool> dp2(1<<h2, true); // dp2[S] := Sが独立集合か?
  FOR(i,h1,n) for(auto j : graph[i]) if(j>=h1) dp2[(1<<(i-h1))|(1<<(j-h1))] = false;
  REP(i,1<<h2) if(!dp2[i]) REP(j,h2) dp2[i|(1<<j)] = false;

  vector<int> dp3(1<<h1, 0); // S1と接続しないV2の最大の部分集合
  dp3[0] = (1<<h2)-1;
  REP(i,h1){
    for(auto j : graph[i]) if(j>=h1) dp3[1<<i] |= (1<<(j-h1));
    dp3[1<<i] ^= ((1<<h2)-1);
  }
  REP(i,1<<h1) REP(j,h1) if((i&(1<<j)) == 0) dp3[i|(1<<j)] = dp3[i] & dp3[1<<j];

  vector<int> dp4(1<<h2, 0); // S2の最大独立集合の大きさ
  REP(i,1<<h2) if(dp2[i]) dp4[i] = __builtin_popcount(i);
  REP(i,1<<h2) REP(j,h2) if((i&(1<<j)) == 0) dp4[i|(1<<j)] = max(dp4[i|(1<<j)], dp4[i]);

  int ans = 0;
  REP(i,1<<h1) if(dp1[i]) chmax(ans, __builtin_popcount(i)+dp4[dp3[i]]);
  return ans;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m;
  while(cin >> n >> m){
    vector<int> v;
    vector<unordered_set<int>> sets;
    map<string,int> map1;

    REP(i,n){
      int c; cin >> c;
      if(c == 1){
	v.push_back(-1);
      }else{
	string s; cin >> s;
	if(EXIST(map1,s)){
	  v.push_back(map1[s]);
	}else{
	  int t = map1.size();
	  map1[s] = t;
	  v.push_back(map1[s]);
	}
      }
    }

    REP(i,n){
      if(i<n-1 && v[i] == -1 && v[i+1] != -1){
	sets.push_back(unordered_set<int>());
      }
      if(v[i] != -1){
	sets.back().insert(v[i]);
      }
    }

    vector<vector<int>> graph(m);
    for(auto &u : sets){
      for(auto i : u){
	for(auto j : u){
	  if(i >= j) continue;
	  graph[i].push_back(j);
	  graph[j].push_back(i);
	}
      }
    }

    REP(i,m){
      sort(ALL(graph[i]));
      auto it = unique(ALL(graph[i]));
      graph[i].erase(it,graph[i].end());
    }
    
    int ans = maximum_independent_set(graph);
    pln(ans);
  }

  return 0;
}
