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
  
  vector<int> find(const T &p){
    vector<int> ret;
    int pl = p.size();
    LLI phash = 0;
    FOR(i,0,pl) phash = (phash*base+p[i]) % mod;
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
