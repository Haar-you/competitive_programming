import Data.Int
import Data.Bits

solve :: Int64 -> Int64 -> Int -> Int64
solve a b i
  | i == 0 = (a`div`2 - b`div`2 + b`mod`2) `mod` 2
  | otherwise = shiftL (((if testBit a i then a-l else 0) + (if testBit b i then r-b-1 else 0)) `mod` 2) i
  where
    l = a .&. (complement $ (bit i) - 1)
    r = b .&. (complement $ (bit i) - 1) + bit i


main :: IO ()
main = do
  [a,b] <- map read . words <$> getLine :: IO [Int64]

  print $ sum $ map (solve a b) [0..64]
