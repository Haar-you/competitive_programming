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

class Test{
  int x;
public:
  int c;
  int coin = 1000;
  Test(int N, int c): c(c){
    std::random_device rnd;
    std::uniform_int_distribution<> rndd(1, N);
    x = rndd(rnd);
  }
  int connect(int y){
    cout << 1 << " " << y << endl;
    coin--;

    int r; cin >> r;
    return r;
    
    //if(y>=x) return 1;
    //return 0;
  }
  void fix(){
    cout << 2 << endl << flush;
    coin -= c;
  }
  void answer(int y){
    cout << 3 << " " << y << endl << flush;
    //cerr << x << " " << (x==y ? "AC" : "WA") << endl;
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N,c; cin >> N >> c;

  Test test(N,c);

  int lower=0, upper=N;
  int q;

  vector<int> checked(N+1,-1);

  REP(_,200){
    q = lower+ceil((double)(upper-lower)/8);

    if(checked[q] != -1) break;

    int r = test.connect(q);
    checked[q] = r;

    if(r == 0){
      lower = q;
    }else{
      test.fix();
      upper = q;
    }
  }

  FORE(i,1,N){
    if(checked[i] == 1){
      test.answer(i);
      break;
    }
  }
  
  return 0;
}
