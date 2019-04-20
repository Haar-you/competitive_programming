main :: IO ()
main = do
  [a,b,c] <- map read . words <$> getLine :: IO [Int]
  putStrLn $ if c < min a b || c > max a b then "No" else "Yes"
