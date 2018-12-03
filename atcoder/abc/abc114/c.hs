is753number :: Int -> Bool
is753number n = let s = show n in all (\x -> x `elem` s) "357" 

main :: IO ()
main = do
  n <- readLn :: IO Int
  let s = concat $ map (filter is753number) $ take 9 $ iterate (\xs -> concat [map (\y -> x*10+y) [3,5,7] | x<-xs]) [3,5,7]
  
  print $ length $ filter (<=n) s
