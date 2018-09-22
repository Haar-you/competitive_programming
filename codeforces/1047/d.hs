import Control.Monad
import Control.Monad.ST.Safe
import Control.Monad.State
import Control.Applicative
import Control.Arrow
import Data.List
import Data.Int

solve 1 x
  | x <= 3 = 0
  | x == 4 = 2
  | x == 5 = 4
  | x == 6 = 6
  | otherwise = (x`div`6)*6 + solve 1 (x`mod`6)
solve 2 x
  | x <= 2 = 0
  | x == 3 = 4
  | x == 4 = 8
  | x == 5 = 10
  | x == 6 = 12
  | x == 7 = 12
  | otherwise = x*2
solve y x = if odd (x*y) then x*y-1 else x*y

main = do
  [n,m] <- sort . map read . words <$> getLine :: IO [Int64]
  print $ solve n m
  
