main :: IO ()
main = do
  [a,p] <- map read . words <$> getLine :: IO [Int]
  let ans = (3*a+p) `div` 2
  print ans
