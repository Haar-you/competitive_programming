object Main{
  def main(args: Array[String]) = {
    val sc = new java.util.Scanner(System.in)
    val n = sc.nextInt
    val as = List.fill(n)(sc.nextInt)
    val s = as.sortBy(identity)

    val bit = new FenwichTree(n*2+2)

    def aux(x:Int): Boolean = {
      bit.init()
      val ys = as.map(a => if (a >= x) 1 else -1).scanLeft(0)(_+_).map(_+(n+1))
      var sum: Long = 0L
      ys.foreach({
        a => {
          sum += bit.get(a)
          bit.update(a,1)
        }
      })
      sum >= 1L*n*(n+1)/4
    }

    def solve(l:Int,r:Int): Int = {
      if (l == r) l
      else if (l+1 == r) {
        if (aux(s(r))) r
        else l
      }
      else {
        val m = (l+r)/2
        if (aux(s(m))) solve(m,r)
        else solve(l,m)
      }
    }
    println(s(solve(0,n-1)))
  }
}


class FenwichTree(val n: Int){
  private var tree: Array[Int] = Array.fill(n+1)(0) //1-index (1..n+1)
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
  def init(): Unit = {tree = Array.fill(n+1)(0)}
}
