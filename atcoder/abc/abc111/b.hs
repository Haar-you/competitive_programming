main = do
  n <- readLn :: IO Int
  print $ head [i | i <- [n..999], i `elem` (map (*111) [1..9])]
