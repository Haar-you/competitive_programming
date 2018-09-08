{-# LANGUAGE MultiWayIf #-}

import Control.Monad
import Control.Monad.ST
import Control.Monad.State
import Control.Applicative
import Data.List
import Data.Array
import Data.Array.IO
import Data.Maybe
import qualified Data.ByteString.Char8 as BS
import qualified Data.Sequence as Sq
import Text.Printf
import Debug.Trace

modifyArray arr i f = readArray arr i >>= \x -> writeArray arr i (f x)

readIntBS = fst . fromJust . BS.readInt

main :: IO ()
main = do
  [h,w] <- map read . words <$> getLine :: IO [Int]
  field <- map (map readIntBS . BS.words) . BS.lines <$> BS.getContents :: IO [[Int]]

  check <- newArray ((1,1),(w,h)) False :: IO (IOUArray (Int,Int) Bool)
  f <- newArray ((1,1),(w,h)) 0 :: IO (IOUArray (Int,Int) Int)

  forM_ (zip [1..h] field) $ \(y,l) -> do
    forM_ (zip [1..w] l) $ \(x,c) -> do
      writeArray f (x,y) c
  
  let
    solve :: StateT (Sq.Seq (Int,Int)) IO [(Int,Int,Int,Int)]
    solve = do
      queue <- get
      let ((x,y) Sq.:< rest) = Sq.viewl queue
      put rest

      s <- lift $ readArray f (x,y)

      when (x<w) $ do
        (lift $ readArray check (x+1,y)) >>= \checked -> unless checked $ (modify (Sq.|> (x+1,y)))
        lift $ writeArray check (x+1,y) True
      when (y<h) $ do
        (lift $ readArray check (x,y+1)) >>= \checked -> unless checked $ (modify (Sq.|> (x,y+1)))
        lift $ writeArray check (x,y+1) True
      
      if
        | x == w && y == h -> return []
        | otherwise -> do
            if
              | odd s -> do
                  if
                    | x == w -> (lift $ modifyArray f (x,y) (+(-1)) >> modifyArray f (x,y+1) (+1)) >> ((y,x,y+1,x):) <$> solve
                    | y == h -> (lift $ modifyArray f (x,y) (+(-1)) >> modifyArray f (x+1,y) (+1)) >> ((y,x,y,x+1):) <$> solve
                    | otherwise -> (lift $ modifyArray f (x,y) (+(-1)) >> modifyArray f (x+1,y) (+1)) >> ((y,x,y,x+1):) <$> solve
              | otherwise -> solve

  ans <- evalStateT solve (Sq.singleton (1,1))

  print $ length ans
  forM_ ans $ \(a,b,c,d) -> do
    printf "%d %d %d %d\n" a b c d
    
