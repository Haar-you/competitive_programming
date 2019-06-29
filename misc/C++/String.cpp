
/*
 * starts_with関数
 * Rolling Hash
 * Rolling Hash 2D version
 * Z-algorithm
 * Suffix Array
 * KMP algorithm
 * Aho-Corasick
 */

/*
  https://yukicoder.me/problems/no/430

  rolling hash [https://yukicoder.me/submissions/347187]
  suffix array [https://yukicoder.me/submissions/347188]
  aho-corasick [https://yukicoder.me/submissions/347348]
 */


bool starts_with(const string &str, const string &prefix){
  if(str.size() < prefix.size()) return false;
  REP(i,prefix.size()){
    if(str[i] != prefix[i]) return false;
  }
  return true;
}


//Rolling Hash
template <typename T> class RollingHash{
private:
  T str;
  LLI base, mod;
  int sl;
  vector<LLI> shash, pow;
public:
  RollingHash(const T &str, LLI base, LLI mod): str(str), base(base), mod(mod), sl(str.size()), shash(sl+1), pow(sl+1){
    pow[0] = 1;
    shash[0] = 0;
    FORE(i,1,sl){
      shash[i] = (shash[i-1]*base+str[i-1]) % mod;
      pow[i] = pow[i-1]*base % mod;
    }
  }

  LLI hash(int i, int j){ // [i, j)
    return (shash[j] - shash[i] * pow[j-i] + mod*mod) % mod;
  }

  LLI hash(const T &p){
    LLI phash = 0;
    REP(i,(int)p.size()) phash = (phash*base+p[i]) % mod;
    return phash;
  }
  
  vector<int> find(const T &p){
    vector<int> ret;
    int pl = p.size();
    LLI phash = hash(p);
    REPE(i,sl-pl) if(hash(i,i+pl) == phash) ret.push_back(i);
    return ret;
  }
};

//Rolling Hash (2D version)
template <typename T> class RollingHash2D{
private:
  T strs;
  LLI baseh, basew, mod;
  int slh, slw;
  vector<vector<LLI>> shash;
  vector<LLI> powh, poww;
  
public:
  RollingHash2D(const T &strs, LLI baseh, LLI basew, LLI mod):
    strs(strs), baseh(baseh), basew(basew), mod(mod), slh(strs.size()), slw(strs[0].size()),
    shash(slh+1, vector<LLI>(slw+1, 0)), powh(slh+1), poww(slw+1){
    powh[0] = 1; FORE(i,1,slh) powh[i] = (powh[i-1]*baseh) % mod;
    poww[0] = 1; FORE(i,1,slw) poww[i] = (poww[i-1]*basew) % mod;
    FORE(i,1,slh) FORE(j,1,slw) shash[i][j] = (shash[i][j-1] * basew + strs[i-1][j-1]) % mod;
    FORE(i,1,slh) FORE(j,1,slw) shash[i][j] = (shash[i-1][j] * baseh + shash[i][j]) % mod;
  }

  LLI hash(int i1, int j1, int i2, int j2){
    return (((shash[i2][j2]-(shash[i1][j2]*powh[i2-i1])%mod+mod*mod)%mod - (shash[i2][j1]*poww[j2-j1])%mod + mod*mod)%mod + ((shash[i1][j1]*powh[i2-i1])%mod*poww[j2-j1])%mod)%mod;
  }

  vector<pair<int,int>> find(const T &p){
    vector<pair<int,int>> r;
    int plh = p.size(), plw = p[0].size();
    LLI phash = 0;
    FOR(i,0,plh){
      LLI temp = 0; FOR(j,0,plw) temp = (temp*basew+p[i][j]) % mod;
      phash = (phash*baseh+temp) % mod;
    }
    
    REPE(i,slh-plh) REPE(j,slw-plw) if(hash(i,j,i+plh,j+plw) == phash) r.push_back(make_pair(i,j));
    return r;
  }
};


// Z-algorithm
// 最長共通接頭辞の長さ配列
template<typename T> vector<int> Z_algorithm(const T &s){
  int n = s.size();
  vector<int> v(n, 0);
  v[0] = n;
  int j = 0;
  
  FOR(i,1,n){
    while(i+j<n && s[j]==s[i+j]) ++j;
    v[i] = j;
    if(j==0) continue;
    int k = 1;
    while(i+k<n && k+v[k]<j) v[i+k] = v[k++];
    i += k-1, j -= k;
  }
  return v;
}

// Suffix Array
template <typename T> class SuffixArray{
public:
  vector<int> sa;
  const T str;
  
  SuffixArray(const T &s): sa(s.size()), str(s){
    int n = s.size();
    vector<int> temp(n);
    REP(i,n) temp[i] = s[i];

    for(int l=1; l<n; l*=2){
      map<pair<int,int>, int> m2;
      REP(i,n) m2[make_pair(temp[i], i+l>=n?-1:temp[i+l])] = 0;
      int i=0;
      ITR(it,m2) it->second = i++;
      REP(i,n) temp[i] = m2[make_pair(temp[i], i+l>=n?-1:temp[i+l])];
    }
    REP(i,n) sa[temp[i]] = i;
  }

  int operator[](int i){return sa[i];}

  bool starts_with(const T &s, int k){
    if(s.size() <= str.size()-k){
      REP(i,(int)s.size()){
	if(s[i] != str[k+i]) return false;
      }
      return true;
    }
    return false;
  }

  int lower_bound(const T &s){
    auto check =
      [&](int x){
	REP(i,(int)s.size()){
	  if(sa[x]+i >= (int)str.size()) return false;
	  if(s[i] < str[sa[x]+i]) return true;
	  if(s[i] > str[sa[x]+i]) return false;
	}
	return true;
      };

    int lb=-1, ub=sa.size(), mid;
    while(abs(lb-ub)>1){
      mid = (lb+ub)/2;

      if(check(mid)){
	ub = mid;
      }else{
	lb = mid;
      }
    }
    
    return ub;
  }

  int upper_bound(const T &s){
    T t(s);

    t.back()++;
    int ret = lower_bound(t);
    t.back()--;
    return ret;
  }
};

// KMP algorithm
class KMP{
private:
  string p;
  vector<int> table;
public:
  KMP(string p): p(p), table(p.size(), 0){
    int j=0;
    FOR(i,1,p.size()){
      if(p[i] == p[j]) table[i] = j++;
      else {table[i] = j; j = 0;}
    }
  }
  
  int search(string s, int i=0){
    int j=0;
    while(i<s.size() && j<p.size()){
      if(s[i] == p[j]){++j; ++i;}
      else if(j == 0) ++i;
      else j = table[j];
    }
    if(j==p.size()) return i-j;
    return s.size();
  }
};

// Aho-Corasick
class AhoCorasick{
public:
  int n;
  vector<unordered_map<char,int>> trie;
  vector<int> failure_edge;
  vector<string> dict;
  vector<vector<int>> dict_index;

  AhoCorasick(): n(1), trie(1), failure_edge(1){
  }

  void add(const string &s){
    dict.push_back(s);

    int cur = 0;

    REP(i,(int)s.size()){
      char c = s[i];

      if(EXIST(trie[cur], c)){
	cur = trie[cur][c];
      }else{
	++n;
	trie.resize(n);

	trie[cur][c] = n-1;
	
	cur = trie[cur][c];
      }
    }

    dict_index.resize(n);
    dict_index[cur].push_back(dict.size()-1);
  }

  void construct_failure_link(){
    failure_edge.resize(n);

    queue<int> dq;
    dq.push(0);

    while(not dq.empty()){
      int cur = dq.front(); dq.pop();

      for(auto &kv : trie[cur]){
	char c = kv.fst;
	int next = kv.snd;

	if(cur == 0){
	  failure_edge[next] = 0;

	}else{
	  int i = failure_edge[cur];
	  int j = 0;
	
	  while(1){
	    if(EXIST(trie[i], c)){
	      j = trie[i][c];
	      break;
	    }else{
	      if(i == 0) break;
	      i = failure_edge[i];
	    }
	  }
	
	  failure_edge[next] = j;

	  for(auto k : dict_index[failure_edge[next]]){
	    dict_index[next].push_back(k);
	  }
	}
	
	dq.push(next);
      }
    }
  }

  vector<pair<int,int>> match(const string &s){
    vector<pair<int,int>> ret;
    int cur = 0;

    REP(i,(int)s.size()){
      char c = s[i];

      while(cur != 0 and not EXIST(trie[cur], c)){
	cur = failure_edge[cur];
      }

      cur = trie[cur][c];

      for(auto j : dict_index[cur]){
	ret.push_back({i, j});
      }
    }
    
    return ret;
  }
};


//Levenshtein distance
int levenshtein(string a, string b){
  vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
  REPE(i,a.size()) dp[i][0] = i;
  REPE(i,b.size()) dp[0][i] = i;
  FORE(i,1,a.size()) FORE(j,1,b.size())
    dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+(a[i-1] == b[j-1] ? 0 : 1));
  return dp[a.size()][b.size()];
}
