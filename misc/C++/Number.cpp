/*

 */

template <typename T> T power(T n, LLI p, const T &e, const function<T(T,T)> &f){
  T ret = e;
  while(p>0){
    if(p&1) ret = f(ret, n);
    n = f(n, n);
    p /= 2;
  }
  return ret;
}

LLI power(LLI n, LLI p, LLI m){
  LLI ret = 1;
  while(p>0){
    if(p&1) (ret *= n) %= m;
    (n *= n) %= m;
    p /= 2;
  }
  return ret;
}

LLI mod_inv(LLI n, LLI p){return power(n,p-2,p);}

LLI mod_log(LLI a, LLI b, LLI m){
  LLI sq = sqrt(m) + 1;

  unordered_map<LLI,LLI> mp;
  LLI t = 1;
  REP(i,sq){
    if(!EXIST(mp,t)) mp[t] = i;
    (t *= a) %= m;
  }

  LLI p = power(mod_inv(a, m), sq, m);
  LLI t2 = b;
  REP(i,sq){
    if(EXIST(mp,t2)){
      LLI ret = i*sq + mp[t2];
      if(ret>0) return ret;
    }
    (t2 *= p) %= m;
  }

  return -1;
}


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

vector<LLI> prime_factorize_unique(LLI n){
  //  if(n==1) return {1};
  vector<LLI> res;
  for(LLI i=2LL; i*i<=n; ++i){
    if(n%i == 0){
      res.push_back(i);
      while(n%i == 0){
	n/=i;
      }
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


// Möbius関数
/*
  mu(1) = 1
  mu(n) = 0 if nが平方因子を持つ
  mu(n) = (-1)^k if nが相異なるk個の素因数に分解される
  mu(nm) = mu(n) * mu(m) if nとmが互いに素
*/
/*
  問題例
  https://codeforces.com/contest/1139/problem/D
*/
vector<int> mobius(int n){
  vector<int> ret(n+1);
  vector<int> ps;
  ret[1] = 1;
  FORE(i,2,n){
    if(is_prime[i]){
      ps.push_back(i);
      ret[i] = -1;
    }
    for(auto &j : ps){
      if(i*j > n) break;
      if(i%j == 0) ret[i*j] = 0;
      else ret[i*j] = ret[i] * ret[j];
    }
  }
  
  return ret;
}

// 分割数
template <int mod> class partition_number{
  vector<vector<LLI>> dp;

public:
  partition_number(int n, int k): dp(n+1, vector<LLI>(k+1)){
    dp[0][0] = 1;

    FORE(i,0,n){
      FORE(j,1,k){
	if(i-j>=0) dp[i][j] = (dp[i][j-1] + dp[i-j][j]) % mod;
	else dp[i][j] = dp[i][j-1];
      }
    }
  }

  vector<LLI>& operator[](size_t i){return dp[i];}
};

