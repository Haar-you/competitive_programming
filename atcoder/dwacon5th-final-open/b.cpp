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
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifdef DEBUG
#include <misc/C++/Debug.cpp>
#else
#define dump(x)
#endif

#define pln(x) cout << (x) << endl
#define gcd __gcd

using namespace std;
template <class T> constexpr T lcm(T m, T n){return m/gcd(m,n)*n;}

template <typename T> using V = vector<T>;
template <typename T, typename U> using P = pair<T,U>;
template <typename I> void join(ostream &ost, I s, I t, string d=" "){for(auto i=s; i!=t; ++i){if(i!=s)ost<<d; ost<<*i;}ost<<endl;}
template <typename T> istream& operator>>(istream &is, vector<T> &v){for(auto &a : v) is >> a; return is;}
template <typename T, typename U> istream& operator>>(istream &is, pair<T,U> &p){is >> p.first >> p.second; return is;}

template <typename T, typename U> T& chmin(T &a, const U &b){return a = (a<=b?a:b);}
template <typename T, typename U> T& chmax(T &a, const U &b){return a = (a>=b?a:b);}
template <typename T, size_t N, typename U> void fill_array(T (&a)[N], const U &v){fill((U*)a, (U*)(a+N), v);}

template <typename T, unsigned int B> 
class BinaryTrie{
  struct node{
    int count;
    node *ch[2];
    node(): count(0){
      ch[0] = ch[1] = nullptr;
    }
  };

  node *root = nullptr;

protected:
  node* insert(node *t, const T &val, int depth = 1){
    if(!t) t = new node();
    ++(t->count);

    if(depth > B) return t;

    int b = (val >> (B-depth)) & 1;
    t->ch[b] = insert(t->ch[b], val, depth+1);
    return t;
  }
public:
  void insert(const T &val){
    root = insert(root, val);
  }

protected:
  node* erase(node *t, const T &val, int depth = 1){
    if(!t) return t;

    --(t->count);
    if(t->count == 0) return nullptr;
    if(depth > B) return t;

    int b = (val >> (B-depth)) & 1;
    t->ch[b] = erase(t->ch[b], val, depth+1);
    return t;
  }
public:
  void erase(const T &val){
    root = erase(root, val);
  }

protected:
  T min_element(node *t, const T &diff, int depth = 1){
    if(depth > B) return 0;
    int b = (diff >> (B-depth)) & 1;
    b ^= !t->ch[b];
    return min_element(t->ch[b], diff, depth+1) | (b << (B-depth));
  }
public:
  T min_element(const T &diff = 0){
    return min_element(root, diff);
  }


public:
  int size(){
    return root->count;
  }


protected:
  void to_list(node *t, const T val, vector<T> &ret){
    if(!t) return;
    if(!t->ch[0] && !t->ch[1]) ret.push_back(val);

    if(t->ch[0]) to_list(t->ch[0], val<<1, ret);
    if(t->ch[1]) to_list(t->ch[1], (val<<1)|1, ret);
  }
public:
  vector<T> to_list(){
    vector<T> ret;
    to_list(root, 0, ret);
    return ret;
  }
};


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N;
  while(cin >> N){
    vector<int> a(N); cin >> a;

    vector<int> s(N+1);
    REP(i,N) s[i+1] = s[i] ^ a[i];

    BinaryTrie<unsigned,32> bt;
    REP(i,N-1){
      bt.insert(s[i+1]);
    }

    vector<int> ans(N);
    int temp = 0;
    REP(i,N-1){
      temp = bt.min_element(temp);
      bt.erase(temp);
      ans[i] = temp;
    }
    ans[N-1] = s[N];
    REV(i,N-2,0) ans[i+1] ^= ans[i];
    join(cout, ALL(ans));
  }
  
  return 0;
}
