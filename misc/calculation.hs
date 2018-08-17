import Data.Ratio
import Data.List


{-- nの階乗 --}
factorial :: Integral a => a -> a
factorial n
  | n <= 1 = 1
  | otherwise = n * (factorial $ n-1)

{-- nの階乗 mod m--}
factorialMod :: Integral a => a -> a -> a
factorialMod n m
  | n <= 1 = 1
  | otherwise = (n * (factorialMod (n-1) m)) `mod` m

{-- nPk --}
permutation :: Integral a => a -> a -> a
permutation n k
  | n < k || n < 0 || k < 0 = 0
  | n == 0 || k == 0 = 1
  | otherwise = n * permutation (n-1) (k-1)

{-- nPk mod m --}
permutationMod :: Integral a => a -> a -> a -> a
permutationMod n k m
  | n < k || n < 0 || k < 0 = 0
  | n == 0 || k == 0 = 1
  | otherwise = (n * permutation (n-1) (k-1)) `mod` m

{-- nCk --}
combination :: Integral a => a -> a -> a
combination n k = numerator $ combination' n k
  where
    combination' :: Integral a => a -> a -> Ratio a
    combination' n k
      | n < k || n < 0 || k < 0 = 0
      | n == 0 || k == 0 = 1
      | otherwise = (n % k) * combination' (n-1) (k-1)

{-- nCk mod p (pは素数)--}
combinationModP :: Integral a => a -> a -> a -> a
combinationModP n k p
  | n < k || n < 0 || k < 0 = 0
  | n == 0 || k == 0 = 1
  | otherwise = (n * (powerMod k (p-2) p) * combinationModP (n-1) (k-1) p) `mod` p
  
{-- n^p --}
power :: Integral a => a -> a -> a
power n 0 = 1
power n 1 = n
power n p = k * k * (if mod p 2 == 0 then 1 else n)
  where
    k = power n (div p 2)

{-- n^p mod m --}
powerMod :: Integral a => a -> a -> a -> a
powerMod n 0 m = 1
powerMod n 1 m = n `mod` m
powerMod n p m = (k * k * (if mod p 2 == 0 then 1 else n)) `mod` m
  where
    k = powerMod n (div p 2) m


main :: IO ()
main = do
  print $ power 2 10
  print $ powerMod 2 40 (10^9+7)
  print $ (combination 84 23) `mod` (10^9+7)
  print $ combinationModP 84 23 (10^9+7)
  print $ (factorial 12) `mod` (10^9+7)
  print $ factorialMod 12 (10^9+7)
