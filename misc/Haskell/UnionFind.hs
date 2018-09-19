{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE MultiWayIf #-}

import Data.Array.IO
import Data.Array.ST
import Control.Monad
import Control.Monad.ST
import Control.Applicative
import qualified Data.Vector.Unboxed.Mutable as VUM
import qualified Data.Vector.Unboxed as VU
import Data.Maybe

-- (親要素のIndex配列, 木の深さの配列, 木の要素数の配列)
type MUnionFind s = (VUM.MVector s Int, VUM.MVector s Int, VUM.MVector s Int)
type IOUnionFind = MUnionFind RealWorld
type STUnionFind s = MUnionFind s

newUnionFind :: (Applicative m, PrimMonad m) => Int -> m (MUnionFind (PrimState m))
newUnionFind n = do
  parentList <- VU.thaw $ VU.fromList [0..n-1]
  depthList <- VU.thaw $ VU.fromList (take n (repeat 1))
  sizeList <- VU.thaw $ VU.fromList (take n (repeat 1))
  return (parentList, depthList, sizeList)

findUnionFind :: (Applicative m, PrimMonad m) => MUnionFind (PrimState m) -> Int -> m Int
findUnionFind uf@(plist,dlist,slist) x = do
  parent <- VUM.unsafeRead plist x
  if parent == x then return x
    else findUnionFind uf parent >>= \next -> VUM.unsafeWrite plist x next >> return next

sameUnionFind :: (Applicative m, PrimMonad m) => MUnionFind (PrimState m) -> Int -> Int -> m Bool
sameUnionFind uf x y = (==) <$> findUnionFind uf x <*> findUnionFind uf y
  
uniteUnionFind :: (Applicative m, PrimMonad m) => MUnionFind (PrimState m) -> Int -> Int -> m ()
uniteUnionFind uf@(plist,dlist,slist) x y = do
  xx <- findUnionFind uf x
  yy <- findUnionFind uf y
  xdepth <- VUM.unsafeRead dlist xx
  xsize <- VUM.unsafeRead slist xx
  ydepth <- VUM.unsafeRead dlist yy
  ysize <- VUM.unsafeRead slist yy

  if xx == yy then return ()
    else if xdepth < ydepth then VUM.unsafeWrite plist xx yy >> VUM.unsafeWrite dlist yy ydepth >> VUM.unsafeWrite slist yy (ysize+xsize)
    else if xdepth > ydepth then VUM.unsafeWrite plist yy xx >> VUM.unsafeWrite dlist xx xdepth >> VUM.unsafeWrite slist xx (xsize+ysize)
    else VUM.unsafeWrite plist yy xx >> VUM.unsafeWrite dlist xx (xdepth+1) >> VUM.unsafeWrite slist xx (xsize+ysize)

sizeUnionFind :: (Applicative m, PrimMonad m) => MUnionFind (PrimState m) -> Int -> m Int
sizeUnionFind uf@(_,_,slist) x = VUM.unsafeRead slist =<< findUnionFind uf x

-- (親要素のIndex配列, 木の深さの配列, 木の要素数の配列, 親要素との重さ差分の配列)
type MWeightedUnionFind s = (VUM.MVector s Int, VUM.MVector s Int, VUM.MVector s Int, VUM.MVector s Int)
type IOWeightedUnionFind = MWeightedUnionFind RealWorld
type STWeightedUnionFind s = MWeightedUnionFind s

newWeightedUnionFind :: (Applicative m, PrimMonad m) => Int -> m (MWeightedUnionFind (PrimState m))
newWeightedUnionFind n = do
  parentList <- VU.thaw $ VU.fromList [0..n-1]
  depthList <- VU.thaw $ VU.fromList (take n (repeat 1))
  sizeList <- VU.thaw $ VU.fromList (take n (repeat 1))
  weightList <- VU.thaw $ VU.fromList (take n (repeat 0))
  return (parentList, depthList, sizeList, weightList)

findWeightedUnionFind :: (Applicative m, PrimMonad m) => MWeightedUnionFind (PrimState m) -> Int -> m Int
findWeightedUnionFind uf@(plist,dlist,slist,wlist) x = do
  parent <- VUM.unsafeRead plist x
  if parent == x then return x
    else do
    next <- findWeightedUnionFind uf parent
    VUM.unsafeWrite wlist x =<< (+) <$> VUM.unsafeRead wlist x <*> VUM.unsafeRead wlist parent
    VUM.unsafeWrite plist x next >> return next

weighWeightedUnionFind :: (Applicative m, PrimMonad m) => MWeightedUnionFind (PrimState m) -> Int -> m Int
weighWeightedUnionFind uf@(_,_,_,wlist) x = findWeightedUnionFind uf x >> VUM.unsafeRead wlist x

diffWeightedUnionFind :: (Applicative m, PrimMonad m) => MWeightedUnionFind (PrimState m) -> Int -> Int -> m (Maybe Int)
diffWeightedUnionFind uf x y = do
  same <- sameWeightedUnionFind uf x y
  if same then do
    a <- (-) <$> weighWeightedUnionFind uf x <*> weighWeightedUnionFind uf y
    return $ Just a
    else
    return Nothing

sameWeightedUnionFind :: (Applicative m, PrimMonad m) => MWeightedUnionFind (PrimState m) -> Int -> Int -> m Bool
sameWeightedUnionFind uf x y = (==) <$> findWeightedUnionFind uf x <*> findWeightedUnionFind uf y
  
uniteWeightedUnionFind :: (Applicative m, PrimMonad m) => MWeightedUnionFind (PrimState m) -> Int -> Int -> Int -> m ()
uniteWeightedUnionFind uf@(plist,dlist,slist,wlist) x y w = do
  xx <- findWeightedUnionFind uf x
  yy <- findWeightedUnionFind uf y
  xdepth <- VUM.unsafeRead dlist xx
  xsize <- VUM.unsafeRead slist xx
  ydepth <- VUM.unsafeRead dlist yy
  ysize <- VUM.unsafeRead slist yy
  xweight <- VUM.unsafeRead wlist x
  yweight <- VUM.unsafeRead wlist y

  if xx == yy then return ()
    else
    if
      | xdepth < ydepth -> do
          VUM.unsafeWrite plist xx yy >> VUM.unsafeWrite dlist yy ydepth >> VUM.unsafeWrite slist yy (ysize+xsize)
          VUM.unsafeWrite wlist xx (w-xweight+yweight)

      | xdepth > ydepth -> do
          VUM.unsafeWrite plist yy xx >> VUM.unsafeWrite dlist xx xdepth >> VUM.unsafeWrite slist xx (xsize+ysize)
          VUM.unsafeWrite wlist yy (-w+xweight-yweight)
          
      | xdepth == ydepth -> do
          VUM.unsafeWrite plist yy xx >> VUM.unsafeWrite dlist xx (xdepth+1) >> VUM.unsafeWrite slist xx (xsize+ysize)
          VUM.unsafeWrite wlist yy (-w+xweight-yweight)

sizeWeightedUnionFind :: (Applicative m, PrimMonad m) => MWeightedUnionFind (PrimState m) -> Int -> m Int
sizeWeightedUnionFind uf@(_,_,slist,_) x = VUM.unsafeRead slist =<< findWeightedUnionFind uf x


main :: IO ()
main = do
  return ()
