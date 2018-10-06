import Control.Applicative
import Data.List

main :: IO ()
main = do
  [n,tmax] <- map read . words <$> getLine :: IO [Int]
  dat <- filter (\[c,t] -> t<=tmax) . map (map read . words) . lines <$> getContents :: IO [[Int]]

  if null dat then
    putStrLn "TLE"
    else
    print $ minimum $ map (\[c,_] -> c) dat
    
