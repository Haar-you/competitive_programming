import Control.Applicative
import Data.List
import qualified Data.ByteString.Char8 as BS

main :: IO ()
main = do
  [n,m] <- map read . words <$> getLine :: IO [Int]
  s <- BS.getLine
  t <- BS.getLine

  let
    l = lcm n m

    solve [] _ = True
    solve _ [] = True
    solve ((x,cx):xs) ((y,cy):ys)
      | x == y = if cx == cy then solve xs ys else False
      | x < y = solve xs ((y,cy):ys)
      | x > y = solve ((x,cx):xs) ys
      
    ans =  solve [(i*l`div`n, s `BS.index` i) | i<-[0..n-1]] [(i*l`div`m, t `BS.index` i) | i<-[0..m-1]]
  
  print $ if ans then l else -1
  
