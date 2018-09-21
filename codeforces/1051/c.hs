{-# LANGUAGE Safe #-}
{-# LANGUAGE MultiWayIf #-}

import Control.Applicative
import Control.Monad
import Control.Monad.State
import Data.List
import Data.Ratio
import Data.Array.IO.Safe
import Data.Maybe
import qualified Data.IntMap as IM


main = do
  n <- readLn :: IO Int
  xs <- map read . words <$> getLine :: IO [Int]

  let
    ys = (map length . group . sort) xs
    cnt1 = length . filter (==1) $ ys
    cntGE3 = length . filter (>=3) $ ys
    im = IM.fromList . (map (\list -> (head list, length list)) . group . sort) $ xs

  if even cnt1 || (odd cnt1 && cntGE3 > 0) then do
    putStrLn "YES"
    let m = ceiling (cnt1 % 2)

    arr <- newArray (0,n-1) '.' :: IO (IOUArray Int Char)

    let (a,b) = splitAt m (IM.toList . IM.filter (==1) $ im)

    forM_ a $ \(x,_) -> writeArray arr (fromJust . elemIndex x $ xs) 'A'
    forM_ b $ \(x,_) -> writeArray arr (fromJust . elemIndex x $ xs) 'B'

    when (odd cnt1) $ do
      let p = head . IM.toList . IM.filter (>=3) $ im
      writeArray arr (fromJust . elemIndex (fst p) $ xs) 'B'

    forM_ [0..n-1] $ \i -> do
      x <- readArray arr i
      when (x == '.') $ writeArray arr i 'A'
    
    putStrLn =<< getElems arr

    else
    putStrLn "NO"
