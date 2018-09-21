{-# LANGUAGE Safe #-}
{-# LANGUAGE MultiWayIf #-}

import Control.Applicative
import Control.Monad
import Data.List
import Data.Maybe
import Data.Char

main = do
  n <- readLn :: IO Int

  replicateM n $ do
    s <- getLine

    let
      cntDig = length $ filter isDigit s
      cntUpp = length $ filter isUpper s
      cntLow = length $ filter isLower s
      cntSum = cntDig + cntUpp + cntLow

      replace i x xs = let (a,b) = splitAt i xs in a ++ (x : (tail b))

    if
      | cntDig > 0 && cntUpp > 0 && cntLow > 0 -> putStrLn s
      | cntSum == cntDig -> putStrLn $ 'a' : 'A' : (tail $ tail s)
      | cntSum == cntUpp -> putStrLn $ 'a' : '1' : (tail $ tail s)
      | cntSum == cntLow -> putStrLn $ 'A' : '1' : (tail $ tail s)
      | cntDig == 0 -> putStrLn $ let Just i = findIndex (if cntUpp >= cntLow then isUpper else isLower) s in replace i '1' s
      | cntUpp == 0 -> putStrLn $ let Just i = findIndex (if cntDig >= cntLow then isDigit else isLower) s in replace i 'A' s
      | cntLow == 0 -> putStrLn $ let Just i = findIndex (if cntUpp >= cntDig then isUpper else isDigit) s in replace i 'a' s

