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
#define UNIQ(v) v.erase(unique(ALL(v)), v.end())
#define bit(i) (1LL<<i)
#define sz(v) ((LLI)(v).size())

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
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> bool chmin(T &a, const U &b){return (a>b ? a=b, true : false);}
template <typename T, typename U> bool chmax(T &a, const U &b){return (a<b ? a=b, true : false);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}


template <typename T> class Matrix{
private:
  int _row, _col;
  vector<vector<T>> _mat;
public:
  Matrix(): _row(0), _col(0), _mat(){}
  Matrix(int _row, int _col): _row(_row), _col(_col), _mat(_row, vector<T>(_col)){}
  Matrix(int _row, int _col, const T &val): _row(_row), _col(_col), _mat(_row, vector<T>(_col, val)){}
  Matrix(const vector<vector<T>> &m): _row(m.size()), _col(m[0].size()), _mat(m){}

  int row() const {return _row;}
  int col() const {return _col;}
  
  const vector<T>& operator[](size_t i) const {return _mat[i];}
  vector<T>& unsafe_row(size_t i){return _mat[i];}
  T& at(size_t r, size_t c){return _mat[r][c];}
  
  Matrix operator+(const Matrix &a) const{Matrix<T> ret(_row, _col); REP(i,_row) REP(j,_col) ret.at(i,j) = _mat[i][j] + a[i][j]; return ret;}
  Matrix operator-(const Matrix &a) const{Matrix<T> ret(_row, _col); REP(i,_row) REP(j,_col) ret.at(i,j) = _mat[i][j] - a[i][j]; return ret;}
  Matrix operator*(const Matrix &a) const{Matrix<T> ret(_row, a.col()); REP(i,_row) REP(j,a.col()) REP(k,_col) ret.at(i,j) += _mat[i][k] * a[k][j]; return ret;}
  Matrix operator*(const T &k) const{Matrix<T> ret(_row, _col); REP(i,_row) REP(j,_col) ret.at(i,j) = _mat[i][j] * k; return ret;}
  
  const Matrix& operator+=(const Matrix &a){REP(i,_row) _mat[i] += a[i]; return *this;}
  const Matrix& operator-=(const Matrix &a){REP(i,_row) _mat[i] -= a[i]; return *this;}
  const Matrix& operator*=(const T &k){REP(i,_row) _mat[i] *= k; return *this;}

  void show_dump(){
#ifdef DEBUG
    REP(i,_row){
      cerr << "|";
      REP(j,_col){
	cerr << setw(10) << _mat[i][j] << " ";
      }
      cerr << "|" << endl;
    }
#endif
  }
};


template <typename T> Matrix<T> unit(int size){
  Matrix<T> ret(size, size);
  REP(i,size) ret.at(i,i) = 1;
  return ret;
}

template <typename T> Matrix<T> power(const Matrix<T> &a, LLI k){
  Matrix<T> ret;
  if(k<=0) return unit<T>(a.row());
  if(k==1) return a;
  Matrix<T> temp = power(a, k/2);
  ret = temp*temp;
  if(k%2) ret = ret*a;
  return ret;
}


class runtime_mod_int{
public:
  static uint64_t M;
  
  uint64_t val;
  runtime_mod_int(): val(0){}
  runtime_mod_int(int64_t n): val(n%M){}
  
  const runtime_mod_int operator+(const runtime_mod_int &a) const {return runtime_mod_int((val+a.val)%M);}
  const runtime_mod_int operator-(const runtime_mod_int &a) const {return runtime_mod_int((val-a.val+M)%M);}
  const runtime_mod_int operator*(const runtime_mod_int &a) const {return runtime_mod_int((val*a.val)%M);}
  const runtime_mod_int operator/(const runtime_mod_int &a) const {return runtime_mod_int((val*a.mod_inv().val)%M);}
  
  const runtime_mod_int& operator=(const runtime_mod_int &a){val = a.val; return *this;}
  const runtime_mod_int& operator+=(const runtime_mod_int &a){(val += a.val) %= M; return *this;}
  const runtime_mod_int& operator-=(const runtime_mod_int &a){((val -= a.val) += M) %= M; return *this;}
  const runtime_mod_int& operator*=(const runtime_mod_int &a){(val *= a.val) %= M; return *this;}
  const runtime_mod_int& operator/=(const runtime_mod_int &a){(val *= a.mod_inv().val) %= M; return *this;}

  const bool operator==(const runtime_mod_int &a) const {return val==a.val;}
  const bool operator!=(const runtime_mod_int &a) const {return val!=a.val;}

  const runtime_mod_int power(LLI p) const{
    runtime_mod_int ret = 1, e = val;
    for(; p; e *= e, p >>= 1) if(p&1) ret *= e;
    return ret;
  }
  
  const runtime_mod_int mod_inv() const{
    return power(M-2);
  }
};

uint64_t runtime_mod_int::M;

istream& operator>>(istream &is, runtime_mod_int &a){is >> a.val; return is;}
ostream& operator<<(ostream &os, const runtime_mod_int &a){ os << a.val; return os;}



using mint = runtime_mod_int;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI L,A,B,M;
  while(cin >> L >> A >> B >> M){
    runtime_mod_int::M = M;

    vector<LLI> d(20);
    vector<LLI> cd(20);

    FORE(i,1,18){
      LLI x = powl(10, i);
      d[i] = min(L, max(0LL, (x-A+B-1)/B));
    }

    FORE(i,1,18){
      cd[i] = d[i] - d[i-1];
    }
    
    mint ans = 0;

    Matrix<mint> res = unit<mint>(3);

    FORE(i,1,18){
      Matrix<mint> mat({
			{(LLI)pow(10,i)%M, 0, 0},
			{1,1,0},
			{0,B%M,1}
		       });
      
      auto p = power(mat, cd[i]);
      res = res*p;
    }

    ans = res[1][0]*A + res[2][0];

    cout << ans << endl;
  }
  
  return 0;
}
