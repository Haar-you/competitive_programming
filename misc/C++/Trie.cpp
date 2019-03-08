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

/*
  binary trie tree
  
  //function
  void insert(T val) // verified by https://beta.atcoder.jp/contests/dwacon5th-final-open/tasks/dwacon5th_final_b
  void erase(T val) // verified by https://beta.atcoder.jp/contests/dwacon5th-final-open/tasks/dwacon5th_final_b

  T min_element(T diff) // verified by https://beta.atcoder.jp/contests/dwacon5th-final-open/tasks/dwacon5th_final_b
  T max_element(T diff)

  vector<T> to_list()

  int lower_bound(T val)
  int upper_bound(T val)

  int size()
  bool empty()

  T at(int index)

 */

template <typename T, unsigned int B> class BinaryTrie{
protected:
  struct node{
    int count;
    node *ch[2];
    node(): count(0){
      ch[0] = ch[1] = nullptr;
    }
  };

  node *root = nullptr;

protected:
  int count(node *t) const {return t ? t->count : 0;}

public:
  int size() const {return root ? root->count : 0;}
  bool empty() const {return !root;}

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

protected:
  node* insert(node *t, const T &val, unsigned int depth = 1){
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
  node* erase(node *t, const T &val, unsigned int depth = 1){
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
  T min_element(node *t, const T &diff, unsigned int depth = 1) const {
    if(depth > B) return 0;
    int b = (diff >> (B-depth)) & 1;
    b ^= !t->ch[b];
    return min_element(t->ch[b], diff, depth+1) | (b << (B-depth));
  }
  
public:
  T min_element(const T &diff = 0) const {
    return min_element(root, diff);
  }

protected:
  T max_element(node *t, const T &diff, unsigned int depth = 1) const {
    if(depth > B) return 0;
    int b = !((diff >> (B-depth)) & 1);
    b ^= !t->ch[b];
    return max_element(t->ch[b], diff, depth+1) | (b << (B-depth));
  }
  
public:
  T max_element(const T &diff = 0) const {
    return max_element(root, diff);
  }

protected:
  T at(node *t, int index, unsigned int depth = 1) const {
    if(depth > B) return 0;

    int c = count(t->ch[0]);
    if(t->ch[0] && index < c) return at(t->ch[0], index, depth+1);
    else return at(t->ch[1], index-c, depth+1) | ((T)1 << (B-depth));
  }

public:
  T at(int index) const {
    return at(root, index);
  }

  T operator[](int index) const {
    return at(index);
  }


protected:
  int lower_bound(node *t, const T &val, unsigned int depth = 1) const {
    if(!t) return 0;

    int b = (val >> (B-depth)) & 1;

    return (b ? count(t->ch[0]) : 0) + lower_bound(t->ch[b], val, depth+1);
  }

public:
  int lower_bound(const T &val) const {
    return lower_bound(root, val);
  }

  int upper_bound(const T &val) const{
    return lower_bound(root, val+1);
  }

protected:
  void debug(node *t){
    if(!t) return;
    cerr << count(t) << " " << count(t->ch[0]) << " " << count(t->ch[1]) << endl;
    debug(t->ch[0]);
    debug(t->ch[1]);
  }

public:
  void debug(){
    debug(root);
  }
};



int main(){
  const int B = 32;
  BinaryTrie<int, B> bt;

  bt.insert(1);
  bt.insert(1);
  bt.insert(2);
  bt.insert(3);
  bt.insert(10);
  bt.insert(25);


  dump(bt.size());

  dump(bt.to_list());

  dump(bt.min_element());
  dump(bt.max_element());

  dump(bt[0]);
  dump(bt.at(1));
  dump(bt.at(2));
  dump(bt.at(3));
  dump(bt.at(4));
  dump(bt.at(5));

  dump(bt.lower_bound(10));
  dump(bt.upper_bound(10));

  return 0;
}
