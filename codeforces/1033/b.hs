import Control.Monad
import Control.Applicative
import Data.List
import Data.Int
main = do
  n <- readLn :: IO Int
  replicateM_ n $ do
    [a,b] <- map read . words <$> getLine :: IO [Int64]
    putStrLn $ if a-b == 1 && isPrime (a+b)  then "YES" else "NO"

isPrime n = all (\x -> n`mod`x /= 0) [2..sq]
  where sq = ceiling $ sqrt $ fromIntegral n
