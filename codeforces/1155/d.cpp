#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
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
  
  T aux(int x, int y, int i, int l, int r){
    if(r<=x || y<=l) return e;
    else if(x<=l && r<=y) return vec[i];
    else return f(aux(x,y,i*2+1,l,(l+r)/2), aux(x,y,i*2+2,(l+r)/2,r));
  };

public:
  SegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd): e(e), f(f), upd(upd){
    size = 1;
    while(size < n) size *= 2;
    size = size*2-1;
    vec = vector<T>(size, e);
  }
  void update(int i, T x){
    int j = i+(size+1)/2-1;
    vec[j] = upd(vec[j], x);
    --j;
    while(j>=0){
      vec[j/2] = f(vec[(j/2)*2+1], vec[(j/2)*2+2]);
      (j /= 2) -= 1;
    }
  }

  T get(int x, int y){return aux(x,y,0,0,(size+1)/2);}
};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,x;
  while(cin >> n >> x){
    vector<LLI> a(n); cin >> a;

    vector<LLI> sum(n+1);
    REP(i,n) sum[i+1] = sum[i] + a[i];

    dump(sum);

    SegmentTree<LLI> seg1(n+1, LLONG_MIN, [](LLI a, LLI b){return max(a,b);}, [](LLI a, LLI b){return b;});
    vector<LLI> dp1(n+1);

    LLI temp = 0;
    REPE(i,n){
      chmin(temp, sum[i]);
      dp1[i] = sum[i] - temp;
      seg1.update(i, sum[i]-temp+x*(sum[n]-sum[i]));
    }

    dump(dp1);

    SegmentTree<LLI> seg2(n+1, LLONG_MIN, [](LLI a, LLI b){return max(a,b);}, [](LLI a, LLI b){return b;});
    vector<LLI> dp2(n+1);
    
    REPE(i,n){
      if(i>0) dp2[i] = max(dp1[i], seg1.get(0,i)-x*(sum[n]-sum[i]));
      seg2.update(i, dp2[i]+sum[n]-sum[i]);
    }

    dump(dp2);

    vector<LLI> dp3(n+1);

    REPE(i,n){
      if(i>0) dp3[i] = max(dp2[i], seg2.get(0,i)-(sum[n]-sum[i]));
    }

    dump(dp3);

    LLI ans = *max_element(ALL(dp3));

    cout << ans << endl;
  }
  
  return 0;
}
