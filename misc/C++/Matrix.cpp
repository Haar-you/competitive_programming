#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#endif

/*
 * 列ベクトル、行ベクトル同士の加減算・定数倍・内積
 * 行列の加減算・積・累乗
 * LU分解
 * 行列式
 * ベクトル・行列の転置
 */


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
	  l.at(i,j) = a[i][j];
	  REP(k,j) l.at(i,j) -= l.at(i,k)*u.at(k,j);
	}else{
	  u.at(i,j) = a[i][j];
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


template <typename T> T determinant(vector<vector<T>> m){
  int n = m.size();
  int s = 0;

  REP(i,n){
    if(m[i][i] == 0){
      FOR(j,i+1,n){
	if(m[j][i] != 0){
	  m[i].swap(m[j]);
	  (s += 1) %= 2;
	  break; 
	}
	if(j == n-1) return 0;
      }
    }
    
    FOR(j,i+1,n){
      T t = m[j][i] / m[i][i];
      REP(k,n) m[j][k] -= m[i][k] * t;
    }
  }

  T ret = s ? -1 : 1;
  REP(i,n) ret *= m[i][i];
  return ret;
}

