import Control.Applicative
import Data.List

main :: IO ()
main = do
  [n,k] <- map read . words <$> getLine :: IO [Integer]

  print $ if odd k then
            (length $ filter ((==0) . (`mod`k)) [1..n]) ^ 3
          else
            (length $ filter ((==0) . (`mod`k)) [1..n]) ^ 3 + (length $ filter ((==(k`div`2)) . (`mod`k)) [1..n]) ^ 3
  
