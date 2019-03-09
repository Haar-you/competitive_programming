import Control.Monad
import Data.List

solve :: [(Integer,Integer)] -> Integer -> Integer -> Integer
solve [] _ _ = 0
solve ((a,b):xs) c m
  | c+b <= m = b*a + solve xs (c+b) m
  | c <= m && c+b > m = (m-c)*a + solve xs m m
  | otherwise = 0

main :: IO ()
main = do
  [n,m] <- map read . words <$> getLine :: IO [Int]
  dat <- sort <$> do
    replicateM n $ do
      [a,b] <- map read . words <$> getLine :: IO [Integer]
      return (a,b)

  print $ solve dat 0 (fromIntegral m)
