
main :: IO ()
main = do
  n <- readLn :: IO Int
  a <- map read . words <$> getLine :: IO [Integer]

  let
    s = sum . map abs $ a
    neg = length . filter (<0) $ a

  print $ if even neg then s else s - 2 * minimum (map abs a)
