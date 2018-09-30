import Data.List

main = do
  [h,w] <- map read . words <$> getLine :: IO [Int]
  c <- lines <$> getContents

  let
    Just i = elemIndex 's' $ last c
    ans = solve i (tail $ reverse c)

  putStrLn $ if ans == [] then "impossible" else head ans


solve :: Int -> [String] -> [String]
solve i [] = [""]
solve i (x:xs) = concat
  [
    if i > 0 && x!!(i-1) == '.' then map ('L':) $ solve (i-1) xs else [],
    if x!!i == '.' then map ('S':) $ solve i xs else [],
    if i < length x-1 && x!!(i+1) == '.' then map ('R':) $ solve (i+1) xs else []
  ]
  
