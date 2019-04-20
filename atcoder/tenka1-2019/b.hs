main :: IO ()
main = do
  n <- readLn :: IO Int
  s <- getLine
  k <- readLn :: IO Int

  let c = s!!(k-1)

  putStrLn $ map (\x -> if x==c then x else '*') s
