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
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

/*


 */

template <typename T> class SqrtDecomposition_RangeGet{
  vector<T> vec, buckets;
  int n;
  int sq;
  T id;
  function<T(T,T)> op;

public:
  SqrtDecomposition_RangeGet(int n, const T &id, const function<T(T,T)> op): n(n), id(id), op(op), sq(sqrt(n)+1){
    vec.assign(n, id);
    buckets.assign(sq, id);
  }

  void update(int x, const T& val){
    vec[x] = op(vec[x], val);
    T t = id;
    int k = x / sq;
    for(int i = k*sq; i < (k+1)*sq && i < n; ++i) t = op(t, vec[i]);
    buckets[k] = t;
  }

  T get(int x, int y){
    T ret = id;
    REP(k,sq){
      int l = k*sq, r = (k+1)*sq;
      if(r <= x || y <= l) continue;
      if(x <= l && r <= y) ret = op(ret, buckets[k]);
      else FOR(i,max(x,l),min(y,r)) ret = op(ret, vec[i]);
    }
    return ret;
  }
};


template <typename T> class SqrtDecomposition_RangeUpdate{
  vector<T> vec, buckets;
  int n;
  int sq;
  T id;
  function<T(T,T)> op;

public:
  SqrtDecomposition_RangeUpdate(int n, const T &id, const function<T(T,T)> op): n(n), id(id), op(op), sq(sqrt(n)+1){
    vec.assign(n, id);
    buckets.assign(sq, id);
  }

  void update(int x, int y, const T& val){
    REP(k,sq){
      int l = k*sq, r = (k+1)*sq;
      if(r <= x || y <= l) continue;
      if(x <= l && r <= y) buckets[k] = op(buckets[k], val);
      else FOR(i,max(x,l),min(y,r)) vec[i] = op(vec[i], val);
    }
  }

  T get(int x){
    int k = x / sq; 
    return op(vec[x], buckets[k]);
  }
};
