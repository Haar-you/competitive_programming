
f s 0 = s
f (x:xs) k = f (xs++[x]) (k-1)

main :: IO ()
main = do
  s <- getLine
  k <- readLn :: IO Int
  putStrLn $ f s k
  
