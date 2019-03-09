main :: IO ()
main = do
  [h,w] <- map read . words <$> getLine :: IO [Int]
  [hh,ww] <- map read . words <$> getLine :: IO [Int]
  print $ (h-hh)*(w-ww)
