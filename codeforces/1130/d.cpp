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
  SegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd):  f(f), e(e), upd(upd){
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

  T find(int x, int y){return aux(x,y,0,0,(size+1)/2);}
};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, m;
  while(cin >> n >> m){
    vector<vector<int>> c(n);

    REP(i,m){
      int a,b; cin >> a >> b;
      --a, --b;
      c[a].push_back(b);
    }

    int size = 0;
    REP(i,n) chmax(size, c[i].size());

    auto dist = [&](int x, int y){return (x>=y ? y+n-x : y-x);};
    
    vector<int> c2(2*n,-1);
    vector<int> c3(2*n,-1);

    REP(i,n){
      sort(ALL(c[i]), [&](int x, int y){return dist(i,x) < dist(i,y);});

      if(size == 1){
	if(c[i].size() == 1){
	  c2[i] = c[i][0];
	}
      }else{
	if(c[i].size() == size){
	  c2[i] = c[i][0];
	  c3[i] = c[i][1];
	}else if(c[i].size() == size-1){
	  c3[i] = c[i][0];
	}
      }
    }

    REP(i,n) if(c3[i] >= 0 && c3[i] < i) c3[i] += n;
    REP(i,n) if(c3[i] >= 0) c3[i+n] = c3[i] + n;

    REP(i,n) if(c2[i] == 0) c2[i] = n;
    REP(i,n) if(c2[i] >= 0 && c2[i] < i) c2[i] += n;
    REP(i,n) if(c2[i] >= 0) c2[i+n] = c2[i] + n;

    auto f = [](int x, int y){return max(x,y);};
    auto g = [](int x, int y){return y;};
    SegmentTree<int> seg(2*n, -1, f, g);
    REP(i,2*n) seg.update(i, c2[i]);
    
    SegmentTree<int> seg2(2*n, -1, f, g);
    REP(i,2*n) seg2.update(i, c3[i]);

    vector<LLI> ans(n);
    REP(i,n){
      int t = seg.find(i,i+n) - i;
      int s = seg2.find(i,i+n) - i - n;
      ans[i] = n*(size-1) + max(t,s);
    }
    join(cout, ALL(ans));
  }
  
  return 0;
}


/*
EditorialのO(n^2+m)解法を基にした解答

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, m;
  while(cin >> n >> m){
    vector<vector<int>> c(n);

    REP(i,m){
      int a,b; cin >> a >> b;
      --a, --b;
      c[a].push_back(b);
    }

    auto dist = [&](int x, int y){return (x>y ? y+n-x : y-x);};

    REP(i,n){
      sort(ALL(c[i]), [&](int x, int y){return dist(i,x) < dist(i,y);});
    }

    vector<LLI> ans(n);
    REP(i,n){
      LLI t = 0;
      REP(j,n){
	if(c[j].size() == 0) continue;
	LLI x = dist(i,j) + n*(c[j].size()-1) + dist(j,c[j][0]);
	chmax(t, x);
      }
      ans[i] = t;
    }
    join(cout, ALL(ans));
  }
  
  return 0;
}
*/
