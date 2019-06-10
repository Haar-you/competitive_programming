#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define ALL(v) (v).begin(), (v).end()
#define LLI long long int

using namespace std;

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif



/*
 * 列ベクトル、行ベクトル同士の加減算・定数倍・内積
 * 行列の加減算・積・累乗
 * LU分解
 * 行列式
 * ベクトル・行列の転置
 */


// 行列・ベクトル計算

template <typename T> class RowVector{
  int _size;
  vector<T> _array;
public:
  RowVector(){}
  RowVector(int _size): _size(_size){}
  RowVector(const vector<T> &_array): _size(_array.size()), _array(_array){}
  RowVector(int _size, const T &_init): _size(_size), _array(_size, _init){}

  int size() const{return _size;}
  const T& operator[](size_t index) const{return _array[index];}
  T& operator[](size_t index){return _array[index];}

  const vector<T>& to_array() const{return _array;}

  friend ostream& operator<<(ostream &os, const RowVector<T> &v){os << v._array; return os;}
  
  RowVector operator+(const RowVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] += a[i]; return ret;}
  RowVector operator-(const RowVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] -= a[i]; return ret;}
  RowVector operator*(const T &k) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] *= k; return ret;}
  T operator*(const RowVector<T> &a) const{T ret = T(); REP(i,this->_size) ret += (*this)[i]*a[i]; return ret;}

  const RowVector& operator +=(const RowVector<T> &a){REP(i,this->_size) this->_array[i] += a[i]; return *this;}
  const RowVector& operator -=(const RowVector<T> &a){REP(i,this->_size) this->_array[i] -= a[i]; return *this;}
  const RowVector& operator *=(const T &k){REP(i,this->_size) this->_array[i] *= k; return *this;}
};


template <typename T> class ColVector{
  int _size;
  vector<T> _array;
public:
  ColVector(){}
  ColVector(int _size): _size(_size){}
  ColVector(const vector<T> &_array): _size(_array.size()), _array(_array){}
  ColVector(int _size, const T &_init): _size(_size), _array(_size, _init){}

  int size() const{return _size;}
  const T& operator[](size_t index) const{return _array[index];}
  T& operator[](size_t index){return _array[index];}

  const vector<T>& to_array() const{return _array;}

  friend ostream& operator<<(ostream &os, const ColVector<T> &v){os << v._array; return os;}
  
  ColVector operator+(const ColVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] += a[i]; return ret;}
  ColVector operator-(const ColVector<T> &a) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] -= a[i]; return ret;}
  ColVector operator*(const T &k) const{vector<T> ret(this->_array); REP(i,this->_size) ret[i] *= k; return ret;}
  T operator*(const ColVector<T> &a) const{T ret = T(); REP(i,this->_size) ret += (*this)[i]*a[i]; return ret;}

  const ColVector& operator +=(const ColVector<T> &a){REP(i,this->_size) this->_array[i] += a[i]; return *this;}
  const ColVector& operator -=(const ColVector<T> &a){REP(i,this->_size) this->_array[i] -= a[i]; return *this;}
  const ColVector& operator *=(const T &k){REP(i,this->_size) this->_array[i] *= k; return *this;}
};

template <typename T> RowVector<T> transpose(ColVector<T> &v){return RowVector<T>(v.to_array());}
template <typename T> ColVector<T> transpose(RowVector<T> &v){return ColVector<T>(v.to_array());}





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


template <typename T> Matrix<T> transpose(const Matrix<T> &m){
  Matrix<T> ret(m.col(), m.row());
  REP(i,m.row()) REP(j,m.col()) ret.at(j,i) = m.at(i,j);
  return ret;
}

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

template <typename T> bool lu_decompose(const Matrix<T> &a, Matrix<T> &l, Matrix<T> &u){
  if(a.row() != a.col()) return false;

  l = Matrix<T>(a.row(), a.row());
  u = unit<T>(a.row());

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

template <typename T> T determinant(Matrix<T> m){
  int n = m.row();
  int s = 0;

  REP(i,n){
    if(m.at(i,i) == 0){
      FOR(j,i+1,n){
	if(m.at(j,i) != 0){
	  m.unsafe_row(i).swap(m.unsafe_row(j));
	  (s += 1) %= 2;
	  break; 
	}
	if(j == n-1) return 0;
      }
    }
    
    FOR(j,i+1,n){
      T t = m.at(j,i) / m.at(i,i);
      REP(k,n) m.at(j,k) -= m.at(i,k) * t;
    }
  }

  T ret = s ? -1 : 1;
  REP(i,n) ret *= m.at(i,i);
  return ret;
}



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



int main(){
  return 0;
}
