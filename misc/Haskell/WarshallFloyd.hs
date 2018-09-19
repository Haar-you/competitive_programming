{-# LANGUAGE FlexibleContexts #-}

import Control.Applicative
import Control.Monad.ST
import Control.Monad.State
import Control.Monad
import Data.Array.ST
import Data.List
import Data.Array

type Node = Int
type Cost = Int
type Edge = (Node, Cost)
type Graph = Array Node [Edge]

inf = div maxBound 2 :: Int

warshall_floyd :: Graph -> Array (Node,Node) Cost
warshall_floyd graph = runST $ do
  let (s,e) = bounds graph
  dp <- newArray ((s,s),(e,e)) inf :: ST s (STUArray s (Node,Node) Cost)

  forM_ [s..e] $ \i -> do
    writeArray dp (i,i) 0

  forM_ [s..e] $ \i -> do
    forM_ (graph ! i) $ \(j,c) -> do
      writeArray dp (i,j) c

  forM_ [s..e] $ \k -> do
    forM_ [s..e] $ \i -> do
      forM_ [s..e] $ \j -> do
        a <- readArray dp (i,j)
        b <- readArray dp (i,k)
        c <- readArray dp (k,j)
        writeArray dp (i,j) $ min a (b+c)

  freeze dp


main :: IO ()
main = do
  return ()
  
