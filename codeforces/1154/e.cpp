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
  
  T get(int x, int y){
    return query_aux(0,0,size/2+1,x,y);
  }
};

using pii = pair<int,int>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n,k;
  while(cin >> n >> k){
    vector<int> a(n); cin >> a;

    vector<pii> b(n);
    REP(i,n) b[i] = {a[i],i};

    pii e = {0,-1};
    RangeRangeSegmentTree<pii,pii> seg
      (n,
       e, [](const pii &a, const pii &b){return max(a,b);},
       e, [&e](const pii &a, const pii &b){return (a==e ? b : a);},
       [&e](const pii &a, const pii &b, int n){return (b==e ? a : b);});

    REP(i,n) seg.update(i,i+1,b[i]);

    vector<int> ans(n);
    int t = 1;

    set<pii, function<bool(pii,pii)>> s([](const pii &a, const pii &b){return a.snd < b.snd;});
    REP(i,n) s.insert(b[i]);
    
    REP(_,n){
      auto m = seg.get(0,n);

      if(m.fst == 0) break;

      auto it = s.lower_bound(m);
      vector<pii> temp = {m};

      int min_id=m.snd, max_id=m.snd;

      auto it_f = next(it);
      REP(i,k){
	if(it_f == s.end()) break;
	temp.push_back(*it_f);
	max_id = it_f->snd;
	it_f = next(it_f);
      }

      auto it_b = it;
      REP(i,k){
	if(it_b == s.begin()) break;
	it_b = prev(it_b);
	temp.push_back(*it_b);
	min_id = it_b->snd;
      }

      for(auto &p : temp) ans[p.snd] = t;

      s.erase(it_b,it_f);

      seg.update(min_id,max_id+1,make_pair(0,0));
      
      t = (t==1 ? 2 : 1);
    }
    
    join(cout, ALL(ans), "");
  }
  
  return 0;
}
