/*
  [問題例]
  https://codeforces.com/contest/1175/problem/E
  https://atcoder.jp/contests/arc060/tasks/arc060_c
 */

class Doubling{
public:
  int n;
  int m;
  vector<vector<int>> table;
  
  // 常に、next[i] >= i を満たすようにする。
  Doubling(const vector<int> &next): n(next.size()), m(ceil(log2(n))+1), table(m, vector<int>(n)){
    REP(i,n) table[0][i] = next[i];
    FOR(i,1,m){
      REP(j,n){
	int k = table[i-1][j];
	if(k>=0 and k<n){
	  table[i][j] = table[i-1][k];
	}
      }
    }
  }

  int distance(int a, int b){ // aからbに移動する(超える)最小回数 (a<=b)
    int ret = 0;
    int cur = a;

    while(1){
      if(table[0][cur] >= b){
	++ret;
	break;
      }

      if(table[0][cur] <= cur) return -1;

      int next = -1;
      int diff = 0;
      
      FOR(i,0,m){
	if(table[i][cur] < b and table[i][cur] >= 0){
	  next = table[i][cur];
	  diff = (1<<i);
	}
      }

      if(next >= cur){
	ret += diff;
	cur = next;
      }else{
	return -1;
      }
    }
    
    return ret;
  }

};

