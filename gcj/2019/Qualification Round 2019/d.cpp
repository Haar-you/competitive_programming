#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define RITR(it, c) for(auto it = (c).rbegin(); it != (c).rend(); ++it)
#define EXIST(c,x) ((c).find(x) != (c).end())
#define LLI long long int
#define fst first
#define snd second

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x) ((void)0)
#endif

using namespace std;


template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

class Test{
  vector<int> broken;
  int N,B;
  
public:
  Test(int N, int B): N(N), B(B){
#ifdef DEBUG
    vector<int> v(N);
    iota(v.begin(), v.end(), 0);
    random_device seed_gen;
    mt19937 engine(seed_gen());
    shuffle(v.begin(), v.end(), engine);

    REP(i,B) broken.push_back(v[i]);
    sort(ALL(broken));
#endif
  }

  string query(const string &s){
    cout << s << endl << flush;
#ifdef DEBUG
    string ret(s);
    REV(i,B-1,0) ret.erase(broken[i], 1);
    return ret;
#else
    string ret;
    cin >> ret;
    return ret;
#endif
  }

  int answer(const vector<int> &v){
    join(cout, ALL(v));
#ifdef DEBUG
    if(v == broken) return 1;
    else return -1;
#else
    int verdict;
    cin >> verdict;
    return verdict;
#endif    
  }
};


int main(){
  int T; cin >> T;

  FORE(_,1,T){
    int N, B, F; cin >> N >> B >> F;
    Test t(N,B);
        
    vector<string> s(5, string(N,'0'));
    
    REP(i,N){
      REP(j,5){
	s[j][i] = '0' + ((i>>j)&1);
      }
    }
    
    vector<int> nb(N-B);

    REP(i,4){
      string r = t.query(s[i]);
      REP(j,(int)r.size()){
	nb[j] += ((int)(r[j]-'0'))<<i;
      }
    }

    {
      string r = t.query(s[4]);
      int d = 0;
      REP(j,(int)r.size()){
	if(j!=0 and r[j-1] != r[j]) d += 16;
	nb[j] += d;
      }
    }
    
    vector<int> ans;
    REP(i,N){
      if(count(ALL(nb),i) == 0) ans.push_back(i);
    }

    if(t.answer(ans) == -1){
      break;
    }
  }

  return 0;
}
