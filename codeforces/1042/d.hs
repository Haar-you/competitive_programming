{-# LANGUAGE Safe #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE TupleSections #-}
{-# LANGUAGE MultiWayIf #-}

import Control.Applicative
import Control.Monad
import Data.List
import Data.Array.IO.Safe
import Data.Int
import Data.Maybe
import Data.Bits
import qualified Data.ByteString.Char8 as BS
import qualified Data.Map as Map

readIntBS = fst . fromJust . BS.readInt

main = do
  [n,t] <- map read . words <$> getLine :: IO [Int64]
  as <- scanl (+) 0 .  map (fromIntegral . readIntBS) . BS.words <$> BS.getLine :: IO [Int64]

  let im = Map.fromList . (flip zip) [1..] . map head . group . sort $ as :: Map.Map Int64 Int

  bit <- newFenwickTree (fromIntegral $ n+1) :: IO IOFenwickTree

  ans <- do
    forM (zip [0..] as) $ \(x,a) -> do
      let f = Map.lookupGT (a-t) im
      res <- case f of
               Just (_,i) -> (x-) <$> queryFenwickTree bit (i-1)
               Nothing -> return 0
      modifyFenwickTree bit (im Map.! a)
      return res

  print $ sum (map fromIntegral ans)


type IOFenwickTree = (IOUArray Int Int, Int)

newFenwickTree :: Int -> IO IOFenwickTree
newFenwickTree n = (,n) <$> newListArray (1,n) (take n (repeat 0))

modifyFenwickTree :: IOFenwickTree -> Int -> IO ()
modifyFenwickTree (tree,size) i = do
  aux i
  where
    aux j = do
      when (j <= size) $ do
        writeArray tree j =<< (+1) <$> readArray tree j
        aux (j + (j .&. (-j)))

queryFenwickTree :: IOFenwickTree -> Int -> IO Int
queryFenwickTree (tree,size) i = do
  aux i
  where
    aux j
      | j <= 0 = return 0
      | otherwise = (+) <$> readArray tree j <*> aux (j - (j .&. (-j)))
