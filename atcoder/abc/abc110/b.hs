import Control.Applicative
import Data.List

main :: IO ()
main = do
  [n,m,x,y] <- map read . words <$> getLine :: IO [Int]
  xs <- map read . words <$> getLine :: IO [Int]
  ys <- map read . words <$> getLine :: IO [Int]

  let
    xx = sort (x:xs)
    yy = sort (y:ys)

  putStrLn $ if last xx < head yy then "No War" else "War"
  
  
