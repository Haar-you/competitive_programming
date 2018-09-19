{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE MultiWayIf #-}

import Control.Applicative
import Control.Monad
import Control.Monad.ST
import Control.Monad.Primitive
import qualified Data.Vector as V
import qualified Data.Vector.Mutable as VM
import qualified Data.Vector.Unboxed as VU
import qualified Data.Vector.Unboxed.Mutable as VUM
import qualified Data.Vector.Generic as VG
import qualified Data.Vector.Generic.Mutable as VGM
import qualified Data.ByteString.Char8 as BS
import Data.Maybe
import Data.Bits
import Debug.Trace

{--
メモ
Range Minimum Query -> INF min
Range Maximum Query -> -INF max
Range Sum Query -> 0 (+)

Range Update Query -> Nil (f(a,b) := if a == Nil then b else a) (Nilは適当な範囲外の値であればよい。)
Range Add Query -> 0 (+)

--}


{-- 点更新・範囲取得のセグメント木 --}
type MSegmentTree v s a = (v s a, a, (a -> a -> a)) -- (セグメント木, 単位元, 二項演算)
type STSegmentTree s a = MSegmentTree VM.MVector s a
type IOSegmentTree a = STSegmentTree RealWorld a
type STUSegmentTree s a = MSegmentTree VUM.MVector s a
type IOUSegmentTree a = STUSegmentTree RealWorld a

newSegmentTree :: (PrimMonad m, VGM.MVector v a) => Int -> a -> (a -> a -> a) -> m (MSegmentTree v (PrimState m) a)
newSegmentTree n e f = return . (,e,f) =<< (VGM.replicate m e)
  where m = 2 * (2 ^ (ceiling $ logBase 2 (fromIntegral n))) - 1

modifySegmentTree :: (PrimMonad m, VGM.MVector v a) => MSegmentTree v (PrimState m) a -> Int -> (a -> a) -> m ()
modifySegmentTree (tree,e,f) i g = do
  VGM.write tree j =<< return . g =<< VGM.read tree j
  aux ((j-1)`div`2)
  where
    n = (VGM.length tree + 1) `div` 2
    j = i + n - 1
    aux i = do
      when (i >= 0) $ VGM.read tree (i*2+1) >>= \a -> VGM.read tree (i*2+2) >>= \b -> VGM.write tree i (f a b) >> aux ((i-1)`div`2)
        
findSegmentTree :: (PrimMonad m, VGM.MVector v a) => MSegmentTree v (PrimState m) a -> Int -> Int -> m a
findSegmentTree (tree,e,f) x y = do
  aux 0 0 n
  where
    n = (VGM.length tree) `div` 2 + 1
    aux i l r
      | r <= x || y <= l = return e
      | x <= l && r <= y = VGM.read tree i
      | otherwise = aux (i*2+1) l ((l+r)`div`2) >>= \a -> aux (i*2+2) ((l+r)`div`2) r >>= \b -> return (f a b)


{-- 範囲更新・点取得のセグメント木--}
type MLazySegmentTree v s a = (v s a, a, (a -> a -> a)) -- (セグメント木, 単位元, 二項演算)
type STLazySegmentTree s a = MLazySegmentTree VM.MVector s a
type IOLazySegmentTree a = STLazySegmentTree RealWorld a
type STULazySegmentTree s a = MLazySegmentTree VUM.MVector s a
type IOULazySegmentTree a = STULazySegmentTree RealWorld a

newLazySegmentTree :: (PrimMonad m, VGM.MVector v a) => Int -> a -> (a -> a -> a) -> m (MLazySegmentTree v (PrimState m) a)
newLazySegmentTree n e f = return . (,e,f) =<< VGM.replicate m e
  where m = 2 * (2 ^ (ceiling $ logBase 2 (fromIntegral n))) - 1

modifyLazySegmentTree :: (PrimMonad m, VGM.MVector v a) => MLazySegmentTree v (PrimState m) a -> Int -> Int -> (a -> a) -> m ()
modifyLazySegmentTree (tree,e,f) x y g = do
  aux 0 0 n
  where
    n = (VGM.length tree) `div` 2 + 1
    aux i l r
      | r <= x || y <= l = return ()
      | x <= l && r <= y = VGM.read tree i >>= \a -> VGM.write tree i (g a)
      | otherwise = propag i >> aux (i*2+1) l ((l+r)`div`2) >> aux (i*2+2) ((l+r)`div`2) r
    propag i = do
      a <- VGM.read tree i
      when (i<n-1) $ do
        VGM.read tree (i*2+1) >>= \b -> VGM.write tree (i*2+1) (f a b)
        VGM.read tree (i*2+2) >>= \b -> VGM.write tree (i*2+2) (f a b)
        VGM.write tree i e

findLazySegmentTree :: (PrimMonad m, VGM.MVector v a) => MLazySegmentTree v (PrimState m) a -> Int -> m a
findLazySegmentTree (tree,e,f) i = do
  aux ((j-1)`div`2)
  VGM.read tree j
  where
    n = (VGM.length tree + 1) `div` 2
    j = i + n - 1
    aux x = do
      when (x >= 0) $ do
        aux ((x-1)`div`2)
        propag x

    propag i = do
      a <- VGM.read tree i
      when (i < n-1) $ do
        VGM.read tree (i*2+1) >>= \b -> VGM.write tree (i*2+1) (f a b)
        VGM.read tree (i*2+2) >>= \b -> VGM.write tree (i*2+2) (f a b)
        VGM.write tree i e


{-- 範囲更新・範囲取得のセグメント木 --}
type MRangeSegmentTree v s a = ((v s a, a, (a -> a -> a)), (v s a, a, (a -> a -> a)), Int, (a -> Int -> a))
-- 範囲取得用の(セグメント木,単位元,二項演算)、範囲更新用の(遅延セグメント木,単位元,二項演算)
type STRangeSegmentTree s a = MRangeSegmentTree VM.MVector s a
type IORangeSegmentTree a = STRangeSegmentTree RealWorld a
type STURangeSegmentTree s a = MRangeSegmentTree VUM.MVector s a
type IOURangeSegmentTree a = STURangeSegmentTree RealWorld a


newRangeSegmentTree :: (Applicative m, PrimMonad m, VGM.MVector v a) => Int -> a -> (a -> a -> a) -> a -> (a -> a -> a) -> (a -> Int -> a) -> m (MRangeSegmentTree v (PrimState m) a)
newRangeSegmentTree n e1 f1 e2 f2 h = do
  tree1 <- VGM.replicate m e1
  tree2 <- VGM.replicate m e2
  return ((tree1,e1,f1),(tree2,e2,f2), m, h)
  where m = 2 * (2 ^ (ceiling $ logBase 2 (fromIntegral n))) - 1

modifyRangeSegmentTree :: (Applicative m, Eq a, PrimMonad m, VGM.MVector v a) => MRangeSegmentTree v (PrimState m) a -> Int -> Int -> (a -> a) -> m ()
modifyRangeSegmentTree ((tree,e1,f1),(lazy,e2,f2),size,h) x y g = do
  void $ aux 0 0 n
  where
    n = size `div` 2 + 1
    aux i l r = do
      propag i (r-l)
      if
        | r <= x || y <= l -> VGM.read tree i
        | x <= l && r <= y -> g <$> VGM.read lazy i >>= (\a -> VGM.write lazy i a >> VGM.read tree i >>= \b ->  return ( (h a (r-l))))
        | otherwise -> f1 <$> aux (i*2+1) l ((l+r)`div`2) <*> aux (i*2+2) ((l+r)`div`2) r >>= (\a -> VGM.write tree i a >> return a)

    propag i len = do
      a <- VGM.read lazy i
      when (a /= e2) $ do
        when (i<n-1) $ do
          VGM.write lazy (i*2+1) =<< f2 a <$> VGM.read lazy (i*2+1)
          VGM.write lazy (i*2+2) =<< f2 a <$> VGM.read lazy (i*2+2)
        VGM.write tree i =<< (\a b -> (f2 (h b len) a)) <$> VGM.read tree i <*> VGM.read lazy i
        VGM.write lazy i e2

findRangeSegmentTree :: (Applicative m, Eq a, PrimMonad m, VGM.MVector v a) => MRangeSegmentTree v (PrimState m) a -> Int -> Int -> m a
findRangeSegmentTree ((tree1,e1,f1),(tree2,e2,f2),size,h) x y = do
  aux 0 0 n
  where
    n = size `div` 2 + 1
    aux i l r = do
      propag i (r-l)
      if
        | r <= x || y <= l -> return e1
        | x <= l && r <= y -> VGM.read tree1 i
        | otherwise -> f1 <$> aux (i*2+1) l ((l+r)`div`2) <*> aux (i*2+2) ((l+r)`div`2) r
        
    propag i len = do
      a <- VGM.read tree2 i
      when (a /= e2) $ do
        when (i<n-1) $ do
          VGM.write tree2 (i*2+1) =<< f2 a <$> VGM.read tree2 (i*2+1)
          VGM.write tree2 (i*2+2) =<< f2 a <$> VGM.read tree2 (i*2+2)
        VGM.write tree1 i =<< (\a b -> (f2 (h b len) a)) <$> VGM.read tree1 i <*> VGM.read tree2 i
        VGM.write tree2 i e2


main = do
  return ()
