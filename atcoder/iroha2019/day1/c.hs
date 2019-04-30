import Control.Monad

main :: IO ()
main = do
  n <- readLn :: IO Int
  mapM_ print $ [n-7..n]
