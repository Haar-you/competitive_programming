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

  int N,M;
  while(cin >> N >> M){
    auto f = [](LLI a, LLI b){return max(a,b);};
    LazySegmentTree<LLI> seg(N, 0, f, f);

    REP(i,M){
      int T,L,R; cin >> T >> L >> R;
      seg.update(L-1,R,T);
    }

    LLI ans = 0;
    REP(i,N) ans += seg.find(i);
    
    cout << ans << endl;
  }
  
  return 0;
}
