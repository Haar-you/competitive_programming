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
  int a, b;
public:
  Test(){
    std::random_device rnd;
    std::uniform_int_distribution<> rndd(0, 1073741823);
    a = rndd(rnd);
    b = rndd(rnd);
    //cerr << a << " " << b << endl;
  }
  int _ask (int c, int d){
    if((a^c) > (b^d)) return 1;
    if((a^c) < (b^d)) return -1;
    return 0;
  }
  int ask(int c, int d){
    cout << "? " << c << " " << d << endl << flush;
    int a; cin >> a;
    return a;
    
    /*int a = _ask(c,d);
    cerr << c << " " << d << endl;
    cerr << a << endl;
    return a;*/
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  Test test;

  
  int s = test.ask(0,0); //a,bの大小を確認
  int a = 0, b = 0;
  
  REV(i,29,0){
    int x = test.ask(a+(1<<i),b);
    int y = test.ask(a,b+(1<<i));

    if(s==1){ // a > b
      if(x==-1 && y==1) a += (1<<i), b += (1<<i);
      else if(x==1 && y==-1) ;
      else a += (1<<i), s = x;
    }else if(s==-1){ // a < b
      if(x==-1 && y==1) a += (1<<i), b += (1<<i);
      else if(x==1 && y==-1) ;
      else b += (1<<i), s = x;
    }else{ // a == b
      if(x==-1 && y==1) a += (1<<i), b += (1<<i);
    }
  }

  cout << "! " << a << " " << b << endl;
  
  return 0;
}
