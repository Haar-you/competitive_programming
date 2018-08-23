{-# LANGUAGE FlexibleContexts #-}

import Control.Monad
import Control.Monad.ST
import Control.Applicative
import Data.List
import Data.Array
import Data.Array.ST
import Data.Int
import Data.STRef
import Debug.Trace

inf = 10^18 :: Int64

type Node = Int
type Cost = Int64
type Edge = (Node, Node, Cost)

bellman_ford :: (Node,Node) -> [Edge] -> Node -> Node -> Cost
bellman_ford bound@(lower,upper) edges src dst = runST $ do
  arr <- newArray bound inf :: ST s (STUArray s Node Cost)
  negcycle <- newSTRef False :: ST s (STRef s Bool)

  writeArray arr src 0
  forM_ [1..(upper-lower+1)] $ \i -> do
    forM_ edges $ \(s,e,c) -> do
      x <- (+c) <$> readArray arr s
      y <- readArray arr e
      when (x < y) $ do
        writeArray arr e x
          
  forM_ [1..(upper-lower+1)] $ \i -> do
    forM_ edges $ \(s,e,c) -> do
      x <- (+c) <$> readArray arr s
      y <- readArray arr e
      when (x < y) $ do
        writeArray arr e x
        when (e == dst) $ do
          writeSTRef negcycle True

  readSTRef negcycle >>= \x -> do
    if x then
      return (-inf)
      else
      readArray arr dst


main :: IO ()
main = do
  return ()
