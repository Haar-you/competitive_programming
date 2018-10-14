main = do
  n <- readLn :: IO Int
  print $ 100 - (100`div`n)
