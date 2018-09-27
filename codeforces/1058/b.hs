import Control.Applicative
import Control.Monad

cross (x1,y1) (x2,y2) = x1*y2-x2*y1
sub (x1,y1) (x2,y2) = (x1-x2,y1-y2)
inRect n d x y = all (>=0) t || all (<=0) t
  where
    t = [cross (-1,1) ((x,y) `sub` (d,0)), cross (1,1) ((x,y) `sub` (0,d)),
         cross (1,-1) ((x,y) `sub` (n-d,n)), cross (-1,-1) ((x,y) `sub` (n,n-d))]

main = do
  [n,d] <- map read . words <$> getLine :: IO [Int]
  m <- readLn :: IO Int

  replicateM m $ do
    [x,y] <- map read . words <$> getLine :: IO [Int]
    putStrLn $ if inRect n d x y then "YES" else "NO"
