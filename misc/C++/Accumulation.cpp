/*

 */



// 二次元累積和
template <typename T> class Accum2D{
public:
  vector<vector<T>> accum;

  Accum2D(vector<vector<T>> &vv){
    int d1 = vv.size(), d2 = vv[0].size();
    accum = vector<vector<T>>(d1+1, vector<T>(d2+1));
    REP(i,d1) REP(j,d2) accum[i+1][j+1] = vv[i][j];
    FORE(i,1,d1) REPE(j,d2) accum[i][j] += accum[i-1][j];
    REPE(i,d1) FORE(j,1,d2) accum[i][j] += accum[i][j-1];
  }

  // 1-indexed
  T sum(int x1, int y1, int x2, int y2){
    return accum[x2][y2] - accum[x1-1][y2] - accum[x2][y1-1] + accum[x1-1][y1-1];
  }
};

// 一次元累積和
template <typename T> class Accum{
public:
  vector<T> accum;

  Accum(vector<T> &v){
    int n = v.size();
    accum = vector<T>(n+1);
    REP(i,n) accum[i+1] = accum[i] + v[i];
  }

  T sum(int i, int j){ //[i,j)
    return accum[j] - accum[i];
  }
};



// 連続部分和の最大値
int max_partial_sum(vector<int> &v){
  int t = v[0], ans = t;
  FOR(i,1,v.size()) ans = max(ans, t = max(t+v[i], v[i]));
  return ans;
}
