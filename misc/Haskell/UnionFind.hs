{-# LANGUAGE FlexibleContexts #-}

import Data.Array.IO
import Data.Array.ST
import Control.Monad
import Control.Monad.ST
import Control.Applicative
import qualified Data.Vector.Unboxed.Mutable as VUM
import qualified Data.Vector.Unboxed as VU

{-- IO union-find tree --}
type IOUnionFind = STUnionFind RealWorld
newIOUnionFind n = stToIO $ newSTUnionFind n
findIOUnionFind uf x = stToIO $ findSTUnionFind uf x
sameIOUnionFind uf x y = stToIO $ sameSTUnionFind uf x y 
uniteIOUnionFind uf x y = stToIO $ uniteSTUnionFind uf x y
sizeIOUnionFind uf x = stToIO $ sizeSTUnionFind uf x

{-- ST union-find tree --}
-- (親要素のIndex配列, 木の深さの配列, 木の要素数の配列)
type STUnionFind s = (VUM.MVector s Int, VUM.MVector s Int, VUM.MVector s Int)

newSTUnionFind :: Int -> ST s (STUnionFind s)
newSTUnionFind n = do
  parentList <- VU.thaw $ VU.fromList [0..n-1]
  depthList <- VU.thaw $ VU.fromList (take n (repeat 1))
  sizeList <- VU.thaw $ VU.fromList (take n (repeat 1))
  return (parentList, depthList, sizeList)

findSTUnionFind :: STUnionFind s -> Int -> ST s Int
findSTUnionFind uf@(plist,dlist,slist) x = do
  parent <- VUM.read plist x
  if parent == x then return x
    else findSTUnionFind uf parent >>= \next -> VUM.write plist x next >> return next

sameSTUnionFind :: STUnionFind s -> Int -> Int -> ST s Bool
sameSTUnionFind uf x y = (==) <$> findSTUnionFind uf x <*> findSTUnionFind uf y
  
uniteSTUnionFind :: STUnionFind s -> Int -> Int -> ST s ()
uniteSTUnionFind uf@(plist,dlist,slist) x y = do
  xx <- findSTUnionFind uf x
  yy <- findSTUnionFind uf y
  xdepth <- VUM.read dlist xx
  xsize <- VUM.read slist xx
  ydepth <- VUM.read dlist yy
  ysize <- VUM.read slist yy

  if xx == yy then return ()
    else if xdepth < ydepth then VUM.write plist xx yy >> VUM.write dlist yy ydepth >> VUM.write slist yy (ysize+xsize)
    else if xdepth > ydepth then VUM.write plist yy xx >> VUM.write dlist xx xdepth >> VUM.write slist xx (xsize+ysize)
    else VUM.write plist yy xx >> VUM.write dlist xx (xdepth+1) >> VUM.write slist xx (xsize+ysize)

sizeSTUnionFind :: STUnionFind s -> Int -> ST s Int
sizeSTUnionFind uf@(_,_,slist) x = VUM.read slist =<< findSTUnionFind uf x


main :: IO ()
main = do
  return ()
