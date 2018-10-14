import Data.List
import Control.Monad
import Data.Ord

main = do
  [n,x] <- map read . words <$> getLine :: IO [Int]
  dat <- reverse . sortBy (comparing (\[a,b] -> b)) <$> (replicateM n $ map read . words <$> getLine :: IO [[Int]])

  let ([a,b]:rest) = dat

  print $ (a+x)*b + (sum $ map (\[x,y] -> x*y) rest)
