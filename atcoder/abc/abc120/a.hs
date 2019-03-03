main :: IO ()
main = do
  [a,b,c] <- map read . words <$> getLine :: IO [Int]
  
  print $ min c (b `div` a)
