import Control.Applicative
import Data.Ratio

main = do
  [a,b,x,y] <- map read . words <$> getLine :: IO [Integer]

  let
    x' = x `div` (gcd x y)
    y' = y `div` (gcd x y)
    solve low upp
      | low == upp = low
      | low + 1 == upp = if aux upp then upp else low
      | otherwise = if aux m then solve m upp else solve low m
      where
        m = (low+upp)`div`2
        aux k = x'*k <= a && y'*k <= b

  print $ solve 0 (10^18)
