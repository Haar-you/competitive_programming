#include <bits/stdc++.h>
#define fst first
#define snd second
using namespace std;

// ConvexHullTrick
// 追加直線の傾き、クエリの値がともに単調性をもつバージョン
// MIN: true -> minクエリ, false -> maxクエリ
// クエリが単調減少のバージョンは未検証。

// verified at https://atcoder.jp/contests/dp/tasks/dp_z (Minクエリ)
// verified at https://codeforces.com/contest/939/problem/E (Maxクエリ)

template <typename T, bool MIN = true> class ConvexHullTrick{
  deque<pair<T,T>> lines;
  bool is_needless(const pair<T,T> &a, const pair<T,T> &b, const pair<T,T> &c){
    return (a.snd-b.snd)*(a.fst-c.fst) >= (a.snd-c.snd)*(a.fst-b.fst);
  }
  
  T apply(const pair<T,T> &f, const T &x){
    return f.fst*x + f.snd;
  }

  function<bool(T,T)> comp;

public:
  ConvexHullTrick(){
    if(MIN) comp = [](const T &a, const T &b){return a > b;};
    else comp = [](const T &a, const T &b){return a < b;};
  }
  
  void add(const T &a, const T &b){
    if(!lines.empty()){
      pair<T,T> l = lines.back();
      
      if(l.fst == a){
	if(!comp(l.snd,b)) return;
	lines.pop_back();
      }
    }
    while(lines.size()>=2 && is_needless(make_pair(a,b), lines.back(), *(lines.end()-2))){
      lines.pop_back();
    }
    lines.push_back(make_pair(a,b));
  }

  T query(const T &x){
    while(lines.size()>=2 && comp(apply(lines[0],x), apply(lines[1],x))){
      lines.pop_front();
    }
    return apply(lines[0],x);
  }
};




template <typename T> class LiChaoSegmentTree{
  using line = pair<T,T>;

  struct node{
    line l;
    node *left, *right;
    node(const line &l): l(l), left(nullptr), right(nullptr){}
  };

  vector<T> xs;
  int n;
  node *root;
  T e;
  function<bool(T,T)> cmp;
  function<T(T,T)> chm;

public:
  LiChaoSegmentTree(const vector<T> _xs, const bool min_mode, const T &e): xs(_xs), n(xs.size()), root(nullptr), e(e){
    if(min_mode){
      cmp = [](const T &a, const T &b){return a < b;};
      chm = [](const T &a, const T &b){return min(a,b);};
    }else{
      cmp = [](const T &a, const T &b){return a > b;};
      chm = [](const T &a, const T &b){return max(a,b);};
    }
  }

  T apply(const line &l, const T &x) const{
    return l.fst*x + l.snd;
  }

protected:
  node* add(node *t, const int left, const int right, line l){ // [l,r]
    if(!t) return new node(l);

    if(cmp(apply(t->l, xs[left]), apply(l, xs[left])) and cmp(apply(t->l, xs[right]), apply(l, xs[right]))){
      return t;
    }
    if(!cmp(apply(t->l, xs[left]), apply(l, xs[left])) and !cmp(apply(t->l, xs[right]), apply(l, xs[right]))){
      t->l = l;
      return t;
    }

    int mid = (left + right) / 2;

    if(!cmp(apply(t->l, xs[mid]), apply(l, xs[mid]))) swap(t->l, l);
    if(!cmp(apply(t->l, xs[left]), apply(l, xs[left]))){
      t->left = add(t->left, left, mid, l);
    }else{
      t->right = add(t->right, mid+1, right, l);
    }

    return t;
  }

public:
  void add_line(T a, T b){
    root = add(root, 0, n-1, make_pair(a,b));
  }

protected:
  T query(node *t, const int left, const int right, const int i) const{
    if(!t) return e;
    if(right == left) return apply(t->l, xs[i]);
    int mid = (left + right) / 2;
    if(i <= mid) return chm(apply(t->l, xs[i]), query(t->left, left, mid, i));
    else return chm(apply(t->l, xs[i]), query(t->right, mid+1, right, i));
  }
  
public:
  T query(const T &x) const{
    int t = lower_bound(ALL(xs), x) - xs.begin();
    return query(root, 0, n-1, t);
  }
};












int main(){
  
  return 0;
}

