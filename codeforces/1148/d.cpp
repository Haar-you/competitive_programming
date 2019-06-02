#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())
#define bit(i) (1LL<<i)
#define sz(v) ((LLI)(v).size())

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

template <typename T> class SegmentTree{
private:
  int size;
  vector<T> vec;
  T e;
  function<T(T,T)> f, upd;
  
  inline T aux(int x, int y, int i, int l, int r){
    if(r<=x || y<=l) return e;
    else if(x<=l && r<=y) return vec[i];
    else return f(aux(x,y,i*2+1,l,(l+r)/2), aux(x,y,i*2+2,(l+r)/2,r));
  };

public:
  SegmentTree(int n, const T &e, const function<T(T,T)> &f, const function<T(T,T)> &upd): e(e), f(f), upd(upd){
    size = 1;
    while(size < n) size *= 2;
    size = size*2-1;
    vec = vector<T>(size, e);
  }

  inline void update(int i, const T &x){
    int j = i+(size+1)/2-1;
    vec[j] = upd(vec[j], x);
    --j;
    while(j>=0){
      vec[j/2] = f(vec[(j/2)*2+1], vec[(j/2)*2+2]);
      (j /= 2) -= 1;
    }
  }

  inline T get(int x, int y){return aux(x,y,0,0,(size+1)/2);}
};

vector<int> solve1(int n, const vector<int> &a, const vector<int> &b){
  vector<int> x, y;
  map<int,int> m;
  REP(i,n){
    if(a[i] < b[i]){
      x.push_back(a[i]);
      y.push_back(b[i]);
    }
    m[b[i]] = i;
  }
  dump(x);
  dump(y);

  if(x.size() == 0) return {};

  vector<int> ret;

  auto f = [](int i, int j){return max(i,j);};
  SegmentTree<int> seg(2*n+1, 0, f, [](int i, int j){return j;});

  REP(i,(int)x.size()){
    seg.update(x[i], y[i]);
  }

  int c;
  {
    c = seg.get(0,2*n+1);
    int i = m[c];
    int k = a[i];
    dump(k);
    
    seg.update(k, 0);
    ret.push_back(i);
  }
  
  while(1){
    c = seg.get(0,c);
    if(c == 0) break;
    int i = m[c];
    int k = a[i];

    seg.update(k, 0);
    ret.push_back(i);
  }
  
  return ret;
}



vector<int> solve2(int n, const vector<int> &a, const vector<int> &b){
  vector<int> x, y;
  map<int,int> m;
  REP(i,n){
    if(a[i] > b[i]){
      x.push_back(a[i]);
      y.push_back(b[i]);
    }
    m[b[i]] = i;
  }
  dump(x);
  dump(y);

  if(x.size() == 0) return {};

  vector<int> ret;

  auto f = [](int i, int j){return min(i,j);};
  SegmentTree<int> seg(2*n+1, INT_MAX, f, [](int i, int j){return j;});

  REP(i,(int)x.size()){
    seg.update(x[i], y[i]);
  }

  int c;
  {
    c = seg.get(0,2*n+1);
    int i = m[c];
    int k = a[i];
    dump(k);
    
    seg.update(k, INT_MAX);
    ret.push_back(i);
  }
  
  while(1){
    c = seg.get(c,2*n+1);
    if(c == INT_MAX) break;
    int i = m[c];
    int k = a[i];

    seg.update(k, INT_MAX);
    ret.push_back(i);
  }
  
  return ret;
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<int> a(n), b(n);
    REP(i,n) cin >> a[i] >> b[i];

    auto ans1 = solve1(n,a,b);
    auto ans2 = solve2(n,a,b);

    for(auto &x: ans1) ++x;
    for(auto &x: ans2) ++x;

    if(ans1.size() >= ans2.size()){
      cout << ans1.size() << endl;
      join(cout, ALL(ans1));
    }else{
      cout << ans2.size() << endl;
      join(cout, ALL(ans2));
    }
  }
  
  return 0;
}
