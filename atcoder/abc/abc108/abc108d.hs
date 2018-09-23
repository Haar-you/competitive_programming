import Control.Monad
import Control.Applicative
import Data.List
import Text.Printf

main :: IO ()
main = do
  l <- readLn :: IO Int

  let
    r = last $ takeWhile (\i -> 2^i <= l) [1..] :: Int
    es = (concat $  map (\i -> [(i,i+1,0), (i,i+1,2^(i-1))]) [1..r]) ++ aux r (reverse [1..r]) l

  printf "%d %d\n" (r+1) (length es)
  forM_ es $ \(u,v,w) -> do
    printf "%d %d %d\n" u v w

  where
    aux _ [] _ = []
    aux r (t:ts) l = if l-2^(t-1) >= 2^r then (t,r+1,l-2^(t-1)) : aux r ts (l-2^(t-1)) else aux r ts l 
