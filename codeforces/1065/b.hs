import Control.Applicative
import Data.List
import Text.Printf

main = do
  [n,m] <- map read . words <$> getLine :: IO [Integer]
  let x = minimum [i | i<-[0..n], i*(i-1)`div`2 >= m]
  printf "%d %d\n" (max 0 (n-2*m)) (n-x)
