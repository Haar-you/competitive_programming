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



template <typename T, typename U> class RangeRangeSegmentTree{
  int size;
  T e1;
  vector<T> vec1;
  function<T(T,T)> f1;
  U e2;
  vector<U> vec2;
  function<U(U,U)> f2;
  function<T(U,T,int)> g;

  void propagate(int i, int l){
    if(vec2[i] == e2) return;
    if(i < size/2){
      vec2[i*2+1] = f2(vec2[i], vec2[i*2+1]);
      vec2[i*2+2] = f2(vec2[i], vec2[i*2+2]);
    }
    vec1[i] = g(vec1[i], vec2[i], l);
    vec2[i] = e2;
  }

  T update_aux(int i, int l, int r, int s, int t, const U &x){
    propagate(i,r-l);
    if(r <= s || t <= l) return vec1[i];
    else if(s <= l && r <= t){
      vec2[i] = f2(vec2[i],x);
      propagate(i,r-l);
      return vec1[i];
    }
    else return vec1[i] = f1(update_aux(i*2+1,l,(l+r)/2,s,t,x), update_aux(i*2+2,(l+r)/2,r,s,t,x));
  }
  
  T query_aux(int i, int l, int r, int x, int y){
    propagate(i,r-l);
    if(r <= x || y <= l) return e1;
    else if(x <= l && r <= y) return vec1[i];
    else return f1(query_aux(i*2+1,l,(l+r)/2,x,y), query_aux(i*2+2,(l+r)/2,r,x,y));
  }
  
public:
  RangeRangeSegmentTree(){}
  RangeRangeSegmentTree(int n, const T &e1, const function<T(T,T)> f1, const U &e2, const function<U(U,U)> f2, const function<T(T,U,int)> g):
    e1(e1), f1(f1), e2(e2), f2(f2), g(g){
    size = 1;
    while(size<n) size*=2;
    size *= 2;
    size -= 1;

    vec1 = vector<T>(size,e1);
    vec2 = vector<U>(size,e2);
  }

  void update(int s, int t, const U &x){
    update_aux(0,0,size/2+1,s,t,x);
  }
  
  T query(int x, int y){
    return query_aux(0,0,size/2+1,x,y);
  }
};

template <typename T> LLI power(T n, T p, T m){
  LLI ret = 1;
  while(p>0){
    if(p&1) (ret *= n) %= m;
    (n *= n) %= m;
    p /= 2;
  }
  return ret;
}

template <typename T> LLI mod_inv(T n, T p){return power(n,p-2,p);}

const LLI mod = 1e9+7;

LLI primes[62] = {2,3,5,7,11,13,17,19,23,29, 31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293};

LLI bits[310];
LLI p_inv[62];

int main(){
  REP(i,62) p_inv[i] = mod_inv(primes[i],mod);

  FORE(i,1,300){
    REP(j,62){
      if(i % primes[j] == 0){
	bits[i] = bits[i] | (1LL<<j);
      }
    }
  }
    

  int n,q;
  while(cin >> n >> q){

    RangeRangeSegmentTree<LLI,LLI> mul_seg(n,
					   1, [](LLI a, LLI b){return (a*b)%mod;},
					   1, [](LLI a, LLI b){return (a*b)%mod;},
					   [](LLI a, LLI b, LLI n){return (a*power(b,n,mod))%mod;}
					   );

    RangeRangeSegmentTree<LLI,LLI> prime_seg(n,
					     0, [](LLI a, LLI b){return a|b;},
					     0, [](LLI a, LLI b){return a|b;},
					     [](LLI a, LLI b, int n){return a|b;}
					     );

    REP(i,n){
      int a; scanf("%d", &a);
      mul_seg.update(i,i+1,a);
      prime_seg.update(i,i+1,bits[a]);
    }


    REP(i,q){
      char s[20]; scanf("%s", s);
      
      if(s[0] == 'M'){
	int l,r,x; scanf("%d %d %d", &l, &r, &x);
	mul_seg.update(l-1,r,x);
	prime_seg.update(l-1,r,bits[x]);
      }else{
	int l,r; scanf("%d %d", &l, &r);

        LLI n = mul_seg.query(l-1,r);
	LLI x = prime_seg.query(l-1,r);

	LLI ans = n;
	REP(i,62) if(x & (1LL<<i)) (ans *= ((primes[i]-1) * p_inv[i]) % mod) %= mod;
        
	printf("%lld\n", ans);
      }
    }
  }
  
  return 0;
}
