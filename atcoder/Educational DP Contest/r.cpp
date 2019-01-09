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
#ifdef DEBUG
#include <boost/core/demangle.hpp>
#define dump(x) cerr << "L" << __LINE__ << ": in " << __PRETTY_FUNCTION__ << " \e[32;1m" << boost::core::demangle(typeid(x).name()) << "\e[37m" << " " << (#x) << " = " << (x) << "\e[m" << endl;
#else
#define dump(x)
#endif
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T> ostream& operator<<(ostream &os, const vector<T> &v){os << "{";ITR(i,v){if(i!=v.begin())os << ","; os << *i;}os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T,U> &p){os << "(" << p.first << "," << p.second << ")"; return os;}

template <typename T> T& chmin(T &a, const T &b){return a = min(a,b);}
template <typename T> T& chmax(T &a, const T &b){return a = max(a,b);}

template <int M> class mod_int_64{
public:
  int64_t val;
  mod_int_64(): val(0){}
  mod_int_64(int64_t n): val(n){}
  mod_int_64(int32_t n): val(n){}
  
  const mod_int_64 operator+(const mod_int_64 &a) const {return mod_int_64((val+a.val)%M);}
  const mod_int_64 operator-(const mod_int_64 &a) const {return mod_int_64((val-a.val+M)%M);}
  const mod_int_64 operator*(const mod_int_64 &a) const {return mod_int_64((val*a.val)%M);}
  const mod_int_64& operator=(const mod_int_64 &a){val = a.val; return *this;}
  const mod_int_64& operator+=(const mod_int_64 &a){(val += a.val) %= M; return *this;}
  const mod_int_64& operator-=(const mod_int_64 &a){((val -= a.val) += M) %= M; return *this;}
  const mod_int_64& operator*=(const mod_int_64 &a){(val *= a.val) %= M; return *this;}
};

template <int M> istream& operator>>(istream &is, mod_int_64<M> &a){is >> a.val; return is;}
template <int M> ostream& operator<<(ostream &os, const mod_int_64<M> &a){ os << a.val; return os;}

template <typename T> class GenericVector{
protected:
  int _size;
  vector<T> _array;

public:
  GenericVector(): _size(0), _array(_size){}
  GenericVector(int _size): _size(_size), _array(_size){}
  GenericVector(const vector<T> &_array): _size(_array.size()), _array(_array){}
  GenericVector(int _size, T _init): _size(_size), _array(_size, _init){}

  int size() const{return _size;}
  const T& operator[](size_t index) const{return _array[index];}
  T& operator[](size_t index){return _array[index];}

  friend ostream& operator<<(ostream &os, const GenericVector<T> &v){
    os << v._array; return os;
  }
};

template <typename T> class RowVector : public GenericVector<T>{
public:
  RowVector(): GenericVector<T>(){}
  RowVector(int _size): GenericVector<T>(_size){}
  RowVector(const vector<T> &_array): GenericVector<T>(_array){}
  RowVector(int _size, T _init): GenericVector<T>(_size, _init){}
  
  RowVector operator+(const RowVector<T> &a) const{
    vector<T> ret(this->_array);
    REP(i,this->_size) ret[i] += a[i];
    return ret;
  }

  RowVector operator-(const RowVector<T> &a) const{
    vector<T> ret(this->_array);
    REP(i,this->_size) ret[i] -= a[i];
    return ret;
  }

  RowVector operator*(const T &k) const{
    vector<T> ret(this->_array);
    REP(i,this->_size) ret[i] *= k;
    return ret;
  }
};

template <typename T> class ColVector : public GenericVector<T>{
public:
  ColVector(): GenericVector<T>(){}
  ColVector(int _size): GenericVector<T>(_size){}
  ColVector(const vector<T> &_array): GenericVector<T>(_array){}
  ColVector(int _size, T _init): GenericVector<T>(_size, _init){}
  
  ColVector operator+(const ColVector<T> &a) const{
    vector<T> ret(this->_array);
    REP(i,this->_size) ret[i] += a[i];
    return ret;
  }

  ColVector operator-(const ColVector<T> &a) const{
    vector<T> ret(this->_array);
    REP(i,this->_size) ret[i] -= a[i];
    return ret;
  }

  ColVector operator*(const T &k) const{
    vector<T> ret(this->_array);
    REP(i,this->_size) ret[i] *= k;
    return ret;
  }
};

template <typename T> T operator*(const GenericVector<T> &a, const GenericVector<T> &b){
  T ret = T();
  REP(i,a.size()) ret += (a[i] * b[i]);
  return ret;
}

template <typename T> class Matrix{
private:
  int _row, _col;
  RowVector<ColVector<T>> _mat;
public:
  Matrix(): _row(0), _col(0), _mat(){}
  Matrix(int _row, int _col): _row(_row), _col(_col), _mat(_row, _col){}
  Matrix(const vector<vector<T>> &_m){
    _row = _m.size();
    _col = _m[0].size();
    _mat = RowVector<ColVector<T>>(_m.size());
    REP(i,_m.size()) _mat[i] = ColVector<T>(_m[i]);
  }

  int row() const {return _row;}
  int col() const {return _col;}
  
  const ColVector<T>& operator[](size_t index) const{return _mat[index];}
  
  Matrix operator+(const Matrix &a) const{
    vector<vector<T>> ret(_row, vector<T>(_col));
    REP(i,_row) REP(j,_col) ret[i][j] = _mat[i][j] + a[i][j];
    return ret;
  }

  Matrix operator-(const Matrix &a) const{
    vector<vector<T>> ret(_row, vector<T>(_col));
    REP(i,_row) REP(j,_col) ret[i][j] = _mat[i][j] - a[i][j];
    return ret;
  }

  Matrix operator*(const Matrix &a) const{
    vector<vector<T>> ret(_row, vector<T>(a.col()));
    REP(i,_row) REP(j,a.col()) REP(k,_col) ret[i][j] += _mat[i][k] * a[k][j];
    return ret;
  }
  
  friend ostream& operator<<(ostream &os, const Matrix<T> &v){
    os << v._mat; return os;
  }

  static Matrix unit(int size){
    vector<vector<T>> ret(size, vector<T>(size));
    REP(i,size) ret[i][i] = 1;
    return ret;
  }

  static Matrix power(const Matrix &a, LLI k){
    Matrix ret;
    
    if(k<=0) return Matrix::unit(a.row());
    if(k==1) return a;
    Matrix temp = power(a, k/2);
    ret = temp*temp;
    if(k%2) ret = ret*a;
    return ret;
  }
};

const LLI mod = 1e9+7;

using mint = mod_int_64<mod>;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N; cin >> N;
  LLI K; cin >> K;
  
  vector<vector<mint>> a(N, vector<mint>(N)); cin >> a;

  Matrix<mint> m(a);

  Matrix<mint> p = Matrix<mint>::power(m,K);

  mint ans = 0;
  REP(i,N) REP(j,N) ans += p[i][j];

  cout << ans << endl;
  
  return 0;
}
