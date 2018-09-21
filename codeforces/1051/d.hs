{-# LANGUAGE Safe #-}

import Control.Applicative
import Control.Monad
import Data.List
import Data.Array.IO.Safe
import Data.Int

main = do
  [n,k] <- map read . words <$> getLine :: IO [Int]
  let m = 998244353

  --      UL
  -- 1 => BB
  -- 2 => BW
  -- 3 => WB
  -- 4 => WW
  
  dp <- newArray ((0,0,1),(n,k+2,4)) 0 :: IO (IOUArray (Int,Int,Int) Int64)

  writeArray dp (1,1,1) 1
  writeArray dp (1,2,2) 1
  writeArray dp (1,2,3) 1
  writeArray dp (1,1,4) 1

  forM_ [2..n] $ \i -> do
    forM_ [1..k] $ \j -> do
      --BB
      writeArray dp (i,j,1) =<< (\a b c d -> (a+b+c+d)`mod`m) <$>
        readArray dp (i-1,j,1) <*> readArray dp (i-1,j,2) <*> readArray dp (i-1,j,3) <*> readArray dp (i-1,j-1,4)
      --BW
      when (j>1) $ do
        writeArray dp (i,j,2) =<< (\a b c d -> (a+b+c+d)`mod`m) <$>
          readArray dp (i-1,j-1,1) <*> readArray dp (i-1,j,2) <*> readArray dp (i-1,j-2,3) <*> readArray dp (i-1,j-1,4)
      --WB
      when (j>1) $ do
        writeArray dp (i,j,3) =<< (\a b c d -> (a+b+c+d)`mod`m) <$>
          readArray dp (i-1,j-1,1) <*> readArray dp (i-1,j-2,2) <*> readArray dp (i-1,j,3) <*> readArray dp (i-1,j-1,4)
      --WW
      writeArray dp (i,j,4) =<< (\a b c d -> (a+b+c+d)`mod`m) <$>
        readArray dp (i-1,j-1,1) <*> readArray dp (i-1,j,2) <*> readArray dp (i-1,j,3) <*> readArray dp (i-1,j,4)

  print =<< (\a b c d -> (a+b+c+d)`mod`m) <$> readArray dp (n,k,1) <*> readArray dp (n,k,2) <*> readArray dp (n,k,3) <*> readArray dp (n,k,4)
