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

class my_rand{
public:
  mt19937 r;
  my_rand(){
    r = mt19937(static_cast<unsigned int>(time(nullptr)));
  }
};


class Interactive{
public:
  int n;
  int x1;
  int d;
  vector<int> a;
  vector<int> sorted;
  my_rand rand;
  int query = 0;
  
  Interactive(){
    x1 = rand.r() % 100001;
    d = rand.r() % 1000001;
    int t = min(1000000, (int)((1000000000-x1)/d+1));
    n = rand.r() % t + 1;

    REP(i,n){
      sorted.push_back(x1+d*i);
    }

    a = vector<int>(sorted);
    shuffle(ALL(a), rand.r);
  }

  int get_n(){
#ifdef DEBUG
    return n;
#else
    int N;
    cin >> N;
    return N;
#endif
  }

  int query_get_ai(int i){
    if(query >= 60) return -1;
    ++query;
    cout << "? " << i << endl;
#ifdef DEBUG
    return a[i-1];
#else
    int ai;
    cin >> ai;
    return ai;
#endif
  }

  int query_gt_x(int x){
    if(query >= 60) return -1;
    ++query;
    cout << "> " << x << endl;
#ifdef DEBUG
    return sorted.back() > x;
#else
    int ret;
    cin >> ret;
    return ret;
#endif
  }

  void answer(int X, int D){
    cout << "! " << X << " " << D << endl;
#ifdef DEBUG
    if(X == x1 && D == d){
      cerr << "AC" << endl;
    }else{
      cerr << "WA" << endl;
    }
#endif
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  Interactive inte;

  int n = inte.get_n();

  int lower=-1, upper=1e9, m;
  while(lower+1 < upper){
    m = (lower + upper) / 2;

    if(inte.query_gt_x(m)){
      lower = m;
    }else{
      upper = m;
    }
  }
  if(inte.query_gt_x(m)) ++m;
  
  dump(inte.sorted.back());
  dump(m);
  
  my_rand rand;
  vector<int> a;
  unordered_set<int> mem;
  REP(i,60){
    int k = rand.r() % n + 1;
    if(mem.size() >= n) break;
    if(EXIST(mem,k)){
      --i;
      continue;
    }

    int p = inte.query_get_ai(k);
    if(p == -1) break;

    a.push_back(p);
    mem.insert(k);
  }
  sort(ALL(a));
  vector<int> diffs;
  FOR(i,1,a.size()) diffs.push_back(a[i]-a[i-1]);
  
  int d = 0;
  for(auto b : diffs) d = gcd(d, b);
  
  dump(d);
  dump(inte.d);

  int x1 = m - d*(n-1);

  inte.answer(x1,d);
  
  
  return 0;
}
