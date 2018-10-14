import Control.Applicative
import Data.List

main = do
  [a,b,c] <- map read . words <$> getLine :: IO [Int]
  let t = [(i,j,k) | i<-[1..200], j<-[1..200], k<-[1..200], i+j>k, i+k>j, j+k>i]
  print $ minimum [(abs $ i-a) + (abs $ j-b) + (abs $ k-c) | (i,j,k) <- t]
  
