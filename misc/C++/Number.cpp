#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#endif

/*

 */

template <typename T> LLI power(T n, T p, T m){if(p==0) return 1LL; if(p==1) return n; LLI k = power(n, p/2, m); return ((k*k)%m*(p%2?n:1))%m;}

// mod逆数
template <typename T> LLI mod_inv(T n, T p){return power(n,p-2,p);}

template <typename T> LLI factorial(T n, T m){LLI k = 1LL; FORE(i,1,n) k = (k*i) % m; return k;}
template <typename T> LLI combination(T n, T k, T p){if(n<k||n<0||k<0) return 0; if(n==0||k==0) return 1; return (((n*modInv(k,p))%p)*combination(n-1,k-1,p))%p;}
template <typename T> LLI permutaion(T n, T k, T p){if(n<k||n<0||k<0) return 0; if(n==0||k==0) return 1; return (n * permutaion(n-1,k-1,p)) % p;}

// 組み合わせ関連の前計算用クラス
template <int mod> class Combination{
public:
  vector<LLI> facto = {1};
  vector<LLI> ifacto = {1};

  LLI factorial(int i){
    if(i < 0) throw exception();
    if(facto.size() <= i) facto.resize(i+1, -1);
    if(i == 0) return facto[0] = 1;
    int j = i;
    for(;j>=0;--j) if(facto[j] != -1) break;
    for(int k=j+1; k<=i; ++k) (facto[k] = facto[k-1] * k) %= mod;
    return facto[i];
  }

  LLI factorial_inverse(int i){
    if(i < 0) throw exception();
    if(ifacto.size() <= i) ifacto.resize(i+1, -1);
    if(ifacto[i] != -1) return ifacto[i];
    return ifacto[i] = mod_inv(factorial(i), mod);
  }

  LLI P(int n, int k){
    return (factorial(n) * factorial_inverse(n-k)) % mod;
  }

  LLI C(int n, int k){
    return (P(n,k) * factorial_inverse(k)) % mod;
  }

  LLI H(int n, int k){
    return C(n+k-1, n);
  }
};

// 符号関数
template <typename T> int sign(T n){return (n>0)-(n<0);}

// a/b以上の最小の整数
template <typename T> T ceilGE(T a, T b){if(a % b) return a/b+1-(sign(a)*sign(b)<0?1:0); return a/b;}
// a/bを超える最小の整数
template <typename T> T ceilGT(T a, T b){return a/b+1-(sign(a)*sign(b)<0?1:0);}

// a/b以下の最大の整数
template <typename T> T floorLE(T a, T b){return a/b-(sign(a)*sign(b)<0?1:0);}
// a/b未満の最大の整数
template <typename T> T floorLT(T a, T b){if(a % b) return a/b-(sign(a)*sign(b)<0?1:0); return a/b-1;}

// 二乗判定
template <typename T> bool is_square(T n){T rt = sqrt(n); return rt*rt == n;}

// 約数個数
int count_divisor(LLI n){int count = 0; for(LLI i=1LL; i*i<=n; ++i) if(n%i == 0) ++count; count = count*2-(is_square(n)?1:0); return count;}

// 約数列挙
vector<LLI> divisor_list(LLI n){
  vector<LLI> temp, res;
  for(LLI i=1LL; i*i<n; ++i) if(n%i == 0) temp.push_back(i);
  for(auto i : temp) res.push_back(i);
  if(is_square(n)) res.push_back((LLI)sqrt(n));
  for(auto itr=temp.rbegin(); itr!=temp.rend(); ++itr) res.push_back(n/(*itr));
  return res;
}

vector<bool> prime_table(int n){
  vector<bool> res(n+1, true);
  res[0] = res[1] = false;
  FOR(i,2,n) if(res[i]) for(int j=2*i; j<=n; j+=i) res[j] = false;
  return res;
}

bool is_prime(int n){
  if(n<=1) return false;
  for(int i=2; i*i<=n; ++i){
    if(n%i==0) return false;
  }
  return true;
}

// 素因数分解
vector<LLI> prime_factorize(LLI n){
  vector<LLI> res;
  for(LLI i=2LL; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);
      n/=i;
      --i;
    }
  }
  if(n!=1) res.push_back(n);
  return res;
}

// n以上の最小の2の冪
template <typename T = int> T minimum_power_2(T n){
  T i = 1;
  while(i<n) i = (i<<1);
  return i;
}

// 拡張ユークリッド互除法
tuple<LLI,LLI,LLI> extGCD(LLI a, LLI b){
  if(b == 0) return make_tuple(a,1,0);
  LLI d,p,q;
  tie(d,q,p) = extGCD(b,(a+b)%b);
  return make_tuple(d,p,q-a/b*p);
}

// Chinese Remainder Algorithm
bool CRA(LLI b1, LLI m1, LLI b2, LLI m2, LLI &r, LLI &m){
  LLI p,q,d; tie(d,p,q) = extGCD(m1,m2);
  if((b2-b1) % d != 0) return false;
  m = m1 * m2 / d;
  LLI t = ((b2-b1) * p / d) % (m2 / d);
  r = (b1 + m1 * t + m) % m;
  return true;
}

bool CRA(vector<LLI> &bs, vector<LLI> &ms, LLI &r, LLI &m){
  LLI R=0,M=1;
  REP(i,bs.size()){
    if(!CRA(R,M,bs[i],ms[i],r,m)) return false;
    R = r;
    M = m;
  }
  return true;
}
