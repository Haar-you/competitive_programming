import Control.Monad
import Control.Applicative
import Data.List

main = do
  t <- readLn :: IO Int
  replicateM_ t $ do
    [s,a,b,c] <- map read . words <$> getLine :: IO [Integer]
    let n = s `div` c
    print $ n + (n`div`a)*b
