{-# LANGUAGE FlexibleContexts #-}

import Data.Array.IO
import Data.Array.ST
import Control.Monad
import Control.Monad.ST

{-- IO union-find tree --}
type UnionFindIO = IOArray Int (Int,Int)
 
newUFIO :: Int -> IO UnionFindIO
newUFIO n = newListArray (1,n) (zip [1..n] (repeat 1))
 
findUFIO :: UnionFindIO -> Int -> IO Int
findUFIO uf x = do
  (parent,size) <- readArray uf x
  if parent == x then
    return x
    else do
    next <- findUFIO uf parent
    writeArray uf x (next,size)
    return next
 
sameUFIO :: UnionFindIO -> Int -> Int -> IO Bool
sameUFIO uf x y = do
  xx <- findUFIO uf x
  yy <- findUFIO uf y
  return $ xx == yy
 
uniteUFIO :: UnionFindIO -> Int -> Int -> IO ()
uniteUFIO uf x y = do
  xx <- findUFIO uf x
  yy <- findUFIO uf y
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

{-- ST union-find tree --}
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
