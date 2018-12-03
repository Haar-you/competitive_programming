main :: IO ()
main = do
  n <- readLn :: IO Int
  putStrLn $ if n `elem` [3,5,7] then "YES" else "NO"
