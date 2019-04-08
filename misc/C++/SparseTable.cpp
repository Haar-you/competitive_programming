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

// SparseTable
template <typename T> class SparseTable{
  using Op = function<T(T,T)>;
  Op f;
  vector<vector<T>> a;
  vector<int> log_table;
public:
  SparseTable(vector<T> &v, Op f): f(f){
    int n = v.size();
    int logn = 0;
    while((1<<logn) <= n) ++logn;
    
    a = vector<vector<T>>(n, vector<T>(logn));
    REP(i,n) a[i][0] = v[i];
    FOR(j,1,logn) REP(i,n) a[i][j] = f(a[i][j-1], a[min(n-1, i+(1<<(j-1)))][j-1]);

    log_table = vector<int>(n+1);
    FOR(i,2,n+1) log_table[i] = log_table[i>>1] + 1;
  }
  
  T query(int s, int t){
    int k = log_table[t-s+1];
    return f(a[s][k], a[t-(1<<k)+1][k]);
  }
};

