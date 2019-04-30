
primeFactor n = aux 2 n
  where
    aux i n
      | i*i > n = if n /= 1 then [n] else []
      | otherwise = if n `mod` i == 0 then i : aux i (n`div`i) else aux (i+1) n


main :: IO ()
main = do
  [n,k] <- map read . words <$> getLine :: IO [Int]

  let
    ps = primeFactor n
    x = product $ take (k-1) ps

  if length ps < k then
    print $ -1
    else if length ps == k then
    putStrLn $ unwords . map show $ ps
    else
    putStrLn $ unwords . map show $ take (k-1) ps ++ [n `div` x]
