import Control.Monad
import Control.Applicative
import Data.List

main = do
  t <- readLn :: IO Int
  replicateM_ t $ do
    [len,v,l,r] <- map read . words <$> getLine :: IO [Int]
    print $ len`div`v - r`div`v + (l-1)`div`v
