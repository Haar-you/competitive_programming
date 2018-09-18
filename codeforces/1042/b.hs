import Control.Applicative
import Data.List
import Data.Int

main = do
  n <- readLn :: IO Int
  dat <- map ((\[a,b] -> (read a, sort b)) . words) . lines <$> getContents :: IO [(Int64,String)]

  let
    inf = 10^9
    f str = minimum $ inf : (map fst . filter ((==str) . snd) $ dat)
    a = f "A"
    b = f "B"
    c = f "C"
    ab = f "AB"
    bc = f "BC"
    ac = f "AC"
    abc = f "ABC"

    ans = minimum [abc, a+b+c, ab+(minimum [c,bc,ac]), bc+(minimum [a,ab,ac]), ac+(minimum [b,ab,bc])]

  print $ if ans < inf then ans else -1
