import Data.List

main :: IO ()
main = do
  n <- readLn :: IO Int
  v <- map read . words <$> getLine :: IO [Int]
  c <- map read . words <$> getLine :: IO [Int]

  print $ sum . takeWhile (>0) . reverse . sort $ zipWith (-) v c
