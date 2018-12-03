import Data.List

factorize :: Int -> [Int]
factorize n = aux n 2
  where
    aux 1 _ = []
    aux n k
      | n `mod` k == 0 = k : aux (n`div`k) k
      | otherwise = aux n (k+1)


main :: IO ()
main = do
  n <- readLn :: IO Int

  let t = map (\xs -> (head xs, length xs)) $ group $ sort $ concat $ map factorize [1..n]

  let
    d2 = filter ((>=2) . snd) t
    d4 = filter ((>=4) . snd) t
    d14 = filter ((>=14) . snd) t
    d24 = filter ((>=24) . snd) t
    d74 = filter ((>=74) . snd) t
    
  print $ length d74 +
    (length $ concat $ map (\(x,_) -> filter ((/=x) . fst) d2) d24) +
    (length $ concat $ map (\(x,_) -> filter ((/=x) . fst) d4) d14) +
    (length $ concat $ map (\(x,y) -> filter ((\a -> a/=x && a/=y) . fst) d2) [(x,y) | (x,_)<-d4, (y,_)<-d4, x<y])

