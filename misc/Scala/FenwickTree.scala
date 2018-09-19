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
  def lower_bound(x: Int): Int = {


  }
}
