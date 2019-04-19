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

template <int M> class mod_int_64{
public:
  int64_t val;
  mod_int_64(): val(0){}
  mod_int_64(int64_t n): val(n){}
  mod_int_64(int32_t n): val(n){}
  
  const mod_int_64 operator+(const mod_int_64 &a) const {return mod_int_64((val+a.val)%M);}
  const mod_int_64 operator-(const mod_int_64 &a) const {return mod_int_64((val-a.val+M)%M);}
  const mod_int_64 operator*(const mod_int_64 &a) const {return mod_int_64((val*a.val)%M);}
  const mod_int_64 operator/(const mod_int_64 &a) const {return mod_int_64((val*a.mod_inv().val)%M);}
  
  const mod_int_64& operator=(const mod_int_64 &a){val = a.val; return *this;}
  const mod_int_64& operator+=(const mod_int_64 &a){(val += a.val) %= M; return *this;}
  const mod_int_64& operator-=(const mod_int_64 &a){((val -= a.val) += M) %= M; return *this;}
  const mod_int_64& operator*=(const mod_int_64 &a){(val *= a.val) %= M; return *this;}
  const mod_int_64& operator/=(const mod_int_64 &a){(val *= a.mod_inv().val) %= M; return *this;}

  const bool operator==(const mod_int_64 &a) const {return val==a.val;}
  const bool operator!=(const mod_int_64 &a) const {return val!=a.val;}

  const mod_int_64 power(LLI p) const{
    mod_int_64 ret = 1, e = val;
    for(; p; e *= e, p >>= 1) if(p&1) ret *= e;
    return ret;
  }
  
  const mod_int_64 mod_inv() const{
    return power(M-2);
  }
};

template <int M> istream& operator>>(istream &is, mod_int_64<M> &a){is >> a.val; return is;}
template <int M> ostream& operator<<(ostream &os, const mod_int_64<M> &a){ os << a.val; return os;}


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

  friend ostream& operator<<(ostream &os, const Matrix<T> &m){
    REP(i,m.row()){
      REP(j,m.col()){
	os << m._mat[i][j] << " ";
      }
      os << endl;
    }
    return os;
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

const int64_t mod = 1e9+7;
using mint = mod_int_64<mod>;


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  LLI n,k;
  while(cin >> n >> k){
    vector<int> a(n); cin >> a;

    int c1 = count(ALL(a), 1);
    int c0 = count(ALL(a), 0);

    int m = min(c0, c1) + 1;

    int ng0 = count(a.begin()+c0, a.end(), 0);

    vector<vector<mint>> v(m, vector<mint>(m));

    REP(i,m){
      mint x = (mint)i*i*2/(n*(n-1));
      mint y = (mint)(c0-i)*(c1-i)*2/(n*(n-1));
      
      v[i][max(i-1,0)] = x;
      v[i][min(i+1,m-1)] = y;
      v[i][i] = (mint)1-x-y;
    }

    Matrix<mint> mat(v);
    mat = power(mat, k);


    mint ans = mat.at(ng0,0);

    cout << ans << endl;
  }
  
  return 0;
}
