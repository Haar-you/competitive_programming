
main :: IO ()
main = do
  n <- readLn :: IO Int
  a <- map read . words <$> getLine :: IO [Int]

  let
    x = init $ scanl gcd 0 a
    y = tail $ reverse $ scanl gcd 0 (reverse a)

  print $ maximum $ zipWith gcd x y
