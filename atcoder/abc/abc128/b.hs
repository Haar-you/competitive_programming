import Control.Monad
import Data.Ord
import Data.List

main :: IO ()
main = do
  n <- readLn :: IO Int
  dat <- forM [1..n] $ \i -> do
    [s,p] <- words <$> getLine
    return (s,(read::String->Int) p,i)

  let sorted = sortBy (\ (s1,p1,_) (s2,p2,_) -> if compare s1 s2 == EQ then compare p2 p1 else compare s1 s2) dat
  let ans = map (\(_,_,i) -> i) sorted

  mapM_ print $ ans
  
