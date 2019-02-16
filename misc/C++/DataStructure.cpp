#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#endif

/*
 * Unioin-Find tree
 * Weighted Union-Find tree
 * 点更新範囲取得のSegment tree
 * 範囲更新点取得のSegment tree
 * 範囲更新範囲取得のSegment tree
 * 点更新範囲取得の動的Segment tree
 * 範囲更新点取得の動的Segment tree
 * Sparse table
 * Binary indexed tree
 */

//unionfind木
class UnionFind{
  vector<int> _parent, _depth, _size;
public:
  UnionFind(int n): _parent(n), _depth(n,1), _size(n,1){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else return _parent[i] = root(_parent[i]);
  }
  bool same(int i, int j){return root(i) == root(j);}
  void merge(int i, int j){
    int ri = root(i), rj = root(j);
    if(ri != rj){
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri];
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
      }
    }
  }
  int size(int i){return _size[root(i)];}
};

//重み付きunoinfind木
class WeightedUnionFind{
  vector<int> _parent, _depth, _size, _weight;
public:
  WeightedUnionFind(int n): _parent(n), _depth(n,1), _size(n,1), _weight(n,0){REP(i, n) _parent[i] = i;}
  int root(int i){
    if(_parent[i] == i) return i;
    else {int p=root(_parent[i]); _weight[i] += _weight[_parent[i]]; return _parent[i] = p;}
  }
  int weight(int i){root(i); return _weight[i];} 
  bool same(int i, int j){return root(i) == root(j);}
  bool diff(int i, int j, int &res){res = weight(i)-weight(j); return same(i,j);}
  void merge(int i, int j, int w){
    int ri = root(i), rj = root(j);
    if(ri != rj){
      if(_depth[ri] < _depth[rj]){
	_parent[ri] = rj; _size[rj] += _size[ri]; _weight[ri] = w - _weight[i] + _weight[j];
      }else{
	_parent[rj] = ri; _size[ri] += _size[rj]; _weight[rj] = -w + _weight[i] - _weight[j];
	if(_depth[ri] == _depth[rj]) ++_depth[ri];
      }
    }
  }
  int size(int i){return _size[root(i)];}
};

// セグメント木
// (T, f :: T->T->T)はmonoid, eは単位元
template <typename T> class SegmentTree{
private:
  int size;
  vector<T> vec;
  T e;
  function<T(T,T)> f, upd;
  
  T aux(int x, int y, int i, int l, int r){
    if(r<=x || y<=l) return e;
    else if(x<=l && r<=y) return vec[i];
    else return f(aux(x,y,i*2+1,l,(l+r)/2), aux(x,y,i*2+2,(l+r)/2,r));
  };

public:
  SegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd):  f(f), e(e), upd(upd){
    size = 1;
    while(size < n) size *= 2;
    size = size*2-1;
    vec = vector<T>(size, e);
  }
  void update(int i, T x){
    int j = i+(size+1)/2-1;
    vec[j] = upd(vec[j], x);
    --j;
    while(j>=0){
      vec[j/2] = f(vec[(j/2)*2+1], vec[(j/2)*2+2]);
      (j /= 2) -= 1;
    }
  }

  T find(int x, int y){return aux(x,y,0,0,(size+1)/2);}
};

// 遅延セグメント木
template <typename T> class LazySegmentTree{
private:
  int size;
  vector<T> vec;
  function<T(T,T)> f, upd;
  T e;
  void propagate(int i){
    if(i<size/2){
      vec[i*2+1] = f(vec[i], vec[i*2+1]);
      vec[i*2+2] = f(vec[i], vec[i*2+2]);
      vec[i] = e;
    }
  }
  void update_aux(int s, int t, int i, int l, int r, T x){
    if(r <= s || t <= l) return;
    else if(s <= l && r <= t) vec[i] = upd(vec[i],x);
    else{
      propagate(i);
      update_aux(s,t,i*2+1,l,(l+r)/2,x);
      update_aux(s,t,i*2+2,(l+r)/2,r,x);
    }
  }
  void find_aux(int i){if(i>0) find_aux((i-1)/2); propagate(i);}
public:
  LazySegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd): f(f), e(e), upd(upd){
    size = 1;
    while(size < n) size *= 2;
    size = size*2-1;
    vec = vector<T>(size, e);
  }
  void update(int s, int t, T x){update_aux(s,t,0,0,size/2+1,x);}
  T find(int i){
    int j=i+size/2;
    find_aux((j-1)/2);
    return vec[j];
  }
};

template <typename T, typename U> class RangeRangeSegmentTree{
  int size;
  T e1;
  vector<T> vec1;
  function<T(T,T)> f1;
  U e2;
  vector<U> vec2;
  function<U(U,U)> f2;
  function<T(U,T,int)> g;

  void propagate(int i, int l){
    if(vec2[i] == e2) return;
    if(i < size/2){
      vec2[i*2+1] = f2(vec2[i], vec2[i*2+1]);
      vec2[i*2+2] = f2(vec2[i], vec2[i*2+2]);
    }
    vec1[i] = g(vec1[i], vec2[i], l);
    vec2[i] = e2;
  }

  T update_aux(int i, int l, int r, int s, int t, const U &x){
    propagate(i,r-l);
    if(r <= s || t <= l) return vec1[i];
    else if(s <= l && r <= t){
      vec2[i] = f2(vec2[i],x);
      propagate(i,r-l);
      return vec1[i];
    }
    else return vec1[i] = f1(update_aux(i*2+1,l,(l+r)/2,s,t,x), update_aux(i*2+2,(l+r)/2,r,s,t,x));
  }
  
  T query_aux(int i, int l, int r, int x, int y){
    propagate(i,r-l);
    if(r <= x || y <= l) return e1;
    else if(x <= l && r <= y) return vec1[i];
    else return f1(query_aux(i*2+1,l,(l+r)/2,x,y), query_aux(i*2+2,(l+r)/2,r,x,y));
  }
  
public:
  RangeRangeSegmentTree(){}
  RangeRangeSegmentTree(int n, const T &e1, const function<T(T,T)> f1, const U &e2, const function<U(U,U)> f2, const function<T(T,U,int)> g):
    e1(e1), f1(f1), e2(e2), f2(f2), g(g){
    size = 1;
    while(size<n) size*=2;
    size *= 2;
    size -= 1;

    vec1 = vector<T>(size,e1);
    vec2 = vector<U>(size,e2);
  }

  void update(int s, int t, const U &x){
    update_aux(0,0,size/2+1,s,t,x);
  }
  
  T query(int x, int y){
    return query_aux(0,0,size/2+1,x,y);
  }
};



// 動的セグメント木
template <typename M> class DynamicSegmentTree{
  using Op = function<M(M,M)>;
  class Node{
  public:
    M val;
    Node *left = nullptr, *right = nullptr;
    Node(const M &val): val(val) {}
  };
  
  Node *root = nullptr;
  LLI size;
  M zero;
  Op op;
  unordered_map<LLI, Node*> umap;

  Node* _update(Node *node, LLI l, LLI r, LLI pos, const M &val){
    LLI m = (l+r)/2;
    if(r-l == 1){
      if(node) node->val = op(node->val, val);
      else node = new Node(val);
      umap[pos] = node;
    }else{
      if(!node) node = new Node(val);
      if(pos<m) node->left = _update(node->left, l, m, pos, val);
      else node->right = _update(node->right, m, r, pos, val);
      node->val = op((node->left ? (node->left)->val : zero), (node->right ? (node->right)->val : zero));
    }
    return node;
  }

  M _query(Node* node, LLI l, LLI r, LLI x, LLI y){
    if(!node) return zero;
    LLI m = (l+r)/2;
    if(x <= l && r <= y) return node ? node->val : zero;
    if(r < x || y < l) return zero;
    return op(_query(node->left, l, m, x, y), _query(node->right, m, r, x, y));
  }

public:
  DynamicSegmentTree(LLI n, const M &zero, Op op): size(pow(2,ceil(log2(n)))), zero(zero), op(op){ // [0,2^n)
    root = new Node(zero);
  }

  void update(LLI i, M &x){
    _update(root, 0, size, i, x);
  }

  M query(LLI x, LLI y){
    return _query(root, 0, size, x, y);
  }

  M operator[](LLI i) const{
    if(umap.find(i) != umap.end()) return umap[i]->val;
    else return zero;
  }
};

// 動的遅延セグメント木
template <typename M> class DynamicLazySegmentTree{
  using Op = function<M(M,M)>;
  class Node{
  public:
    M val;
    Node *left = nullptr, *right = nullptr;
    Node(const M &val): val(val) {}
  };
  
  Node *root = nullptr;
  LLI size;
  M zero;
  Op op;
  unordered_map<LLI, Node*> umap;

  Node* propagate(Node *node, LLI l, LLI r){
    if(r-l > 1){
      int m = (l+r)/2;
      if(node->left) (node->left)->val = op(node->val, (node->left)->val);
      else node->left = new Node(node->val);

      if(node->right) (node->right)->val = op(node->val, (node->right)->val);
      else node->right = new Node(node->val);

      node->val = zero;
    }
    return node;
  }

  Node* _update(Node *node, LLI l, LLI r, LLI x, LLI y, const M &val){
    LLI m = (l+r)/2;
    if(r-l == 1){
      if(x <= l && r <= y) node->val = op(node->val, val);
      umap[l] = node;
      return node;
    }
    if(r < x || y < l) return node;
    else if(x <= l && r <= y) node->val = op(node->val, val);
    else{
      propagate(node, l, r);
      _update(node->left, l, m, x, y, val);
      _update(node->right, m, r, x, y, val);
    }
    return node;
  }

  Node* _query(Node* node, LLI l, LLI r, LLI x){
    if(r-l == 1){
      umap[l] = node;
      return node;
    }
    propagate(node, l, r);
    int m = (l+r)/2;
    if(x < m) _query(node->left, l, m, x);
    else _query(node->right, m, r, x);
    return node;
  }

public:
  DynamicLazySegmentTree(LLI n, const M &zero, Op op): size(pow(2,ceil(log2(n)))), zero(zero), op(op){ // [0,2^n)
    root = new Node(zero);
  }

  void update(LLI s, LLI t, M &x){
    _update(root, 0, size, s, t, x);
  }

  M query(LLI x){
    _query(root, 0, size, x);
    return umap[x]->val;
  }
};


// SparseTable
template <typename T> class SparseTable{
  using Op = function<T(T,T)>;
  Op f;
  vector<vector<T>> a;
  vector<int> log_table;
public:
  SparseTable(vector<T> &v, Op f): f(f){
    int n = v.size();
    int logn = 0;
    while((1<<logn) <= n) ++logn;
    
    a = vector<vector<T>>(n, vector<T>(logn));
    REP(i,n) a[i][0] = v[i];
    FOR(j,1,logn) REP(i,n) a[i][j] = f(a[i][j-1], a[min(n-1, i+(1<<(j-1)))][j-1]);

    log_table = vector<int>(n+1);
    FOR(i,2,n+1) log_table[i] = log_table[i>>1] + 1;
  }
  
  T query(int s, int t){
    int k = log_table[t-s+1];
    return f(a[s][k], a[t-(1<<k)+1][k]);
  }
};


//Binary Indexed Tree (1-indexed)
template <typename T> class BIT_1{
private:
  vector<T> tree;
  int n;
public:
  BIT_1(int size): tree(size+1, 0), n(size){}
  void update(int x, T a){while(x <= n){tree[x] += a; x += (x & (-x));}}
  T sum(int x){T a = 0; while(x > 0){a += tree[x]; x -= (x & (-x));} return a;}
  T get(int x){return sum(x) - (x==1 ? 0 : sum(x-1));}
};

//Binary Indexed Tree (0-indexed)
template <typename T> class BIT_0{
private:
  vector<T> tree;
  int n;
public:
  BIT_0(int size): tree(size, 0), n(size){}
  void update(int x, T a){while(x < n){tree[x] += a; x |= (x + 1);}}
  T sum(int x){T a = 0; while(x >= 0){a += tree[x]; x = (x & (x+1)) - 1;} return a;}
  T get(int x){return sum(x) - (x==0 ? 0 : sum(x-1));}
};


// 追加直線の傾きが単調減少、minクエリの値が単調増加
template <typename T> class ConvexHullTrick{
public:
  deque<pair<T,T>> lines;

  bool is_needless(pair<T,T> a, pair<T,T> b, pair<T,T> c){
    return (a.snd-b.snd)*(a.fst-c.fst) >= (a.snd-c.snd)*(a.fst-b.fst);
  }
  
  void add(T a, T b){
    if(!lines.empty()){
      auto l = lines.back();
      if(l.fst == a){
	if(l.snd < b) return;
	else lines.pop_back();
      }
    }
    while(lines.size()>=2 && is_needless(make_pair(a,b), lines.back(), *(lines.end()-2))){
      lines.pop_back();
    }
    lines.push_back(make_pair(a,b));
  }

  T apply(pair<T,T> f, T x){
    return f.fst*x + f.snd;
  }

  T query(T x){
    while(lines.size()>=2 && apply(lines[0],x)>apply(lines[1],x)){
      lines.pop_front();
    }
    return apply(lines[0],x);
  }
};
