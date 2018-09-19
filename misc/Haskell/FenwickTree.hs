{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE MultiWayIf #-}

import Control.Monad
import Control.Monad.Primitive
import Control.Applicative
import Data.Bits
import qualified Data.ByteString.Char8 as BS
import qualified Data.Set as Set
import qualified Data.Vector as V
import qualified Data.Vector.Mutable as VM
import qualified Data.Vector.Unboxed as VU
import qualified Data.Vector.Unboxed.Mutable as VUM
import qualified Data.Vector.Generic as VG
import qualified Data.Vector.Generic.Mutable as VGM

type MFenwickTree v s a = (v s a, a, (a -> a -> a), Int) -- (フェニック木, 単位元, 二項演算)
type STFenwickTree s a = MFenwickTree VM.MVector s a
type IOFenwickTree a = STFenwickTree RealWorld a
type STUFenwickTree s a = MFenwickTree VUM.MVector s a
type IOUFenwickTree a = STUFenwickTree RealWorld a

newFenwickTree :: (Applicative m, PrimMonad m, VGM.MVector v a) => Int -> a -> (a -> a -> a) -> m (MFenwickTree v (PrimState m) a)
newFenwickTree n e f = (,e,f,n) <$> VGM.replicate (n+1) e

modifyFenwickTree :: (Applicative m, PrimMonad m, VGM.MVector v a) => MFenwickTree v (PrimState m) a -> Int -> (a -> a) -> m ()
modifyFenwickTree (tree,e,f,size) i g = do
  aux i
  where
    aux j = do
      when (j <= size) $ do
        VGM.write tree j =<< g <$> VGM.read tree j
        aux (j + (j .&. (-j)))

queryFenwickTree :: (Applicative m, PrimMonad m, VGM.MVector v a) => MFenwickTree v (PrimState m) a -> Int -> m a
queryFenwickTree (tree,e,f,size) i = do
  aux i
  where
    aux j
      | j <= 0 = return e
      | otherwise = f <$> VGM.read tree j <*> aux (j - (j .&. (-j)))

lowerBoundFenwickTree :: (Num a, Ord a, Eq a, Applicative m, PrimMonad m, VGM.MVector v a) => MFenwickTree v (PrimState m) a -> a -> m Int
lowerBoundFenwickTree (tree,e,f,size) x = do
  aux k 0 x
  where
    k = (2 ^ (floor $ logBase 2 (fromIntegral size)))
    aux i j w
      | i == 0 = return (j+1)
      | otherwise = do
          if i+j <= size then do
            a <- VGM.read tree (i+j)
            if a < w then aux (i `div` 2) (i+j) (w-a) else aux (i `div` 2) j w
            else
            aux (i `div` 2) j w


main :: IO ()
main = do
  return ()
