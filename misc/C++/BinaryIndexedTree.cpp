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
using namespace std;

//Binary Indexed Tree (1-indexed)
template <typename T> class BIT_1{
private:
  vector<T> tree;
  int n;
public:
  BIT_1(int size): tree(size+1, 0), n(size){}
  void update(int x, T a){while(x <= n){tree[x] += a; x += (x & (-x));}}
  T sum(int x){T a = 0; while(x > 0){a += tree[x]; x -= (x & (-x));} return a;}
  T get(int x){return sum(x) - (x==1 ? 0 : sum(x-1));}
};

//Binary Indexed Tree (0-indexed)
template <typename T> class BIT_0{
private:
  vector<T> tree, vec;
  int n;
  int n_floor2;
  
public:
  BIT_0(int size): tree(size, 0), vec(size, 0), n(size){
    n_floor2 = 1;
    while(n_floor2*2<=n) n_floor2*=2;
  }
  void update(int x, T a){
    vec[x] += a;
    while(x < n){
      tree[x] += a;
      x |= (x + 1);
    }
  }
  T sum(int x){  // [0,x)
    T a = 0;
    --x;
    while(x >= 0){
      a += tree[x];
      x = (x & (x+1)) - 1;
    }
    return a;
  }
  T get(int x){
    return vec[x];
  }
  int lower_bound(int w){
    if(w <= 0) return 0;
    int x = 0;
    
    for(int k = n_floor2; k > 0; k /= 2){
      if(x+k <= n and tree[x+k-1] < w){
	w -= tree[x+k-1];
	x += k;
      }
    }

    return x;
  }
  int upper_bound(int w){
    return lower_bound(w+1);
  }
};
