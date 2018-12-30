#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}
template <typename T> LLI modInv(T n, T p){return power(n,p-2,p);}

template <typename T> class BIT_0{
private:
  vector<T> tree;
  int n;
public:
  BIT_0(int size): tree(size, 0), n(size){}
  void update(int x, T a){while(x < n){tree[x] += a; x |= (x + 1);}}
  T sum(int x){T a = 0; while(x >= 0){a += tree[x]; x = (x & (x+1)) - 1;} return a;}
  T get(int x){return sum(x) - (x==0 ? 0 : sum(x-1));}
};

const LLI mod = 998244353;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n; cin >> n;
  vector<LLI> p(n);
  REP(i,n) cin >> p[i];

  LLI ans = 0;

  BIT_0<LLI> bit(n+1);
  vector<int> a;
  REP(i,n) if(p[i]!=-1) a.push_back(p[i]);
  for(LLI i=0;i<a.size();++i){
    (ans += i-bit.sum(a[i])) %= mod;
    bit.update(a[i],1);
  }

  LLI k = count(ALL(p),-1);

  (ans += ((k*(k-1))%mod*modInv(4LL,mod))%mod) %= mod;

  BIT_0<LLI> b1(n+1),b2(n+1);

  LLI c = k;
  REP(i,n){
    if(p[i]==-1) --c;
    else b1.update(p[i],c);
  }

  c = 0;
  REP(i,n){
    if(p[i]==-1) ++c;
    else b2.update(p[i],c);
  }

  set<LLI> s;
  REP(i,n) s.insert(i+1);
  REP(i,n) if(p[i]!=-1) s.erase(p[i]);

  LLI t = 0;
  for(auto x : s){
    (t += b1.sum(n) - b1.sum(x) + b2.sum(x) + mod) %= mod;
  }
  (t *= modInv(k,mod)) %= mod;
  (ans += t) %= mod;
  
  cout << ans << endl;
  
  return 0;
}
