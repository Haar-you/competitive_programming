main = do
  n <- readLn :: IO Int
  dat <- map (map read . words) . lines <$> getContents :: IO [[Int]]

  let (ds,ans) = solve dat

  if ans == [] then
    print $ -1
    else do
    print $ length ds
    putStrLn $ unwords . map show $ ds
    mapM_ putStrLn ans
  

solve dat
  | all (\[x,y] -> odd (abs x + abs y)) dat = let ds = reverse $ map (2^) [0..30] in (ds, f ds)
  | all (\[x,y] -> even (abs x + abs y)) dat = let ds = reverse $ 1 : map (2^) [0..30] in (ds, f ds)
  | otherwise = ([], [])
  where f ds = map (\[x,y] -> aux (x,y) ds (0,0)) dat
    

aux _ [] p = []
aux t@(tx,ty) (d:ds) (x,y)
  | abs (tx-x) > abs (ty-y) = if tx > x then 'R' : aux t ds (x+d,y) else 'L' : aux t ds (x-d,y)
  | otherwise = if ty > y then 'U' : aux t ds (x,y+d) else 'D' : aux t ds (x,y-d)

