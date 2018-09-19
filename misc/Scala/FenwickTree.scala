class FenwichTree(val n: Int){
  private var tree: Array[Int] = Array.fill(n+1)(0) //1-index (1..n+1)
  def init(): Unit = {tree = Array.fill(n+1)(0)}
  def update(x: Int, a: Int): Unit = {
    var i: Int = x
    while (i <= n){
      tree(i) = tree(i) + a
      i += (i &  (-i))
    }
  }
  def get(x: Int): Int = {
    var i: Int = x
    var a: Int = 0
    while (i > 0){
      a += tree(i)
      i -= (i & (-i))
    }
    return a
  }
  def lower_bound(i: Int): Int = {
    var w = i
    var k: Int = 1
    var x: Int = 0
    while (k*2 <= n) k *= 2
    while (k > 0){
      if (x+k <= n && tree(x+k) < w) {
        w -= tree(x+k)
        x += k
      }
      k /= 2
    }
    x+1
  }
}
