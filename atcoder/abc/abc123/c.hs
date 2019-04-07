import Control.Monad

solve _ t [] = t + 4
solve n t (x:xs) = solve n (max t $ (n+x-1) `div` x) xs

main :: IO ()
main = do
  n <- readLn :: IO Integer
  xs <- replicateM 5 $ readLn :: IO [Integer]

  print $ solve n 0 xs
