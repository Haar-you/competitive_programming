#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#include "Misc.cpp"
#endif

/*
 * starts_with関数
 * Rolling Hash
 * Rolling Hash 2D version
 * Z-algorithm
 * Suffix Array
 * KMP algorithm
 */

bool starts_with(const string &str, const string &prefix){
  if(str.size() < prefix.size()) return false;
  REP(i,prefix.size()){
    if(str[i] != prefix[i]) return false;
  }
  return true;
}


//Rolling Hash
class RollingHash{
private:
  string str;
  LLI base, mod;
  int sl;
  vector<LLI> shash, pow;
public:
  RollingHash(string _str, LLI _base, LLI _mod): str(_str), base(_base), mod(_mod), sl(str.size()), pow(sl+1), shash(sl+1){
    pow[0] = 1; shash[0] = 0;
    FORE(i,1,sl){shash[i] = (shash[i-1]*base+str[i-1]) % mod; pow[i] = pow[i-1]*base % mod;}
  }
  LLI hash(int i, int j){return (shash[j] - shash[i] * pow[j-i] + mod*mod) % mod;}
  vector<int> find(string p){
    vector<int> r;
    int pl = p.size();
    LLI phash = 0; FOR(i,0,pl) phash = (phash*base+p[i]) % mod;
    REPE(i,sl-pl) if(hash(i,i+pl) == phash) r.push_back(i);
    return r;
  }
};


//Rolling Hash (2D version)
class RollingHash2D{
private:
  vector<string> strs;
  LLI baseh, basew, mod;
  int slh, slw;
  vector<vector<LLI>> shash;
  vector<LLI> powh, poww;
  LLI hash(int i1, int j1, int i2, int j2){
    return (((shash[i2][j2]-(shash[i1][j2]*powh[i2-i1])%mod+mod*mod)%mod - (shash[i2][j1]*poww[j2-j1])%mod + mod*mod)%mod + ((shash[i1][j1]*powh[i2-i1])%mod*poww[j2-j1])%mod)%mod;
  }
public:
  RollingHash2D(vector<string> _strs, LLI _baseh, LLI _basew, LLI _mod):
    strs(_strs), baseh(_baseh), basew(_basew), mod(_mod), slh(strs.size()), slw(strs[0].size()),
    powh(slh+1), poww(slw+1), shash(slh+1, vector<LLI>(slw+1, 0)){
    powh[0] = 1; FORE(i,1,slh) powh[i] = (powh[i-1]*baseh) % mod;
    poww[0] = 1; FORE(i,1,slw) poww[i] = (poww[i-1]*basew) % mod;
    FORE(i,1,slh) FORE(j,1,slw) shash[i][j] = (shash[i][j-1] * basew + strs[i-1][j-1]) % mod;
    FORE(i,1,slh) FORE(j,1,slw) shash[i][j] = (shash[i-1][j] * baseh + shash[i][j]) % mod;
  }
  
  vector<pair<int,int>> find(vector<string> p){
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
class SuffixArray{
public:
  vector<int> sa;
  const string str;
  
  SuffixArray(const string &s): sa(s.size()), str(s){
    int n = s.size();
    vector<int> temp(n);
    REP(i,n) temp[i] = s[i];

    for(int l=1; l<n; l*=2){
      map<pair<int,int>, int> m2;
      REP(i,n) m2[make_pair(temp[i], i+l>=n?-1:temp[i+l])] = 0;
      int i=0;
      ITR(it,m2) it->second = i++;
      REP(i,n)temp[i] = m2[make_pair(temp[i], i+l>=n?-1:temp[i+l])];
    }
    REP(i,n) sa[temp[i]] = i;
  }

  int operator[](int i){return sa[i];}

  bool starts_with(const string &s, int k){
    if(s.size() <= str.size()-k){
      REP(i,s.size()){
	if(s[i] != str[k+i]) return false;
      }
      return true;
    }
    return false;
  }
  
  int lower_bound(const string &s){
    auto f = [&](int x){
	       REP(i,s.size()){
		 if(sa[x]+i >= str.size()) return false;
		 if(s[i] < str[sa[x]+i]) return true;
		 if(s[i] > str[sa[x]+i]) return false;
	       }
	       return true;
	     };
    return my_binary_search(-1, sa.size(), f, false);
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
