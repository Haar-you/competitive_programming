#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
using namespace std;

// 畳み込み演算とか

// fast mobius transform for subsets
// f(S) = ∑_{T⊆S} g(T) * (-1)^(|S|-|T|)
// verified at https://onlinejudge.u-aizu.ac.jp/challenges/search/volumes/2446 (包除原理への応用)
template <typename T> void fast_mobius_transform_subset(vector<T> &f){
  for(int i=0; (1<<i) < f.size(); ++i){
    REP(j,f.size()){
      if(j & (1<<i)) f[j] -= f[j ^ (1<<i)];
    }
  }
}

// fast mobius transform for supersets
// f(S) = ∑_{S⊆T} g(T) * (-1)^(|T|-|S|)
template <typename T> void fast_mobius_transform_superset(vector<T> &f){
  for(int i=0; (1<<i) < f.size(); ++i){
    REP(j,f.size()){
      if(!(j & (1<<i))) f[j] -= f[j ^ (1<<i)];
    }
  }
}

// fast zeta transform for subsets
// f(S) = ∑_{T⊆S} g(T)
// verified at https://atcoder.jp/contests/arc100/tasks/arc100_c (演算がやや特殊)
template <typename T> void fast_zeta_transform_subset(vector<T> &f){
  for(int i=0; (1<<i) < f.size(); ++i){
    REP(j,f.size()){
      if(j & (1<<i)) f[j] += f[j ^ (1<<i)];
    }
  }
}

// fast zeta transform for supersets
// f(S) = ∑_{S⊆T} g(T)
template <typename t> void fast_zeta_transform_superset(vector<T> &f){
  for(int i=0; (1<<i) < f.size(); ++i){
    REP(j,f.size()){
      if(!(j & (1<<i))) f[j] += f[j ^ (1<<i)];
    }
  }
}
