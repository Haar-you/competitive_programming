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



// 行列・ベクトル計算
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

  friend ostream& operator<<(ostream &os, const GenericVector<T> &v){os << v._array; return os;}
};

template <typename T> class ColVector;
template <typename T> class RowVector;

template <typename T> class RowVector : public GenericVector<T>{
public:
  RowVector(): GenericVector<T>(){}
  RowVector(int _size): GenericVector<T>(_size){}
  RowVector(const vector<T> &_array): GenericVector<T>(_array){}
  RowVector(int _size, T _init): GenericVector<T>(_size, _init){}
  
  RowVector operator+(const RowVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] += a[i]; return ret;}
  RowVector operator-(const RowVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] -= a[i]; return ret;}
  RowVector operator*(const T &k) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] *= k; return ret;}
  T operator*(const RowVector<T> &a) const{T ret = T(); REP(i,this->_size) ret += (*this)[i]*a[i]; return ret;}

  const RowVector& operator +=(const RowVector<T> &a){REP(i,this->_size) this->_array[i] += a[i]; return *this;}
  const RowVector& operator -=(const RowVector<T> &a){REP(i,this->_size) this->_array[i] -= a[i]; return *this;}
  const RowVector& operator *=(const T &k){REP(i,this->_size) this->_array[i] *= k; return *this;}

  ColVector<T> transpose(){return ColVector<T>(this->_array);}
};

template <typename T> class ColVector : public GenericVector<T>{
public:
  ColVector(): GenericVector<T>(){}
  ColVector(int _size): GenericVector<T>(_size){}
  ColVector(const vector<T> &_array): GenericVector<T>(_array){}
  ColVector(int _size, T _init): GenericVector<T>(_size, _init){}
  
  ColVector operator+(const ColVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] += a[i]; return ret;}
  ColVector operator-(const ColVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] -= a[i]; return ret;}
  ColVector operator*(const T &k) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] *= k; return ret;}
  T operator*(const ColVector<T> &a) const{T ret = T(); REP(i,this->_size) ret += (*this)[i]*a[i]; return ret;}

  const ColVector& operator +=(const ColVector<T> &a){REP(i,this->_size) this->_array[i] += a[i]; return *this;}
  const ColVector& operator -=(const ColVector<T> &a){REP(i,this->_size) this->_array[i] -= a[i]; return *this;}
  const ColVector& operator *=(const T &k){REP(i,this->_size) this->_array[i] *= k; return *this;}

  RowVector<T> transpose(){return RowVector<T>(this->_array);}
};


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
  T& at(size_t r, size_t c){return _mat[r][c];}
  
  Matrix operator+(const Matrix &a) const{
    Matrix<T> ret(_row, _col);
    REP(i,_row) REP(j,_col) ret.at(i,j) = _mat[i][j] + a[i][j];
    return ret;
  }

  Matrix operator-(const Matrix &a) const{
    Matrix<T> ret(_row, _col);
    REP(i,_row) REP(j,_col) ret.at(i,j) = _mat[i][j] - a[i][j];
    return ret;
  }

  Matrix operator*(const Matrix &a) const{
    Matrix<T> ret(_row, a.col());
    REP(i,_row) REP(j,a.col()) REP(k,_col) ret.at(i,j) += _mat[i][k] * a[k][j];
    return ret;
  }

  Matrix operator*(const T &k) const{
    Matrix<T> ret(_row, _col);
    REP(i,_row) REP(j,_col) ret.at(i,j) = _mat[i][j] * k;
    return ret;
  }

  const Matrix& operator+=(const Matrix &a){
    REP(i,_row) _mat[i] += a[i];
    return *this;
  }

  const Matrix& operator-=(const Matrix &a){
    REP(i,_row) _mat[i] -= a[i];
    return *this;
  }

  const Matrix& operator*=(const T &k){
    REP(i,_row) _mat[i] *= k;
    return *this;
  }
  

  Matrix transpose(){
    Matrix<T> ret(_col, _row);
    REP(i,_row) REP(j,_col) ret.at(j,i) = _mat[i][j];
    return ret;
  }
  
  friend ostream& operator<<(ostream &os, const Matrix<T> &v){os << v._mat; return os;}

  static Matrix unit(int size){
    Matrix<T> ret(size, size);
    REP(i,size) ret.at(i,i) = 1;
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

  static bool lu_decompose(const Matrix &a, Matrix &l, Matrix &u){
    if(a.row() != a.col()) return false;

    l = Matrix(a.row(), a.row());
    u = Matrix::unit(a.row());

    REP(i,a.row()){
      REP(j,a.row()){
	if(i>=j){
	  l.at(i,j) = a.at[i][j];
	  REP(k,j) l.at(i,j) -= l.at(i,k)*u.at(k,j);
	}else{
	  u.at(i,j) = a.at[i][j];
	  REP(k,i) u.at(i,j) -= l.at(i,k)*u.at(k,j);
	  u.at(i,j) /= l.at(i,i);
	}
      }
    }
    return true;
  }
  
  static T determinant(const Matrix &a){
    Matrix l,u;
    if(!lu_decompose(a,l,u)) return 0;

    T det = 1;
    REP(i,a.row()) det *= l[i][i];
    return det;
  }
};

template <typename T> Matrix<T> operator*(const ColVector<T> &a, const RowVector<T> &b){
  Matrix<T> ret(a.size(),b.size());
  REP(i,a.size()) REP(j,b.size()) ret.at(i,j) = a[i] * b[j];
  return ret;
}

template <typename T> Matrix<T> operator*(const RowVector<T> &a, const ColVector<T> &b){
  Matrix<T> ret(1,1);
  REP(i,a.size()) ret.at(0,0) += (a[i] * b[i]);
  return ret;
}

template <typename T> Matrix<T> operator*(const Matrix<T> &a, const ColVector<T> &b){
  Matrix<T> ret(a.row(),1);
  REP(i,a.row()) REP(j,a.col()) ret.at(i,0) += a[i][j] * b[j];
  return ret;
}

template <typename T> Matrix<T> operator*(const RowVector<T> &a, const Matrix<T> &b){
  Matrix<T> ret(1,b.col());
  REP(i,b.col()) REP(j,b.row()) ret.at(0,i) += a[j] * b[j][i];
  return ret;
}



int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);


  return 0;
}
