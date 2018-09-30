import Data.List

main = do
  n <- readLn :: IO Int
  s <- map read . words <$> getLine :: IO [Int]
  a <- map read . words <$> getLine :: IO [Int]

  print $ maximum $ zipWith (*) s a
