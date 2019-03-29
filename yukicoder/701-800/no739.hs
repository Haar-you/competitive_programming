main = do
  s <- getLine
  let (a,b) = splitAt ((length s)`div`2) s

  putStrLn $ if a == b then "YES" else "NO"
