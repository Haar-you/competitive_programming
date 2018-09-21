{-# LANGUAGE Safe #-}

import Control.Applicative
import Control.Monad
import Data.List
import Text.Printf

main = do
  [l,r] <- map read . words <$> getLine :: IO [Integer]

  putStrLn "YES"
  forM_ (slice 2 [l..r]) $ \[i,j] -> do
    printf "%d %d\n" i j


slice _ [] = []
slice n xs = take n xs : slice n (drop n xs)
