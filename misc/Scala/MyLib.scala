import scala.math._
import scala.collection.mutable._
import scala.collection.immutable._

object Main{
  def main(args: Array[String]): Unit = {
    val sc = new java.util.Scanner(System.in)
    val pw = new java.io.PrintWriter(System.out)



    pw.flush()
  }
}

object Algorithms{
  val inf = 1000000000

  def lowerBound(xs: Array[Int], x: Int): Int = {
    def aux(l: Int, r: Int): Int = {
      if(r-l <= 1){
        if(xs(l) < x) r else l
      }else{
        val m = (l+r)/2
        if(xs(m) < x) aux(m, r) else aux(l, m)
      }
    }
    aux(0, xs.length)
  }

  def LIS(xs: Array[Int]): Int = {
    val dp: Array[Int] = Array.fill(xs.length)(inf)
    for(x <- xs) dp(lowerBound(dp,x)) = x
    dp.takeWhile(_<inf).length
  }

  def levenshteinDistance(a: String, b: String): Int = {
    val dp = Array.fill(a.length+1,b.length+1)(0)
    for(i <- 0 to a.length){dp(i)(0) = i}
    for(i <- 0 to b.length){dp(0)(i) = i}

    for(i <- 1 to a.length) for(j <- 1 to b.length)
      dp(i)(j) = min(min(dp(i-1)(j)+1, dp(i)(j-1)+1), dp(i-1)(j-1)+(if (a(i-1)==b(j-1)) 0 else 1))
    dp(a.length)(b.length)
  }

  def LCS(a: String, b: String): Int = {
    val dp = Array.fill(a.length+1, b.length+1)(0)

    for(i <- 1 to a.length){
      for(j <- 1 to b.length){
        if(a(i-1) == b(j-1))
          dp(i)(j) = dp(i-1)(j-1)+1
        else
          dp(i)(j) = max(dp(i-1)(j), dp(i)(j-1))
      }
    }
    dp(a.length)(b.length)
  }
}

object Graph{
  type Cost = Int

  val inf: Cost = 200000000

  def dijkstra(graph: Array[ArrayBuffer[(Int,Cost)]], start: Int): Array[Cost] = {
    val cost: Array[Cost] = Array.fill(graph.length)(-1)
    val pqueue: PriorityQueue[(Cost,Int)] = PriorityQueue((0,start))(Ordering.by((_: (Cost,Int))._1).reverse)
    val check: Array[Boolean] = Array.fill(graph.length)(false)
    cost(start) = 0

    while(!pqueue.isEmpty){
      val (d,v) = pqueue.dequeue
      check(v) = true
      for((u,c) <- graph(v)){
        if(cost(u) < 0){cost(u) = d+c; pqueue.enqueue((cost(u),u))}
        else
          if(d+c < cost(u)){cost(u) = d+c; if(!check(u)) pqueue.enqueue((cost(u),u))}
      }
    }

    cost
  }

  def bellmanford(graph: Array[ArrayBuffer[(Int,Cost)]], src: Int): Option[Array[Cost]] = {
    val cost = Array.fill(graph.length)(inf)
    cost(src) = 0

    for(i <- 0 to graph.length-1)
      for(s <- 0 to graph.length-1)
        for((t,d) <- graph(s)){
          if(cost(s) < inf && cost(t) < inf && cost(s)+d < cost(t) && i == graph.length-1) return None
          if(cost(s) >= inf && cost(t) >= inf) cost(t) = inf else cost(t) = min(cost(t), cost(s)+d)
        }

    Some(cost)
  }

  def warshallfloyd(graph: Array[ArrayBuffer[(Int,Cost)]]): Option[Array[Array[Cost]]] = {
    val n = graph.length
    val cost = Array.fill(n,n)(inf)
    for(i <- 0 to n-1) cost(i)(i) = 0
    for(i <- 0 to n-1) for((j,d) <- graph(i)) cost(i)(j) = d
    for(k <- 0 to n-1) for(i <- 0 to n-1) for(j <- 0 to n-1)
      if(cost(i)(k) < inf && cost(k)(j) < inf) cost(i)(j) = min(cost(i)(j), cost(i)(k)+cost(k)(j))
    for(i <- 0 to n-1) if(cost(i)(i) < 0) return None //detected negative cycle
    Some(cost)
  }

  def kruskal(n: Int, edges: Array[(Int,Int,Int)]): ArrayBuffer[(Int,Int,Int)] = {
    val sorted = edges.sortBy(_._3)
    val uf = new UnionFind(n)
    val result: ArrayBuffer[(Int,Int,Int)] = new ArrayBuffer
    for((s,t,d) <- sorted) if(!uf.same(s,t)){uf.merge(s,t); result.append((s,t,d))}
    result
  }

  def getArticulationPoints(graph: Array[ArrayBuffer[Int]]): Array[Int] = {
    val n = graph.length
    val check: Array[Int] = Array.fill(n)(-1)
    val low: Array[Int] = Array.fill(n)(-1)
    val aps: ArrayBuffer[Int] = new ArrayBuffer
    var i = 0

    def dfs(cur: Int, par: Int): Unit = {
      check(cur) = i
      var temp = i
      val children: ArrayBuffer[Int] = new ArrayBuffer
      i += 1
      for(next <- graph(cur)){
        if (next != par){
          if(check(next) == -1){
            dfs(next, cur)
            temp = min(temp, low(next))
            children.append(next)
          }else{
            temp = min(temp, check(next))
          }
        }
      }
      low(cur) = temp
      if((cur != 0 || children.length >= 2) && children.exists(x => low(x) >= check(cur))) aps.append(cur)
    }
    dfs(0, -1)
    aps.toArray
  }

  def getBridges(graph: Array[ArrayBuffer[Int]]): Array[(Int,Int)] = {
    val n = graph.length
    val check: Array[Int] = Array.fill(n)(-1)
    val low: Array[Int] = Array.fill(n)(-1)
    val brs: ArrayBuffer[(Int,Int)] = new ArrayBuffer
    var i = 0

    def dfs(cur: Int, par: Int): Unit = {
      check(cur) = i
      var temp = i
      i += 1
      for(next <- graph(cur)){
        if (next != par){
          if(check(next) == -1){
            dfs(next, cur)
            temp = min(temp, low(next))
            if(low(next) > check(cur)) brs.append(if(cur < next) (cur, next) else (next, cur))
          }else{
            temp = min(temp, check(next))
          }
        }
      }
      low(cur) = temp
    }
    dfs(0, -1)
    brs.toArray
  }

  def stronglyConnectedComponents(graph: Array[ArrayBuffer[Int]]): Array[Int] = {
    val n = graph.length
    val visit: Array[Boolean] = Array.fill(n)(false)
    val check: ArrayBuffer[Int] = new ArrayBuffer(n)

    def dfs(cur: Int){
      visit(cur) = true
      for(next <- graph(cur)) if(!visit(next)) dfs(next)
      check.append(cur)
    }
    for(i <- 0 to n-1) if(!visit(i)) dfs(i)

    val rgraph: Array[ArrayBuffer[Int]] = Array.fill(n)(new ArrayBuffer)
    for(s <- 0 to n-1) for(t <- graph(s)) rgraph(t).append(s)

    val result: Array[Int] = Array.fill(n)(-1)

    def rdfs(cur: Int, i: Int){
      result(cur) = i
      for(next <- rgraph(cur)) if(result(next) == -1) rdfs(next, i)
    }

    var index = 0
    for(c <- check.reverse) if(result(c) == -1){rdfs(c, index); index += 1}
    
    result
  }

  def hasCycle(graph: Array[ArrayBuffer[Int]]): Boolean = {
    val visit: Array[Int] = Array.fill(graph.length)(-1)
    def dfs(cur: Int): Boolean = {
      visit(cur) = 0
      val b = graph(cur).forall(next => {
        visit(next) match{
          case 0 => false
          case -1 => dfs(next)
          case 1 => true
        }
      })
      visit(cur) = 1
      b
    }

    for(i <- 0 to graph.length-1) if(visit(i) == -1) if(!dfs(i)) return true
    false
  }

  def treeDiameter(tree: Array[ArrayBuffer[(Int, Int)]]): Int = {
    val visit: Array[Boolean] = Array.fill(tree.length)(false)
    def dfs(cur: Int, d: Int): (Int,Int) = {
      visit(cur) = true
      val res = tree(cur).filter{case (t,_) => !visit(t)}.map{case (t,c) => dfs(t,d+c)}
      if(res.isEmpty) (d,cur) else res.max
    }
    val (a,x) = dfs(0,0)
    for(i <- 0 to tree.length-1) visit(i) = false
    dfs(x,0)._1
  }
}
 
class BIT(val n: Int){
  private var tree: Array[Int] = Array.fill(n+1)(0) //1-index (1..n)
  def init(): Unit = {tree = Array.fill(n+1)(0)}
  def update(x: Int, a: Int): Unit = {
    var i: Int = x
    while (i <= n){tree(i) = tree(i) + a; i += (i &  (-i))}
  }
  def get(x: Int): Int = {
    var i: Int = x
    var a: Int = 0
    while (i > 0){a += tree(i); i -= (i & (-i))}
    a
  }
  def lower_bound(i: Int): Int = {
    var w = i
    var k: Int = 1
    var x: Int = 0
    while (k*2 <= n) k *= 2
    while (k > 0){
      if (x+k <= n && tree(x+k) < w) {w -= tree(x+k); x += k}
      k /= 2
    }
    x+1
  }
}

class UnionFind(val n: Int){
  private val parent: Array[Int] = (0 to n-1).toArray
  private val depth: Array[Int] = Array.fill(n)(1)
  private val size: Array[Int] = Array.fill(n)(1)

  def getRoot(x: Int): Int = {
    if (parent(x) == x) x
    else {val p = getRoot(parent(x)); parent(x) = p; p}
  }
  def same(x: Int, y: Int): Boolean = getRoot(x) == getRoot(y)
  def merge(x: Int, y: Int): Unit = {
    val rtx = getRoot(x)
    val rty = getRoot(y)

    if (rtx != rty) {
      if (depth(rtx) < depth(rty)) {parent(rtx) = rty; size(rty) += size(rtx)}
      else{parent(rty) = rtx; size(rtx) += size(rty); if (depth(rtx) == depth(rty)) depth(rtx) += 1}
    }
  }
  def getSize(x: Int): Int = size(getRoot(x))
}

class WeightedUnionFind(val n: Int){
  private val parent: Array[Int] = (0 to n-1).toArray
  private val depth: Array[Int] = Array.fill(n)(1)
  private val size: Array[Int] = Array.fill(n)(1)
  private val weight: Array[Int] = Array.fill(n)(0)

  def getRoot(x: Int): Int = {
    if(parent(x) == x)x
    else{val p = getRoot(parent(x)); weight(x) += weight(parent(x)); parent(x) = p; p}
  }
  def getWeight(x: Int): Int = {getRoot(x); weight(x)}
  def same(x: Int, y: Int): Boolean = getRoot(x) == getRoot(y)
  def diff(x: Int, y: Int): Option[Int] = {if(same(x, y)) Some (getWeight(x) - getWeight(y)) else None}
  def merge(x: Int, y: Int, w: Int): Unit = {
    val rtx = getRoot(x)
    val rty = getRoot(y)

    if(rtx != rty){
      if(depth(rtx) < depth(rty)){parent(rtx) = rty; size(rty) += size(rtx); weight(rtx) = w-weight(x)+weight(y)}
      else{
        parent(rty) = rtx; size(rtx) += size(rty); weight(rty) = -w+weight(x)-weight(y)
        if(depth(rtx) == depth(rty)) depth(rtx) += 1
      }
    }
  }
  def getSize(x: Int): Int = size(getRoot(x))
}

class LCA(graph: Array[ArrayBuffer[Int]]){
  private val n = graph.length
  private val log2n = ceil(log(n)/log(2)).toInt + 1
  private val parent: Array[Array[Int]] = Array.fill(n)(Array.fill(log2n)(0))
  private val depth: Array[Int] = Array.fill(n)(0)
  private def dfs(cur: Int, par: Int, dp: Int){
    parent(cur)(0) = par
    depth(cur) = dp
    for(next <- graph(cur)) if(next != par) dfs(next, cur, dp+1)
  }
  private def aux{
    dfs(0, -1, 0)
    for(k <- 0 until log2n-1) for(v <- 0 to n-1) parent(v)(k+1) = if(parent(v)(k) < 0) -1 else parent(parent(v)(k))(k)
  }
  aux
  def query(a: Int, b: Int): Int = {
    var x = if (depth(a) < depth(b)) a else b
    var y = if (depth(a) < depth(b)) b else a
    for(k <- 0 until log2n) if(((depth(y) - depth(x)) >> k & 1) == 1) y = parent(y)(k)
    if(x == y) return x
    for(k <- (0 until log2n).reverse)
      if(parent(x)(k) != parent(y)(k)){
        x = parent(x)(k)
        y = parent(y)(k)
      }
    parent(x)(0)
  }
}

class SegmentTree(n: Int, e: Int, f: ((Int, Int) => Int)){
  private val size: Int = (1 << (ceil(log(n)/log(2)).toInt+1)) - 1
  private val array: Array[Int] = Array.fill(size)(e)
  def update(i: Int, g: Int => Int){
    val j = i+(size+1)/2-1
    def aux(k: Int){
      if(k >= 0){
        array(k/2) = f(array((k/2)*2+1), array((k/2)*2+2))
        aux(k/2-1)
      }
    }
    array(j) = g(array(j))
    aux(j-1)
  }
  def query(x: Int, y: Int): Int = {
    def aux(i: Int, l: Int, r: Int): Int = {
      if(r <= x || y <= l)
        e
      else if(x <= l && r <= y)
        array(i)
      else
        f(aux(i*2+1,l,(l+r)/2), aux(i*2+2,(l+r)/2,r))
    }
    aux(0,0,(size+1)/2)
  }
}

class SegmentTreeLazy(n: Int, e: Int, f: ((Int, Int) => Int)){
  private val size: Int = (1 << (ceil(log(n)/log(2)).toInt+1)) - 1
  private val array: Array[Int] = Array.fill(size)(e)
  private def propagate(i: Int){
    if(i < size/2){array(i*2+1) = f(array(i), array(i*2+1)); array(i*2+2) = f(array(i), array(i*2+2)); array(i) = e}
  }
  def update(s: Int, t: Int, g: Int => Int){
    def aux(i: Int, l: Int, r: Int){
      if(r <= s || t <= l) return
      else if(s <= l && r <= t) array(i) = g(array(i))
      else{propagate(i); aux(i*2+1,l,(l+r)/2); aux(i*2+2,(l+r)/2,r)}
    }
    aux(0,0,size/2+1)
  }
  def query(x: Int): Int = {
    def aux(i: Int){if(i>0) aux((i-1)/2); propagate(i)}
    val j = x+size/2
    aux((j-1)/2)
    array(j)
  }
}

class SegmentTreeComplicated[A: ClassTag]
  (n: Int, e: A, e1: A, f1: (A, A) => A, e2: A, f2: (A, A) => A, h: (A,Int) => A)(implicit num: Numeric[A]){
  private val size: Int = (1 << (ceil(log(n)/log(2)).toInt+1)) - 1
  private val tree: Array[A] = Array.fill(size)(e)
  private val tlazy: Array[A] = Array.fill(size)(e2)
  private def propagate(i: Int, l: Int){
    if(i < size/2){tlazy(i*2+1) = f2(tlazy(i), tlazy(i*2+1)); tlazy(i*2+2) = f2(tlazy(i), tlazy(i*2+2))}
    tree(i) = f2(h(tlazy(i), l), tree(i))
    tlazy(i) = e2
  }
  def update(s: Int, t: Int, g: A => A){
    def aux(i: Int, l: Int, r: Int): A = {
      propagate(i, r-l)
      if(r <= s || t <= l) tree(i)
      else if(s <= l && r <= t){tlazy(i) = g(tlazy(i)); propagate(i, r-l); tree(i)}
      else{tree(i) = f1(aux(i*2+1,l,(l+r)/2), aux(i*2+2,(l+r)/2,r)); tree(i)}
    }
    aux(0,0,size/2+1)
  }
  def query(x: Int, y: Int): A = {
    def aux(i: Int, l: Int, r: Int): A = {
      propagate(i, r-l)
      if(r <= x || y <= l) e1
      else if(x <= l && r <= y) tree(i)
      else f1(aux(i*2+1,l,(l+r)/2), aux(i*2+2,(l+r)/2,r))
    }
    aux(0,0,size/2+1)
  }
}
