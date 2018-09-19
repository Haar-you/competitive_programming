{-# LANGUAGE FlexibleContexts #-}
     
import Control.Applicative
import Control.Monad
import Control.Monad.ST
import Data.List
import Data.Maybe
import Data.Array.ST
import Data.Array

inf = maxBound :: Int

lis :: [Int] -> Int
lis xs = runST $ do
  let
    n = length xs
    b = array (1, n) (zip [1..] xs)
    
  dp <- newArray (1, n) inf :: (ST s (STArray s Int Int))
  
  let
    lowerBound l r x = do
      ll <- readArray dp l
      rr <- readArray dp r
      c <- readArray dp (div (l+r) 2)

      if r == l then
        return r
        else if r - l ==  1 then
        return $ if ll < x then r else l
        else if x < c then
        lowerBound l (div (l+r) 2) x
        else
        lowerBound (div (l+r) 2) r x

  forM_ xs $ \x -> do
    p <- lowerBound 1 n x
    writeArray dp p x
     
  length . takeWhile (<inf) <$> getElems dp

main :: IO ()
main = do
  return ()
