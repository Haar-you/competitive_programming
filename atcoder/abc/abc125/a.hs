
main :: IO ()
main = do
  [a,b,t] <- map read . words <$> getLine :: IO [Int]
  print $ (t`div`a) * b
