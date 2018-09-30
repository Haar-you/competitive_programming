{-# LANGUAGE MultiWayIf #-}

import Data.List
import Data.Ord
import Data.Function
import Control.Arrow

main = do
  n <- readLn :: IO Int
  vs <- map read . words <$> getLine :: IO [Int]

  let
    f = map (length . head &&& map head) . groupBy ((==) `on` length) . reverse . sortBy (comparing length) . group . sort 
    xs = f $ [v | (i,v) <- zip [0..] vs, even i]
    ys = f $ [v | (i,v) <- zip [0..] vs, odd i]

    ((lx,xx):xs') = xs
    ((ly,yy):ys') = ys

  print $
    if
      | length xx == 1 && length yy == 1 ->
          if
            | head xx == head yy ->
              if
                | xs' == [] && ys' == [] -> min lx ly
                | xs' == [] && ys' /= [] -> n - (fst . head $ ys')
                | xs' /= [] && ys' == [] -> n - (fst . head $ xs')
                | otherwise -> n - max (lx + (fst . head $ ys')) (ly + (fst . head $ xs'))
            | otherwise -> n - lx - ly
      | otherwise -> n - lx - ly
