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

template <typename T> class LazySegmentTree{
private:
  int size;
  vector<T> vec;
  function<T(T,T)> f, upd;
  T e;
  void propagate(int i){
    if(i<size/2){
      vec[i*2+1] = f(vec[i], vec[i*2+1]);
      vec[i*2+2] = f(vec[i], vec[i*2+2]);
      vec[i] = e;
    }
  }
  void update_aux(int s, int t, int i, int l, int r, T x){
    if(r <= s || t <= l) return;
    else if(s <= l && r <= t) vec[i] = upd(vec[i],x);
    else{
      propagate(i);
      update_aux(s,t,i*2+1,l,(l+r)/2,x);
      update_aux(s,t,i*2+2,(l+r)/2,r,x);
    }
  }
  void find_aux(int i){if(i>0) find_aux((i-1)/2); propagate(i);}
public:
  LazySegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd): f(f), e(e), upd(upd){
    size = 1;
    while(size < n) size *= 2;
    size = size*2-1;
    vec = vector<T>(size, e);
  }
  void update(int s, int t, T x){update_aux(s,t,0,0,size/2+1,x);}
  T find(int i){
    int j=i+size/2;
    find_aux((j-1)/2);
    return vec[j];
  }
};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,m;
  while(cin >> n >> m){
    vector<int> a(n); cin >> a;
    vector<pair<int,int>> s(m); cin >> s;

    vector<pair<int,vector<int>>> res(n);

    REP(i,n){
      LazySegmentTree<int> seg(n,0,[](int a, int b){return a+b;},[](int a, int b){return a+b;});
      REP(j,n) seg.update(j,j+1,a[j]);

      REP(j,m){
	auto &p = s[j];
	if(i+1>=p.fst && i+1<=p.snd){
	  seg.update(p.fst-1,p.snd,-1);
	  res[i].snd.push_back(j+1);
	}
      }

      vector<int> t(n);
      REP(j,n) t[j] = seg.find(j);
      sort(ALL(t));
      int d = t.back() - t.front();
      res[i].fst = d;
    }

    sort(ALL(res));
    reverse(ALL(res));
    auto ans = res.front();

    cout << ans.fst << endl;
    cout << ans.snd.size() << endl;
    join(cout, ALL(ans.snd));
  }
  
  return 0;
}
