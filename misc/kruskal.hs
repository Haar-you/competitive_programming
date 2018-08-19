{-# LANGUAGE FlexibleContexts #-}

import Data.Array.ST
import Data.Array
import Data.List
import Data.Ord
import qualified Data.ByteString.Char8 as BS
import Data.Maybe
import Control.Monad
import Control.Monad.ST
import Control.Monad.State
import Control.Applicative

type UnionFindST s = STArray s Int (Int,Int)

newUFST :: Int -> ST s (UnionFindST s)
newUFST n = newListArray (1,n) (zip [1..n] (repeat 1))

findUFST :: Int -> UnionFindST s -> ST s Int
findUFST x uf = do
  (parent,size) <- readArray uf x
  if parent == x then
    return x
    else do
    next <- findUFST parent uf
    writeArray uf x (next,size)
    return next

sameUFST :: Int -> Int -> UnionFindST s -> ST s Bool
sameUFST x y uf = do
  xx <- findUFST x uf
  yy <- findUFST y uf
  return $ xx == yy

uniteUFST :: Int -> Int -> UnionFindST s -> ST s ()
uniteUFST x y uf = do
  xx <- findUFST x uf
  yy <- findUFST y uf
  (_,xs) <- readArray uf xx
  (_,ys) <- readArray uf yy

  if xx == yy then
    return ()
    else if xs < ys then do
    writeArray uf xx (yy,0)
    else if xs > ys then do
    writeArray uf yy (xx,0)
    else do
    writeArray uf yy (xx,0)
    writeArray uf xx (xx,xs+1)


type Node = Int
type Cost = Int
type Edge = (Node, Node, Cost)

kruskal :: [Node] -> [Edge] -> [Edge]
kruskal nodes edges = runST $ do
  let sorted = sortBy (\(_,_,c1) (_,_,c2) -> compare c1 c2) edges
  uf <- newUFST (length nodes)
  execStateT (kruskal' uf sorted) []
  where
    kruskal' _ [] = return ()
    kruskal' uf (e@(i,j,c):rest) = do
      isSame <- lift $ sameUFST i j uf
      unless isSame $ do
        lift $ uniteUFST i j uf
        modify (e:)
      kruskal' uf rest

main :: IO ()
main = do
  return ()
