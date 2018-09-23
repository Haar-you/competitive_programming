import Control.Applicative
import Data.List

main :: IO ()
main = do
  [n,x] <- map read . words <$> getLine :: IO [Int]
  as <- scanl1 (+) . sort . map read . words <$> getLine :: IO [Int]

  let a = length $ takeWhile (<=x) as

  print $
    if a == n && last as < x then
      a - 1
    else
      a
