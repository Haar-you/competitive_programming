import Control.Monad
import Data.List

rmNeg _ [] = []
rmNeg 0 vs = vs
rmNeg k (v:vs) = if v>0 then (v:vs) else rmNeg (k-1) vs


main :: IO ()
main = do
  [n,k] <- map read . words <$> getLine :: IO [Int]
  vs <- map read . words <$> getLine :: IO [Int]

  let ans = maximum [sum . rmNeg (k-l-r) . sort $ take l vs ++ take r (reverse vs) | l<-[0..n], r<-[0..n], l+r<=n, l+r<=k]

  print $ max 0 ans
  
