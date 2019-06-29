
/*

 */

template <typename T> using rev_priority_queue = priority_queue<T,vector<T>,greater<T>>;

template <typename T, typename U> P<T,U> operator+(const P<T,U> &a, const P<T,U> &b){return {a.first + b.first, a.second + b.second};}
template <typename T, typename U> P<T,U> operator-(const P<T,U> &a, const P<T,U> &b){return {a.first - b.first, a.second - b.second};}

const int dir4[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
const int dir5[5][2] = {{1,0},{-1,0},{0,1},{0,-1},{0,0}};
const int dir8[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
const int dir9[9][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1},{0,0}};

//Longest Common Subsequence
template <typename T> int LCS(T a, T b){
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


// signed 64bit整数同士の積がオーバーフローするかどうかを判定。
bool check_overflow_mul_ll(int64_t a, int64_t b){
  return a >= LLONG_MAX / b;
}

template <typename T, typename Container=vector<T>> vector<pair<T,int>> group(const Container &v){
  vector<pair<T,int>> ret;

  for(auto &x : v){
    if(ret.empty()) ret.push_back({x,1});
    else if(ret.back().fst == x) ++ret.back().snd;
    else ret.push_back({x,1});
  }

  return ret;
}


