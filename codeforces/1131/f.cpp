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

class UnionFind{
  vector<int> _parent, _depth, _size;
public:
  UnionFind(int n): _parent(n), _depth(n,1), _size(n,1){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else return _parent[i] = root(_parent[i]);
  }
  bool same(int i, int j){return root(i) == root(j);}
  void merge(int i, int j){
    int ri = root(i), rj = root(j);
    if(ri != rj){
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri];
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
      }
    }
  }
  int size(int i){return _size[root(i)];}
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  while(cin >> n){

    vector<deque<int>> ds(n);
    UnionFind uf(n);
    REP(i,n) ds[i].push_back(i);

    REP(i,n-1){
      int x,y; cin >> x >> y; --x, --y;
      int rx = uf.root(x), ry = uf.root(y);
      uf.merge(x,y);

      auto &dqx = ds[rx];
      auto &dqy = ds[ry];

      if(dqx.size() > dqy.size()){
	if(dqx.front() == x){
	  if(dqy.front() == y){
	    while(!dqy.empty()){
	      dqx.push_front(dqy.front());
	      dqy.pop_front();
	    }
	  }else{
	    while(!dqy.empty()){
	      dqx.push_front(dqy.back());
	      dqy.pop_back();
	    }
	  }
	}else{
	  if(dqy.front() == y){
	    while(!dqy.empty()){
	      dqx.push_back(dqy.front());
	      dqy.pop_front();
	    }
	  }else{
	    while(!dqy.empty()){
	      dqx.push_back(dqy.back());
	      dqy.pop_back();
	    }
	  }
	}
      }else{
	if(dqy.front() == y){
	  if(dqx.front() == x){
	    while(!dqx.empty()){
	      dqy.push_front(dqx.front());
	      dqx.pop_front();
	    }
	  }else{
	    while(!dqx.empty()){
	      dqy.push_front(dqx.back());
	      dqx.pop_back();
	    }
	  }
	}else{
	  if(dqx.front() == x){
	    while(!dqx.empty()){
	      dqy.push_back(dqx.front());
	      dqx.pop_front();
	    }
	  }else{
	    while(!dqx.empty()){
	      dqy.push_back(dqx.back());
	      dqx.pop_back();
	    }
	  }
	}
      }
      
      if(uf.root(x) == rx){
	if(dqx.empty()) dqx.swap(dqy);
      }else{
	if(dqy.empty()) dqx.swap(dqy);
      }
    }
    

    REP(i,n){
      if(!ds[i].empty()){
	auto ans(ds[i]);

	for(auto &x : ans) ++x;
        
	join(cout, ALL(ans));
	break;
      }
    }
  }
  
  return 0;
}
