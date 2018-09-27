{-# LANGUAGE MultiWayIf #-}

import Control.Applicative
import Data.Ratio
import Text.Printf

main = do
  [n,m,k] <- map read . words <$> getLine :: IO [Integer]

  let
    area = (n*m) % k
    d = denominator area
    
  if
    | d<=2 -> do
        let
          m' = m `div` (gcd m k)
          k' = k `div` (gcd m k)
          n' = n `div` (gcd n k')
        printf "YES\n"
        mapM_ (\(x,y) -> printf "%d %d\n" x y) $
          case d of
            1 -> if m' < m then [(0,0),(n',0),(0,2*m')] else [(0,0),(2*n',0),(0,m')]
            2 -> if m' < m then [(0,0),(n',0),(0,m')] else [(0,0),(n',0),(0,m')]
    | otherwise -> printf "NO\n"
