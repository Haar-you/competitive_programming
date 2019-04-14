
main = do
  n <- readLn :: IO Int
  hs <- map read . words <$> getLine :: IO [Int]

  print $ sum [1 | i<-[0..n-1], all (<=hs!!i) (take i hs)]
