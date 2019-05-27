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



main :: IO ()
main = do
  [n,q] <- map read . words <$> getLine :: IO [Int]
  stx <- replicateM n $ do
    map (fst . fromJust . BS.readInt) . BS.words <$> BS.getLine :: IO [Int]

  ds <- V.fromList <$> do
    replicateM q $ do
      fst . fromJust . BS.readInt <$> BS.getLine :: IO Int

  seg <- newLazySegmentTree q (maxBound :: Int) min :: IO (IOULazySegmentTree Int)

  forM_ stx $ \[s,t,x] -> do
    let i = lowerBound ds (s-x)
    let j = lowerBound ds (t-x)
    modifyLazySegmentTree seg i j (min x)

  ans <- forM [0..q-1] $ \i -> do
    x <- findLazySegmentTree seg i
    return $ if x == (maxBound::Int) then -1 else x

  mapM_ print $ ans

  
lowerBound :: Ord a => V.Vector a -> a -> Int
lowerBound vec x = aux (-1) (V.length vec)
  where
    aux lb ub
      | ub-lb > 1 =
        let mid = (lb+ub)`div`2 in
          if vec V.! mid >= x then
            aux lb mid
          else
            aux mid ub
      | otherwise = ub


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
