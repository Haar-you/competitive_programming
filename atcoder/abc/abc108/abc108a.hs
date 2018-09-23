main :: IO ()
main = do
  k <- readLn :: IO Int

  print $ (k`div`2) * (k`div`2 + k`mod`2)
  
