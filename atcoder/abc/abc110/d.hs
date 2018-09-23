import Control.Applicative
import Data.List
import Data.Int

primes = takeWhile (<=(truncate . sqrt . fromIntegral $ 10^9)) $ aux [2..]
  where aux (x:xs) = x : aux [y | y<-xs, y`mod`x/=0]

factorize n = aux n primes
  where
    aux n [] = if n == 1 then [] else [n]
    aux n (p:ps)
      | n `mod` p == 0 = p : aux (n`div`p) (p:ps)
      | otherwise = aux n ps

{-- nCk mod p (pは素数)--}
combinationModP :: Integral a => a -> a -> a -> a
combinationModP n k p
  | n < k || n < 0 || k < 0 = 0
  | n == 0 || k == 0 = 1
  | otherwise = (n * (powerMod k (p-2) p) * combinationModP (n-1) (k-1) p) `mod` p


{-- n^p mod m --}
powerMod :: Integral a => a -> a -> a -> a
powerMod n 0 m = 1
powerMod n 1 m = n `mod` m
powerMod n p m = (k * k * (if mod p 2 == 0 then 1 else n)) `mod` m
  where
    k = powerMod n (div p 2) m

main :: IO ()
main = do
  [n,m] <- map read . words <$> getLine :: IO [Integer]

  let
    fs = map (fromIntegral . length) . group . factorize $ m
    p = 10^9+7

  print $ foldl (\a b -> (a*b) `mod` p) 1 [combinationModP (n+a-1) a p | a<-fs]
