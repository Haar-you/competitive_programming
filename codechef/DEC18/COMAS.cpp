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
public:
  vector<int> a;
  Interactive(int N): a(N){
    iota(ALL(a),1);
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    shuffle(ALL(a),engine);
  }
  pair<int,int> ask(const vector<int> &v){
    //printf("? %d %d %d %d %d\n", v[0], v[1], v[2], v[3], v[4]);
    cout << "?" << " " << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << v[4] << endl << flush;

    int p,q; cin >> p >> q;
    return make_pair(p,q);
    
    /*vector<pair<int,int>> t(5);
    REP(i,5) t[i] = make_pair(a[v[i]-1], v[i]);
    sort(ALL(t));
    //fprintf(stderr, "> %d %d\n", t[2].second, t[3].second);
    return make_pair(t[2].second, t[3].second);*/
  }
  void answer(int x){
    //printf("! %d\n", x);
    cout << "!" << " " << x << endl << flush;

    //cerr << max_element(ALL(a)) - a.begin() + 1 << endl;
    //join(cerr,ALL(a));
  }
};

int main(){
  int T; cin >> T;

  REP(_,T){
    int N; cin >> N;
    Interactive intera(N);

    vector<bool> checked(N,false);
    deque<int> dq;
    REP(i,N) dq.push_back(i+1);

    int Q = N/2 + 4;
    
    pair<int,int> p;
    REP(i,Q){
      vector<int> t;
      
      if(dq.size() >= 5){
	REP(j,5){t.push_back(dq.front()); dq.pop_front();}

	p = intera.ask(t);
	checked[p.first-1] = checked[p.second-1] = true;

	REP(j,5) if(t[j] != p.first && t[j] != p.second) dq.push_back(t[j]);
	  
      }else if(dq.size() == 4){
	REP(j,4){t.push_back(dq.front()); dq.pop_front();}
	int d = find(ALL(checked),true) - checked.begin() + 1;
	t.push_back(d);

	p = intera.ask(t);
	checked[p.first-1] = checked[p.second-1] = true;
 
	REP(j,5) if(t[j] != p.first && t[j] != p.second && t[j] != d) dq.push_back(t[j]);
      }else if(dq.size() == 3){
	int a = dq.front(); dq.pop_front();
	int b = dq.front(); dq.pop_front();
	int c = dq.front(); dq.pop_front();

	int d;
	REP(j,N){
	  if(checked[j] && j+1 != p.first && j+1 != p.second){
	    d = j+1;
	    break;
	  }
	}

	auto x = intera.ask({d,b,c,p.first,p.second});
	auto y = intera.ask({a,d,c,p.first,p.second});
	auto z = intera.ask({a,b,d,p.first,p.second});

	if(x==y) intera.answer(c);
	if(x==z) intera.answer(b);
	if(y==z) intera.answer(a);
      }
    }
  }
  
  return 0;
}
