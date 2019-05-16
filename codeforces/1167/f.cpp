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

template <typename T, typename U> class RAQ_RSQ{
  int size;
  vector<T> vec1;
  vector<U> vec2;

  inline void propagate(int i, int l){
    if(vec2[i] == 0) return;
    if(i < size/2){
      vec2[i*2+1] = vec2[i] + vec2[i*2+1];
      vec2[i*2+2] = vec2[i] + vec2[i*2+2];
    }
    vec1[i] = vec1[i] + vec2[i] * l;
    vec2[i] = 0;
  }

  inline T update_aux(int i, int l, int r, int s, int t, const U &x){
    propagate(i,r-l);
    if(r <= s || t <= l) return vec1[i];
    else if(s <= l && r <= t){
      vec2[i] = vec2[i] + x;
      propagate(i,r-l);
      return vec1[i];
    }
    else return vec1[i] = update_aux(i*2+1,l,(l+r)/2,s,t,x) + update_aux(i*2+2,(l+r)/2,r,s,t,x);
  }
  
  inline T query_aux(int i, int l, int r, int x, int y){
    propagate(i,r-l);
    if(r <= x || y <= l) return 0;
    else if(x <= l && r <= y) return vec1[i];
    else return query_aux(i*2+1,l,(l+r)/2,x,y) + query_aux(i*2+2,(l+r)/2,r,x,y);
  }
  
public:
  RAQ_RSQ(){}
  RAQ_RSQ(int n){
    size = 1;
    while(size<n) size*=2;
    size *= 2;
    size -= 1;

    vec1 = vector<T>(size,0);
    vec2 = vector<U>(size,0);
  }

  inline void update(int s, int t, const U &x){
    update_aux(0,0,size/2+1,s,t,x);
  }
  
  inline T get(int x, int y){
    return query_aux(0,0,size/2+1,x,y);
  }
};


const LLI mod = 1e9+7;


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n;
  while(cin >> n){
    vector<LLI> a(n); cin >> a;

    vector<pair<int,int>> m;

    REP(i,n) m.push_back({a[i], i});
    sort(ALL(m));
    
    RAQ_RSQ<LLI,LLI> seg_l(n);
    RAQ_RSQ<LLI,LLI> seg_r(n);
    
    LLI ans = 0;

    for(auto &kv : m){
      LLI i = kv.snd;
      
      seg_l.update(0,i+1,1);
      seg_r.update(i,n,1);
      
      LLI l = seg_l.get(0,i+1);
      LLI r = seg_r.get(i,n);

      LLI dl = (i+1)*(seg_l.get(i,i+1)-1);
      LLI dr = (n-i)*(seg_r.get(i,i+1));

      l -= dl;
      r -= dr;

      l %= mod;
      r %= mod;

      LLI t = (l * (n-i) % mod + (i+1) * r % mod) % mod;

      (t *= kv.fst) %= mod;
      
      (ans += t) %= mod;
    }

    cout << ans << endl;
  }
  
  return 0;
}
