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

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

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

  T get_at(int x){
    return query(x,x+1);
  }
};






int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){
    vector<LLI> a(n); cin >> a;
    vector<LLI> k(n-1); cin >> k;

    int q; cin >> q;

    auto f = [](LLI a, LLI b){return a+b;};
    auto f2 = [](LLI a, LLI b, int n){return a+b*n;};
    auto h = [](LLI a, LLI b){return (a==LLONG_MIN ? b : a);};
    auto h2 = [](LLI a, LLI b, int n){return (b==LLONG_MIN ? a : b*n);};

    RangeRangeSegmentTree<LLI,LLI> seg1(n, 0, f, 0, f, f2), seg2(n, 0, f, LLONG_MIN, h, h2);

    REP(i,n-1){
      seg1.update(i+1,n,k[i]);
    }

    REP(i,n){
      seg2.update(i,i+1,a[i]-seg1.get_at(i));
    }
    
    REP(_,q){
      char op; cin >> op;

      if(op == '+'){
	LLI i,x; cin >> i >> x; --i;

	
	LLI p = seg2.get_at(i) + x;

	int lb = i, ub = n, mid;
	while(abs(lb-ub) > 1){
	  mid = (lb+ub) / 2;
	  if(seg2.get_at(mid) >= p){
	    ub = mid;
	  }else{
	    lb = mid;
	  }
	}

	seg2.update(i,ub,p);

      }else{
	LLI l,r; cin >> l >> r; --l;

	LLI ans = seg1.query(l,r) + seg2.query(l,r);
	cout << ans << endl;
      }
    }
  }
  
  return 0;
}
