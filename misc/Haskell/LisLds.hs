{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE MultiWayIf #-}
     
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
  dp <- newArray (1, n) inf :: (ST s (STUArray s Int Int))
  forM_ xs $ \x -> do
    p <- lowerBound dp 1 n x
    writeArray dp p x
  length . takeWhile (<inf) <$> getElems dp
  where
    n = length xs
    lowerBound arr l r x = do
      ll <- readArray arr l
      rr <- readArray arr r
      c <- readArray arr (div (l+r) 2)
      if
        | r == l -> return r
        | r - l ==  1 -> return $ if ll < x then r else l
        | x < c -> lowerBound arr l (div (l+r) 2) x
        | x >= c -> lowerBound arr (div (l+r) 2) r x


lds :: [Int] -> Int
lds = lis . map negate


main :: IO ()
main = do
  return ()
