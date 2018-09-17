import Control.Applicative
import Control.Monad
import Data.List
import Data.Maybe
import Text.Printf

main = do
  n <- readLn :: IO Int

  xs <- sort . catMaybes <$> do
    replicateM (n-1) $ do
      [a,b] <- sort . map read . words <$> getLine :: IO [Int]
      return $ if b == n && a < b then Just a else Nothing

  if length xs == n-1 && and [i<=x | (i,x) <- zip [1..] xs] then do
    putStrLn "YES"
    let
      aux :: [[Int]] -> [Int] -> IO ()
      aux [] _ = return ()
      aux (ys:rest) as = do
        let
          (p,q) = span (<=(head ys)) as
          zs = n : (drop (length p - length ys) p)
        forM_ (zip zs (tail zs)) $ \(x,y) -> do
          printf "%d %d\n" x y
        aux rest (take (length p - length ys) p ++ q)

    aux (group xs) [1..n-1]

    else
    putStrLn "NO"

