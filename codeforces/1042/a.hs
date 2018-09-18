import Control.Applicative
import Data.List
import Text.Printf
import Data.Ratio

main = do
  n <- readLn :: IO Int
  m <- readLn :: IO Int
  as <- sort . map read . lines <$> getContents :: IO [Int]

  let
    mx = maximum as
    s = sum (map (\a -> mx - a) as)
    x = if s >= m then mx else ceiling ((m-s) % n) + mx
    y = mx + m
  printf "%d %d\n" x y
