#include <bits/stdc++.h>
#define FOR(v, a, b) for(int v = (a); v < (b); ++v)
#define FORE(v, a, b) for(int v = (a); v <= (b); ++v)
#define REP(v, n) FOR(v, 0, n)
#define REPE(v, n) FORE(v, 0, n)
#define REV(v, a, b) for(int v = (a); v >= (b); --v)
#define ALL(x) (x).begin(), (x).end()
#define ITR(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define LLI long long int
using namespace std;
template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}

class Interactive{
  vector<int> a;
public:
  Interactive(int N): a(N){
    std::random_device rnd;
    std::uniform_int_distribution<> rndd(1, 1073741824);

    REP(i,N){
      a[i] = rndd(rnd);
    }
  }
  LLI ask(int i, int j, int k){
    cout << 1 << " " << i << " " << j << " " << k << endl << flush;
    
    --i; --j; --k;

    LLI r; cin >> r;
    return r;
  }
  int answer(vector<LLI> &v){
    cout << 2 << " ";
    join(cout, ALL(v));
    cout << flush;

    int r; cin >> r;
    return r;
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  
  int T; cin >> T;

  REP(_,T){
    int N; cin >> N;
    Interactive intera(N);
    vector<LLI> a(N);

    int y,z;

    if(N % 3 != 0){
      y = 1, z = 2;
    }else if(N % 7 != 0){
      y = 5, z = 6;
    }else if(N % 5 != 0){
      y = 1, z = 4;
    }else{
      y = 2, z = 5;
    }
    
    REP(i,N){
      a[i] = intera.ask(i+1,(i+y)%N+1,(i+z)%N+1);
    }

    vector<LLI> b(N,0);
    
    for(LLI i=1; i<=(1LL<<30); i<<=1){
      vector<LLI> t(N,0);

      int cnt = 0;

      REP(j,1<<8){
	REP(k,8) t[k] = (j & (1<<k)) ? i : 0;

	REP(k,N-z) t[k+z] = (a[k] & i) ^ t[k+y] ^ t[k];
	
	bool f = true;
	REP(k,N){
	  if((t[k]^t[(k+y)%N]^t[(k+z)%N]) != (a[k]&i)){
	    f = false;
	    break;
	  }
	}

	if(!f) continue;
	++cnt;
	  
	break;
      }

      REP(j,N) b[j] += t[j];
    }
    
    
    if(intera.answer(b) == -1) return 0;
  }
  
  return 0;
}
