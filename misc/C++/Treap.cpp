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

mt19937 my_rand(static_cast<unsigned int>(time(nullptr)));

template <typename T> struct treap_node{
  T val;
  T sum;
  treap_node *right, *left;
  int priority;
  int size;
  bool rev;

  treap_node(T val): val(val), sum(val), size(1), rev(false){
    right = left = nullptr;
    priority = my_rand();
  }

  friend ostream& operator<<(ostream &os, const treap_node<T> &t){
    os << t.val << " ";
    if(t.left) os << (t.left)->val; else os << "null"; os << " ";
    if(t.right) os << (t.right)->val; else os << "null";
    return os;
  }
};

/* index-ordered treap */

template <typename T> class Treap{
protected:
  using Op = function<T(T,T)>;
  using node = treap_node<T>;
  
  T e;
  Op f;
  node *root = nullptr;

public:
  Treap(): e(T()), f([&](const T &a, const T &b){return e;}){}
  Treap(int n): e(T()), f([&](const T &a, const T &b){return e;}){REP(i,n) push_back(e);}
  Treap(const T &e, const Op f): e(e), f(f){}
  Treap(node *t, const T &e, const Op f): e(e), f(f), root(t){}
  Treap(int n, const T &e, const Op f): e(e), f(f){REP(i,n) push_back(e);}
  Treap(int n, const T &e): e(e), f([&](const T &a, const T &b){return e;}){REP(i,n) push_back(e);}
  
  int size() const {return count(root);}
  bool empty() const {return !root;}

protected:
  int count(node *t) const {return !t ? 0 : t->size;}
  T sum(node *t) const {return !t ? e : t->sum;}

  node* update_node_status(node *t){
    t->size = count(t->right) + count(t->left) + 1;
    t->sum = f(f(sum(t->right), sum(t->left)), t->val);
    return t;
  }

  void pushdown(node *t){
    if(!t) return;
    if(t->rev){
      swap(t->left, t->right);
      if(t->left) t->left->rev ^= true;
      if(t->right) t->right->rev ^= true;
      t->rev = false;
    }
    update_node_status(t);
  }
  
  node* rotate_right(node *t){
    node *s = t->left;
    t->left = s->right;
    s->right = t;
    update_node_status(t);
    update_node_status(s);
    return s;
  }

  node* rotate_left(node *t){
    node *s = t->right;
    t->right = s->left;
    s->left = t;
    update_node_status(t);
    update_node_status(s);
    return s;
  }

protected:
  node* insert(node *t, int k, T val){
    auto s = split(t, k);
    return merge(s.first, merge(new node(val), s.second));
  }
  
public:
  void insert(int k, const T &val){root = insert(root, k, val);}
  void insert(int k){insert(k, e);}

protected:
  node* erase(node *t, int k){
    node *l, *r, *m;
    tie(l,r) = split(t, k);
    tie(m,r) = split(r, 1);
    return merge(l,r);
  }
  
public:
  void erase(int k){root = erase(root, k);}

protected:
  node* merge(node *l, node *r){
    pushdown(l);
    pushdown(r);
    if(!l || !r) return !l ? r : l;
    if(l->priority > r->priority){
      l->right = merge(l->right, r);
      return update_node_status(l);
    }else{
      r->left = merge(l, r->left);
      return update_node_status(r);
    }
  }
  
public:
  void merge_left(const Treap<T> &t){root = merge(t.root, root);}
  void merge_right(const Treap<T> &t){root = merge(root, t.root);}

protected:
  pair<node*,node*> split(node *t, int k){
    if(!t) return make_pair(nullptr, nullptr);
    pushdown(t);
    int c = count(t->left);
    if(k <= c){
      auto s = split(t->left, k);
      t->left = s.second;
      return make_pair(s.first, update_node_status(t));
    }else{
      auto s = split(t->right, k-(c+1));
      t->right = s.first;
      return make_pair(update_node_status(t), s.second);
    }
  }
  
public:
  pair<Treap<T>,Treap<T>> split(int k){
    node *l, *r;
    tie(l, r) = split(root, k);
    return make_pair(Treap<T>(l,e,f), Treap<T>(r,e,f));
  }


protected:
  node* reverse(node *t, int l, int r){
    node *a, *b, *c;
    tie(a,c) = split(t, l);
    tie(b,c) = split(c, r-l);
    b->rev ^= true;
    return t = merge(merge(a,b),c);
  }
  
public:
  void reverse(int l, int r){
    reverse(root, l, r);
  }

protected:
  void update_node(node *t, int k, const T &val){
    int c = count(t->left);
    if(k==c) t->val = val;
    else if(k>c) update_node(t->right, k-(c+1), val);
    else update_node(t->left, k, val);
    update_node_status(t);
  }
  
public:
  void update(int k, const T &val){update_node(root, k, val);}


protected:
  node* get_node(node *t, int k) const {
    if(!t) return t;
    int c = count(t->left);
    if(k==c) return t;
    if(k>c) return get_node(t->right, k-(c+1));
    else return get_node(t->left, k);
  }

  T get_sum(node *t, int l, int r) const { // [l,r)
    if(!t) return e;
    l = max(0, l);
    r = min(t->size, r);
    if(l >= r) return e;
    if(l == 0 && r == t->size) return t->sum;
    int c = count(t->left);
    T lv = get_sum(t->left, l, r);
    T rv = get_sum(t->right, l-(c+1), r-(c+1));
    if(l <= c && c < r) return f(lv, f(t->val, rv));
    else return f(lv, rv);
  }
  
public:
  const T& get(int k) const {
    node* t = get_node(root, k);
    return t->val;
  }

  const T& get(int l, int r) const { // [l,r)
    return get_sum(root, l, r);
  }
  
protected:
  node* inorder(node *t, vector<T> &v, int &index) const {
    if(!t) return t;
    inorder(t->left, v, index);
    v[index] = t->val;
    index++;
    inorder(t->right, v, index);
    return t;
  }

public:
  vector<T> to_list() const {
    vector<T> v(size());
    int index = 0;
    inorder(root, v, index);
    return v;
  }

public:
  void push_back(const T &val){insert(size(), val);}
  void push_front(const T &val){insert(0, val);}

  void pop_front(){erase(0);}
  void pop_back(){erase(size()-1);}

  const T& front() const {return get(0);}
  const T& back() const {return get(size()-1);}


  void debug_(node *t){
    if(!t) return;
    dump(*t);
    debug_(t->left);
    debug_(t->right);
  }
  
  void debug(){
    debug_(root);
  }
};


/* value-ordered treap */

template <typename T> class Ordered_treap : public Treap<T>{
protected:
  using node = treap_node<T>;
  function<bool(T,T)> lt;
  function<bool(T,T)> eq;

  bool le(const T &a, const T &b) const {return lt(a,b) or eq(a,b);}
  bool ge(const T &a, const T &b) const {return not lt(a,b);}
  bool gt(const T &a, const T &b) const {return not le(a,b);}
  
public:
  Ordered_treap(): Treap<T>(), lt([](const T &a, const T &b){return a<b;}), eq([](const T &a, const T &b){return a==b;}){}
  Ordered_treap(const function<bool(T,T)> &lt, const function<bool(T,T)> &eq): Treap<T>(), lt(lt), eq(eq){}
  Ordered_treap(const function<bool(T,T)> &lt): Treap<T>(), lt(lt), eq([](const T &a, const T &b){return a==b;}){}

  /* lower_bound */
protected:
  int lower_bound(node *t, const T &val) const {
    if(!t) return 0;
    int c = Treap<T>::count(t->left);
    if(ge(t->val, val)) return min(c, lower_bound(t->left, val));
    else return c+1+lower_bound(t->right, val);
  }
  
public:
  int lower_bound(const T &val) const {
    return lower_bound(Treap<T>::root, val);
  }

  /* upper_bound */
protected:
  int upper_bound(node *t, const T &val) const {
    if(!t) return 0;
    int c = Treap<T>::count(t->left);
    if(gt(t->val, val)) return min(c, upper_bound(t->left, val));
    else return c+1+upper_bound(t->right, val);
  }
  
public:
  int upper_bound(const T &val) const {
    return upper_bound(Treap<T>::root, val);
  }

  /* insert by order */
public:
  void insert_by_order(const T &val){
    int k = lower_bound(val);
    Treap<T>::insert(k, val);
  }

  /* find by order */
public:
  int find_by_order(const T &val) const {
    int k = lower_bound(Treap<T>::root, val);
    if(k >= Treap<T>::size()) return -1;
    auto t = Treap<T>::get(k);
    return (eq(t, val) ? k : -1);
  }

  /* erase by order */
public:
  void erase_by_order(const T &val){
    int k = find_by_order(val);
    if(k == -1) return;
    Treap<T>::erase(k);
  }
};



int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  Ordered_treap<int> t([](int a, int b){return a<b;});
  
  t.insert_by_order(4);
  t.insert_by_order(3);
  t.insert_by_order(4);
  t.insert_by_order(6);
  t.insert_by_order(5);
  t.insert_by_order(8);
  
  dump(t.to_list());

  t.erase_by_order(5);

  dump(t.to_list());
  
  FORE(i,0,10){
    dump(t.find_by_order(i));
  }
  
  return 0;
}
