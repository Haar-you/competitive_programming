#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#endif

/*

 */

template <typename T> using rev_priority_queue = priority_queue<T,vector<T>,greater<T>>;

template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}


const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
const int dir5[5][2] = {{1,0},{-1,0},{0,1},{0,-1},{0,0}};
const int dir8[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
const int dir9[9][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1},{0,0}};

const int inf = INT_MAX;




// 二分探索
// fが適当なxの前後でtrueからfalseに変わる場合tfはtrue, falseからtrueに変わる場合tfはfalse.
LLI my_binary_search(LLI lower, LLI upper, function<bool(LLI)> f, bool tf=true){
  LLI mid;
  while(abs(upper-lower)>1){
    mid = (lower+upper)/2;
    
    if(f(mid)^(!tf)) lower = mid;
    else upper = mid;
  }
  return upper;
}

//Longest Common Subsequence
template <typename T>
int LCS(T a, T b){
  vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
  FORE(i,1,a.size()) FORE(j,1,b.size()) dp[i][j] = a[i-1] == b[j-1] ? dp[i-1][j-1]+1 : max(dp[i-1][j], dp[i][j-1]);
  return dp[a.size()][b.size()];
}

//Longest Increasing Subsequence
template <typename T> int LIS(vector<T> &xs, T INF){
  vector<T> dp(xs.size(), INF);
  for(auto x : xs) dp[lower_bound(ALL(dp),x)-dp.begin()] = x;
  return lower_bound(ALL(dp),INF) - dp.begin();
}

//Levenshtein distance
int levenshtein(string a, string b){
  vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
  REPE(i,a.size()) dp[i][0] = i;
  REPE(i,b.size()) dp[0][i] = i;
  FORE(i,1,a.size()) FORE(j,1,b.size())
    dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+(a[i-1] == b[j-1] ? 0 : 1));
  return dp[a.size()][b.size()];
}


// 連続部分和の最大値
int max_partial_sum(vector<int> &v){
  int t = v[0], ans = t;
  FOR(i,1,v.size()) ans = max(ans, t = max(t+v[i], v[i]));
  return ans;
}

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

// 二次方程式の実数解
pair<double,double> quadratic_equation(double a, double b, double c){
  double x1 = (-b + sqrt(b*b-4*a*c))/(2*a);
  double x2 = (-b - sqrt(b*b-4*a*c))/(2*a);
  return make_pair(x1,x2);
}


// signed 64bit整数同士の積がオーバーフローするかどうかを判定。
bool check_overflow_mul_ll(int64_t a, int64_t b){
  return a >= LLONG_MAX / b;
}

// 乱数
class my_rand{
public:
  mt19937 r;
  my_rand(){
    r = mt19937(static_cast<unsigned int>(time(nullptr)));
  }
};

// ヒストグラム中の最大面積長方形の面積
LLI max_rectangle_in_histogram(const vector<LLI> &h){
  stack<pair<LLI,LLI>> st;
  LLI ret = 0;

  REP(i,(int)h.size()){
    if(st.empty()) st.push({h[i],i});
    else if(st.top().fst < h[i]) st.push({h[i],i});
    else if(st.top().fst > h[i]){
      int j = i;
      while(not st.empty() and st.top().fst > h[i]){
	chmax(ret, st.top().fst * (i-st.top().snd));
	j = st.top().snd;
	st.pop();
      }
      st.push({h[i],j});
    }
  }

  while(not st.empty()){
    chmax(ret, st.top().fst * ((int)h.size()-st.top().snd));
    st.pop();
  }
  
  return ret;
}
