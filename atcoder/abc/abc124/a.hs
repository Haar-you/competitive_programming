
main = do
  [a,b] <- map read . words <$> getLine :: IO [Int]
  print $ maximum [2*a-1, 2*b-1, a+b]
