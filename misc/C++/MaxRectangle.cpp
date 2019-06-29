

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

/*
  https://atcoder.jp/contests/arc081/submissions/5708645 ((w+1)*(h+1)の最大値を求める変種)
 */

// 最大面積長方形の面積
int max_rectangle(const vector<vector<int>> &d){
  int H = d.size();
  int W = d[0].size();
    
  vector<vector<int>> c(d);
  FOR(i,1,H){
    REP(j,W){
      if(c[i][j]){
	c[i][j] += c[i-1][j];
      }
    }
  }
  int ret = 0;
  REP(i,H){
    int t = max_rectangle_in_histogram(c[i]);
    chmax(ret, t);
  }
  
  return ret;
}
