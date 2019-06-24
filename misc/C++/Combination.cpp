

/*

 */

// 組み合わせ関連の前計算用クラス
template <LLI MOD> class Combination{
public:
  static vector<LLI> facto;
  static vector<LLI> ifacto;

  static void init(int N){
    facto.assign(N+1, 1);
    ifacto.assign(N+1, 1);

    FORE(i,1,N){
      (facto[i] = facto[i-1] * i) %= MOD;
    }

    ifacto[N] = mod_inv(facto[N],MOD);

    REV(i,N-1,0){
      ifacto[i] = ifacto[i+1] * (i+1) % MOD;
    }
  }

  static LLI factorial(LLI i){
    assert(i < facto.size());
    return facto[i];
  }
  
  static LLI factorial_inverse(LLI i){
    assert(i < ifacto.size());
    return ifacto[i];
  }

  static LLI P(LLI n, LLI k);
  static LLI C(LLI n, LLI k);
  static LLI H(LLI n, LLI k);
  static LLI stirling_number(LLI n, LLI k);
  static LLI bell_number(LLI n, LLI k);
  static vector<LLI> montmort_number(int n);
};

template <LLI MOD> vector<LLI> Combination<MOD>::facto = vector<LLI>();
template <LLI MOD> vector<LLI> Combination<MOD>::ifacto = vector<LLI>();

template <LLI MOD> LLI Combination<MOD>::H(LLI n, LLI k){
  if(n == 0 and k == 0) return 1;
  return C(n+k-1, k);
}

template <LLI MOD> LLI Combination<MOD>::C(LLI n, LLI k){
  if(n < k or n < 0 or k < 0) return 0;
  return P(n,k) * factorial_inverse(k) % MOD;
}

template <LLI MOD> LLI Combination<MOD>::P(LLI n, LLI k){
  if(n < k or n < 0 or k < 0) return 0;
  return factorial(n) * factorial_inverse(n-k) % MOD;
}

template <LLI MOD> LLI Combination<MOD>::stirling_number(LLI n, LLI k){
  LLI ret = 0;
  FORE(i,1,k) (ret += ((k-i)%2==0 ? 1 : -1) * (C(k,i) * power(i,n,mod) % mod) + mod) %= mod;
  (ret *= factorial_inverse(k)) %= mod;
  return ret;
}

template <LLI MOD> LLI Combination<MOD>::bell_number(LLI n, LLI k){
  LLI ret = 0;
  FORE(j,1,k) (ret += stirling_number(n,j)) %= mod;
  return ret;
}

template <LLI MOD> vector<LLI> Combination<MOD>::montmort_number(int n){
  vector<LLI> ret(n+1);

  ret[0] = 0;
  ret[1] = 0;
  ret[2] = 1;

  FORE(i,3,n){
    ret[i] = (i-1)*(ret[i-1]+ret[i-2])%MOD;
  }

  return ret;
}
