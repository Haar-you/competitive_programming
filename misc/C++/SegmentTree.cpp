#ifndef COMPILE_TEST
#define COMPILE_TEST
#include "Basic.cpp"
#endif

/*
 * 点更新範囲取得のSegment tree
 * 範囲更新点取得のSegment tree
 * 範囲更新範囲取得のSegment tree
 * 点更新範囲取得の動的Segment tree
 * 範囲更新点取得の動的Segment tree
 * 2D Segment tree
 */

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
  SegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd): e(e), f(f), upd(upd){
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

  T get(int x, int y){return aux(x,y,0,0,(size+1)/2);}
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
  void get_aux(int i){if(i>0) find_aux((i-1)/2); propagate(i);}
public:
  LazySegmentTree(int n, T e, function<T(T,T)> f, function<T(T,T)> upd): f(f), e(e), upd(upd){
    size = 1;
    while(size < n) size *= 2;
    size = size*2-1;
    vec = vector<T>(size, e);
  }
  void update(int s, int t, T x){update_aux(s,t,0,0,size/2+1,x);}
  T get(int i){
    int j=i+size/2;
    get_aux((j-1)/2);
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
  
  T get(int x, int y){
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
  DynamicSegmentTree(LLI n, const M &zero, Op op): size(pow(2,ceil(log2(n)))), zero(zero), op(op){ // [0,n)
    root = new Node(zero);
  }

  void update(LLI i, M &x){
    _update(root, 0, size, i, x);
  }

  M get(LLI x, LLI y){
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
  DynamicLazySegmentTree(LLI n, const M &zero, Op op): size(pow(2,ceil(log2(n)))), zero(zero), op(op){ // [0,n)
    root = new Node(zero);
  }

  void update(LLI s, LLI t, M &x){
    _update(root, 0, size, s, t, x);
  }

  M get(LLI x){
    _query(root, 0, size, x);
    return umap[x]->val;
  }
};


// 2Dセグメント木
/*
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068 // Case#7でMLE


 */

template <typename T> class SegmentTree2D{
  int w, h;
  vector<vector<T>> dat;

  T e;
  function<T(T,T)> f, upd;

  T get_w(int x1, int y1, int x2, int y2, int i, int l, int r, int y){
    if(x2 <= l or r <= x1) return e;
    if(x1 <= l and r <= x2) return dat[i][y];
    return f(get_w(x1,y1,x2,y2,i*2+1,l,(l+r)/2,y), get_w(x1,y1,x2,y2,i*2+2,(l+r)/2,r,y));
  }
  
  T get_h(int x1, int y1, int x2, int y2, int i, int l, int r){
    if(y2 <= l or r <= y1) return e;
    if(y1 <= l and r <= y2) return get_w(x1,y1,x2,y2,0,0,(w+1)/2,i);
    return f(get_h(x1,y1,x2,y2,i*2+1,l,(l+r)/2), get_h(x1,y1,x2,y2,i*2+2,(l+r)/2,r));
  }

public:
  SegmentTree2D(int width, int height, const T &e, const function<T(T,T)> &f, const function<T(T,T)> &upd):
    e(e), f(f), upd(upd){

    w = 1;
    while(w < width) w *= 2;
    w = w*2-1;

    h = 1;
    while(h < height) h *= 2;
    h = h*2-1;
    
    dat = vector<vector<T>>(w, vector<T>(h));
  }

  T get(int x1, int y1, int x2, int y2){ // [(x1,y1),(x2,y2))
    return get_h(x1,y1,x2,y2,0,0,(h+1)/2);
  }

  void update(int x, int y, const T &val){
    int i = x+(w+1)/2-1;
    int j = y+(h+1)/2-1;

    dat[i][j] = upd(dat[i][j], val);

    for(int X=i, Y=j; X>0; X=(X-1)/2){
      dat[(X-1)/2][Y] = f(dat[((X-1)/2)*2+1][Y], dat[((X-1)/2)*2+2][Y]);
    }

    for(int Y=j; Y>0; Y=(Y-1)/2){
      for(int X=i; ; X=(X-1)/2){
	dat[X][(Y-1)/2] = f(dat[X][((Y-1)/2)*2+1], dat[X][((Y-1)/2)*2+2]);
	if(X==0) break;
      }
    }
  }
};

