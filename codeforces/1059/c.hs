solve 1 = [1]
solve 2 = [1,2]
solve 3 = [1,1,3]
solve n = replicate ((n+1)`div`2) 1 ++ map (*2) (solve (n`div`2))

main = do
  n <- readLn :: IO Int
  putStrLn $ unwords . map show $ solve n
