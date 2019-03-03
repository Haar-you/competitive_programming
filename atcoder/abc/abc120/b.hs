main :: IO ()
main = do
  [a,b,k] <- map read . words <$> getLine :: IO [Int]

  print $ (reverse [x | x<-[1..100], a`mod`x==0, b`mod`x==0]) !! (k-1)
