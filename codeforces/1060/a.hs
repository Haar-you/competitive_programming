import Control.Applicative

main = do
  n <- readLn :: IO Int
  xs <- getLine
  let count8 = length . filter (=='8') $ xs
  print $ min (n `div` 11) count8
