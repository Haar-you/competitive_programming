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
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m*n/gcd(m,n);}

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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m;
  while(cin >> n >> m){
    vector<int> a(n); cin >> a;
    vector<pair<int,int>> s(m); cin >> s;

    vector<int> ps;
    REP(i,m){
      ps.push_back(s[i].fst);
      ps.push_back(s[i].snd);
    }

    sort(ALL(ps));
    auto it = unique(ALL(ps));
    ps.erase(it,ps.end());
    
    vector<pair<int,vector<int>>> res(ps.size()+1);
    
    REP(i,ps.size()){
      vector<int> t(n+1);

      REP(j,m){
	auto &p = s[j];
	if(ps[i]>=p.fst && ps[i]<=p.snd){
	  --t[p.fst-1];
	  ++t[p.snd];
	  
	  res[i].snd.push_back(j+1);
	}
      }
      
      REPE(j,n) if(j>0) t[j] += t[j-1];
      t.pop_back();

      REP(j,n) t[j] += a[j];

      int d = *max_element(ALL(t)) - *min_element(ALL(t));
      res[i].fst = d;
    }

    {
      int d = *max_element(ALL(a)) - *min_element(ALL(a));
      res.back().fst = d;
    }

    sort(ALL(res), [](pair<int,vector<int>> &a, pair<int,vector<int>> &b){return a.fst < b.fst;});
    auto ans = res.back();

    cout << ans.fst << endl;
    cout << ans.snd.size() << endl;
    join(cout, ALL(ans.snd));
  }
  
  return 0;
}
