
main :: IO ()
main = do
  s <- getLine
  putStrLn $ [head s]
