 =import Data.Ratio
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
  | otherwise = (n * permutationMod (n-1) (k-1) m) `mod` m

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
  | otherwise = ((n * (powerMod k (p-2) p)) `mod` p * combinationModP (n-1) (k-1) p) `mod` p
  
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
powerMod n p m = ((k * k) `mod` m * (if mod p 2 == 0 then 1 else n)) `mod` m
  where
    k = powerMod n (div p 2) m

{-- mod 逆数--}
modInv :: Integral a => a -> a -> a
modInv n p = powerMod n (p-2) p

{-- sieve of eratosthenes--}
primes = aux [2..]
  where aux (x:xs) = x : aux [y | y<-xs, y`mod`x/=0]


{-- Fibonacci数の一般項 (mod p)--}
fibonacci 0 _ = 0
fibonacci 1 _ = 1
fibonacci n p = let [x,_,_,_] = matpow [1,1,1,0] (n-1) in x `mod` p
  where
    matprod [a,b,c,d] [w,x,y,z] = map (`mod` p) [a*w+b*y,a*x+b*z,c*w+d*y,c*x+d*z]
    matpow a 0 = [1,0,0,1]
    matpow a 1 = a
    matpow a p = let t = matpow a (div p 2) in (if even p then id else (`matprod` a)) (t `matprod` t)

{-- 拡張Euclid互除法 --}
extendedEuclidean :: Integral a => a -> a -> (a, a, a)
extendedEuclidean a 0 = (a,1,0)
extendedEuclidean a b = (d,p,q-a`div`b*p)
  where (d,q,p) = extendedEuclidean b (a`mod`b)

{-- 中国剰余定理 --}
chineseRemainder :: Integral a => [(a,a)] -> Maybe (a,a)
chineseRemainder xs = foldl aux (Just (0,1)) xs
  where
    aux Nothing _ = Nothing
    aux (Just (b1,m1)) (b2,m2)
      | (b2-b1) `mod` d /= 0 = Nothing
      | otherwise = Just (b1+m1*(((b2-b1)*p`div`d)`mod`(m2`div`d)), m1*m2`div`d)
      where
        (d,p,q) = extendedEuclidean m1 m2


main :: IO ()
main = do
  print $ power 2 10
  print $ powerMod 2 40 (10^9+7)
  print $ (combination 84 23) `mod` (10^9+7)
  print $ combinationModP 84 23 (10^9+7)
  print $ (factorial 12) `mod` (10^9+7)
  print $ factorialMod 12 (10^9+7)
