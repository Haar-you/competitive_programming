#include <bits/stdc++.h>
#define LLI long long int
#define FOR(v, a, b) for(LLI v = (a); v < (b); ++v)
#define FORE(v, a, b) for(LLI v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(LLI v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define fst first
#define snd second
#define popcount __builtin_popcount
#define UNIQ(v) (v).erase(unique(ALL(v)), (v).end())
#define bit(i) (1LL<<(i))

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(...) ((void)0)
#endif

#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}


/**
 * @brief 0-indexedのbinary indexed tree
 */
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
  
  T get(int x){ // [0,x)
    T a = 0;
    --x;
    while(x >= 0){
      a += tree[x];
      x = (x & (x+1)) - 1;
    }
    return a;
  }

  T get(int x, int y){ // [x,y)
    return get(y) - get(x);
  }
  
  T at(int x){
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




const LLI mod = 998244353;

template <uint32_t M> class ModInt{
public:
  uint64_t val;
  ModInt(): val(0){}
  ModInt(int64_t n): val(n>=M ? n%M : n){}
  
  inline constexpr ModInt operator+(const ModInt &a) const {return ModInt((val+a.val)%M);}
  inline constexpr ModInt operator-(const ModInt &a) const {return ModInt((val-a.val+M)%M);}
  inline constexpr ModInt operator*(const ModInt &a) const {return ModInt((val*a.val)%M);}
  inline constexpr ModInt operator/(const ModInt &a) const {return ModInt((val*a.inv().val)%M);}
  
  inline constexpr ModInt& operator=(const ModInt &a){val = a.val; return *this;}
  inline constexpr ModInt& operator+=(const ModInt &a){if((val += a.val) >= M) val -= M; return *this;}
  inline constexpr ModInt& operator-=(const ModInt &a){if(val < a.val) val += M; val -= a.val; return *this;}
  inline constexpr ModInt& operator*=(const ModInt &a){(val *= a.val) %= M; return *this;}
  inline constexpr ModInt& operator/=(const ModInt &a){(val *= a.inv().val) %= M; return *this;}

  inline constexpr bool operator==(const ModInt &a) const {return val==a.val;}
  inline constexpr bool operator!=(const ModInt &a) const {return val!=a.val;}

  inline constexpr static ModInt power(LLI a, LLI p){
    ModInt ret = 1, e = a;
    for(; p; e *= e, p >>= 1) if(p&1) ret *= e;
    return ret;
  }

  inline constexpr ModInt power(LLI p) const{
    ModInt ret = 1, e = val;
    for(; p; e *= e, p >>= 1) if(p&1) ret *= e;

    return ret;
  }
  
  inline constexpr ModInt inv() const{
    int64_t a = val, b = M, u = 1, v = 0;

    while(b){
      int64_t t = a/b;
      a -= t*b; swap(a,b);
      u -= t*v; swap(u,v);
    }
    u %= M;
    if(u < 0) u += M;
    
    return u;
  }
};

template <uint32_t M> ModInt<M> operator+(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)+b.val);}
template <uint32_t M> ModInt<M> operator-(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)-b.val);}
template <uint32_t M> ModInt<M> operator*(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)*b.val);}
template <uint32_t M> ModInt<M> operator/(int64_t a, const ModInt<M> &b){return ModInt<M>(ModInt<M>(a)/b.val);}

template <uint32_t M> istream& operator>>(istream &is, ModInt<M> &a){is >> a.val; return is;}
template <uint32_t M> ostream& operator<<(ostream &os, const ModInt<M> &a){ os << a.val; return os;}

using mint = ModInt<mod>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  vector<mint> pow2(300000,1);
  FORE(i,1,200000){
    pow2[i] = pow2[i-1] * 2;
  }


  int N;
  while(cin >> N){
    vector<pair<int,int>> p(N);
    vector<int> xs, ys;
    
    REP(i,N){
      int x, y; cin >> x >> y;
      p[i] = make_pair(x,y);
      xs.push_back(x);
      ys.push_back(y);
    }

    sort(ALL(xs));
    UNIQ(xs);
    sort(ALL(ys));
    UNIQ(ys);

    REP(i,N){
      p[i].fst = lower_bound(ALL(xs), p[i].fst) - xs.begin();
      p[i].snd = lower_bound(ALL(ys), p[i].snd) - ys.begin();
    }
    
    sort(ALL(p));

    
    BIT_0<int> seg1(ys.size()), seg2(ys.size());
    

    REP(i,N){
      seg1.update(p[i].snd, 1);
    }

    vector<vector<int>> a(xs.size());
    REP(i,N){
      a[p[i].fst].push_back(p[i].snd);
    }

    mint ans = 0;

    /*
             |  |
         k2  |c2|  k3
      _______|__|_______
         c1  |  |  c3
      _______|__|_______
             |  |
         k1  |c4|  k4
             |  |
     */


    REP(i,N){
      int x = p[i].fst, y = p[i].snd;

      int c1 = seg2.get(y,y+1);
      int c3 = seg1.get(y,y+1) - c1 - 1;
      int c4 = lower_bound(ALL(a[x]), y) - a[x].begin();
      int c2 = a[x].size() - c4 - 1;

      int k1 = seg2.get(0,y) - c4;
      int k2 = seg2.get(y+1,ys.size());
      int k3 = seg1.get(y+1,ys.size()) - k2 - c2;
      int k4 = seg1.get(0,y) - k1 - c4;

      int cs = c1+c2+c3+c4;

      //4
      ans += (pow2[k1]-1) * (pow2[k2]-1) * (pow2[k3]-1) * (pow2[k4]-1) * pow2[cs+1];
      
      //3
      ans += (
              (pow2[k1]-1) * (pow2[k2]-1) * (pow2[k3]-1) +
              (pow2[k1]-1) * (pow2[k2]-1) * (pow2[k4]-1) +
              (pow2[k1]-1) * (pow2[k3]-1) * (pow2[k4]-1) +
              (pow2[k2]-1) * (pow2[k3]-1) * (pow2[k4]-1)
              ) * pow2[cs+1];

      //2
      ans +=
        (pow2[k1]-1) * (pow2[k2]-1) * (pow2[cs+1] - (1 + (pow2[c1]-1))) + 
        (pow2[k2]-1) * (pow2[k3]-1) * (pow2[cs+1] - (1 + (pow2[c2]-1))) + 
        (pow2[k3]-1) * (pow2[k4]-1) * (pow2[cs+1] - (1 + (pow2[c3]-1))) + 
        (pow2[k4]-1) * (pow2[k1]-1) * (pow2[cs+1] - (1 + (pow2[c4]-1))) +
        (pow2[k1]-1) * (pow2[k3]-1) * pow2[cs+1] + 
        (pow2[k2]-1) * (pow2[k4]-1) * pow2[cs+1];
      
      //1
      ans +=
        (pow2[k1]-1) * (pow2[cs+1] - (1 + (pow2[c1]-1) + (pow2[c4]-1))) +
        (pow2[k2]-1) * (pow2[cs+1] - (1 + (pow2[c2]-1) + (pow2[c1]-1))) +
        (pow2[k3]-1) * (pow2[cs+1] - (1 + (pow2[c3]-1) + (pow2[c2]-1))) +
        (pow2[k4]-1) * (pow2[cs+1] - (1 + (pow2[c4]-1) + (pow2[c3]-1)));
      
      //0
      ans += pow2[cs] + (pow2[cs] - (1 + (pow2[c1]-1) + (pow2[c2]-1) + (pow2[c3]-1) + (pow2[c4]-1)));
      
      seg2.update(y,1);
    }
    
    cout << ans << endl;    
  }
  
  return 0;
}
