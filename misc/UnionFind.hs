{-# LANGUAGE FlexibleContexts #-}

import Data.Array.IO
import Data.Array.ST
import Control.Monad
import Control.Monad.ST
import qualified Data.Vector.Unboxed.Mutable as VUM

-- IO版は今後修正する
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
-- (親要素のIndex配列, 木の深さの配列, 木の要素数の配列)
type STUnionFind s = (VUM.MVector s Int, VUM.MVector s Int, VUM.MVector s Int)

newUF :: Int -> ST s (STUnionFind s)
newUF n = do
  parentList <- VU.thaw $ VU.fromList [0..n-1]
  depthList <- VU.thaw $ VU.fromList (take n (repeat 1))
  sizeList <- VU.thaw $ VU.fromList (take n (repeat 1))
  return (parentList, depthList, sizeList)

findUF :: STUnionFind s -> Int -> ST s Int
findUF uf@(plist,dlist,slist) x = do
  parent <- VUM.read plist x
  if parent == x then
    return x
    else do
    next <- findUF uf parent
    VUM.write plist x next
    return next

sameUF :: STUnionFind s -> Int -> Int -> ST s Bool
sameUF uf x y = (==) <$> findUF uf x <*> findUF uf y
  
uniteUF :: STUnionFind s -> Int -> Int -> ST s ()
uniteUF uf@(plist,dlist,slist) x y = do
  xx <- findUF uf x
  yy <- findUF uf y
  xdepth <- VUM.read dlist xx
  xsize <- VUM.read slist xx
  ydepth <- VUM.read dlist yy
  ysize <- VUM.read slist yy

  if xx == yy then
    return ()
    else if xdepth < ydepth then
    VUM.write plist xx yy >> VUM.write dlist yy ydepth >> VUM.write slist yy (ysize+xsize)
    else if xdepth > ydepth then
    VUM.write plist yy xx >> VUM.write dlist xx xdepth >> VUM.write slist xx (xsize+ysize)
    else
    VUM.write plist yy xx >> VUM.write dlist xx (xdepth+1) >> VUM.write slist xx (xsize+ysize)

sizeUF :: STUnionFind s -> Int -> ST s Int
sizeUF uf@(_,_,slist) x = VUM.read slist =<< findUF uf x
