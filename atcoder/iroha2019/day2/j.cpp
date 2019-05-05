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

const LLI mod = 1e9+7;

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

struct AddMul{
  LLI val;
  LLI a, b, c;
  bool is_add;
};

AddMul add(LLI a, LLI b, LLI c){
  return AddMul {0, a, b, c, true};
}

AddMul mul(LLI val){
  return AddMul {val, 0, 0, 0, false};
}

AddMul operator*(const AddMul &x, const AddMul &y){
  if(x.is_add and y.is_add){
    return add(x.a, (x.b+x.c*y.a%mod+y.b)%mod, y.c);
  }
  if(x.is_add){
    return add(x.a, x.b, x.c*y.val%mod);
  }
  if(y.is_add){
    return add(x.val*y.a%mod, y.b, y.c);
  }
  return mul(x.val*y.val%mod);
}

ostream& operator<<(ostream &os, const AddMul &x){
  if(x.is_add) os << "(" << x.a << "," << x.b << "," << x.c << ")";
  else os << "(" << x.val << ")";
  return os;
}

LLI calc(const AddMul &x){
  if(x.is_add) return (x.b+x.c)%mod;
  else return x.val;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){
    vector<LLI> A(N); cin >> A;
    string S; cin >> S;

    SegmentTree<AddMul> seg(N, mul(1),
			    [](const AddMul &a, const AddMul &b){return a*b;},
			    [](const AddMul &a, const AddMul &b){return b;});

    REP(i,N){
      if(i==0){
	seg.update(i, add(0, 0, A[i]));
      }else{
	if(S[i-1]=='+'){
	  seg.update(i, add(1, 0, A[i]));
	}else{
	  seg.update(i, mul(A[i]));
	}
      }
    }

    dump(A);
    dump(S);

    int Q; cin >> Q;
    REP(i,Q){
      int T,X,Y; cin >> T >> X >> Y;
      --X;

      if(T==1){
	A[X] = Y;

	if(X==0){
	  seg.update(X, add(0, 0, Y));
	}else{
	  if(S[X-1]=='+'){
	    seg.update(X, add(1, 0, Y));
	  }else{
	    seg.update(X, mul(Y));
	  }
	}

      }else if(T==2){
	S[X] = (S[X] == '*' ? '+' : '*');

	if(S[X] == '*'){
	  seg.update(X+1, mul(A[X+1]));
	}else{
	  seg.update(X+1, add(1, 0, A[X+1]));
	}

      }else{

	if(not seg.get(X,X+1).is_add){
	  LLI val = seg.get(X,X+1).val;
	  seg.update(X, add(0, 0, val));
	  auto res = seg.get(X,Y);
	  LLI ans = calc(res);
	  cout << ans << endl;
	  seg.update(X, mul(val));
	}else{
	  auto res = seg.get(X,Y);
	  LLI ans = calc(res);
	  cout << ans << endl;
	}
      }
    }
  }
  
  return 0;
}
