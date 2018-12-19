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

int Q,K;

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
      if(node->left) (node->left)->val = op((node->left)->val, node->val);
      else node->left = new Node(node->val);

      if(node->right) (node->right)->val = op((node->right)->val, node->val);
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

  void update(LLI s, LLI t, const M &x){
    _update(root, 0, size, s, t, x);
  }

  M query(LLI x){
    _query(root, 0, size, x);
    return umap[x]->val;
  }
};

void solve(){
  using T = tuple<int,int,int,int,int,int,int,int>;

  int maxf,f1,f2,sumf, maxb,b1,b2,sumb;
  int maxF,F1,F2,sumF, maxB,B1,B2,sumB;

  auto f = [&](const T &x, const T &y){
	     tie(maxf,f1,f2,sumf, maxb,b1,b2,sumb) = x;
	     tie(maxF,F1,F2,sumF, maxB,B1,B2,sumB) = y;

	     return make_tuple(
			       max({f1,f2,F1,F2,maxf,maxF,sumf,sumF,sumf+sumF,f1+F2}),
			       max(F1,sumF+f1),
			       max(f2,sumf+F2),
			       sumf+sumF,
			       max({b1,b2,B1,B2,maxb,maxB,sumb,sumB,sumb+sumB,b1+B2}),
			       max(B1,sumB+b1),
			       max(b2,sumb+B2),
			       sumb+sumB
			       );
	   };
  DynamicLazySegmentTree<T> dst(1000000100, make_tuple(0,0,0,0,0,0,0,0), f);

  int ans = 0;
  int a;
  int c,d;
  
  REP(i,Q){
    scanf("%d", &a);
    
    if(a == 1){
      scanf("%d %d", &c, &d);
      c = c^ans;
      dst.update(max(0,c-K), min(1000000000,c+K)+1, make_tuple(max(0,d),max(0,d),max(0,d),d,0,0,0,0));
    }else if(a == 2){
      scanf("%d %d", &c, &d);
      c = c^ans;
      dst.update(max(0,c-K), min(1000000000,c+K)+1, make_tuple(0,0,0,0,max(0,d),max(0,d),max(0,d),d));
    }else{
      scanf("%d", &c);
      c = c^ans;
      T t = dst.query(c);

      tie(maxf,f1,f2,sumf, maxb,b1,b2,sumb) = t;
      ans = max({f1,f2,b1,b2,maxf,maxb,sumf,sumb,sumf+sumb,f2+b2});
      
      printf("%d\n", ans);
    }
  }
}
  
int main(){
  scanf("%d %d", &Q, &K);

  solve();

  return 0;
}
