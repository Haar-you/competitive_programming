import Control.Monad

main :: IO ()
main = do
  [n,m,c] <- map read . words <$> getLine :: IO [Int]
  bs <- map read . words <$> getLine :: IO [Int]
  print . length . filter id =<< do
    replicateM n $ do
      as <- map read . words <$> getLine :: IO [Int]
      return $ (sum $ zipWith (*) as bs) + c > 0
