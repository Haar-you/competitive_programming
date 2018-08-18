import Control.Monad
import Control.Applicative
import Data.List
import Data.Array
import Data.Array.IO
import Data.Maybe
import qualified Data.ByteString.Char8 as BS
import Debug.Trace

modifyArray arr i f = readArray arr i >>= \x -> writeArray arr i (f x)

listToTuple2 [a,b] = (a,b)
listToTuple3 [a,b,c] = (a,b,c)
listToTuple4 [a,b,c,d] = (a,b,c,d)

readIntBS = fst . fromJust . BS.readInt

main :: IO ()
main = do
  (n,m,query) <- listToTuple3 . map read . words <$> getLine :: IO (Int,Int,Int)
  dat <- map (listToTuple2 . map readIntBS . BS.words) <$> (replicateM m BS.getLine) :: IO [(Int,Int)]
  
  arr <- newArray ((0,0),(n,n)) 0 :: IO (IOArray (Int,Int) Int)

  forM_ dat $ \(l,r) -> do
    modifyArray arr (l,r) (+1)

  {-- 二次元累積和 --}
  forM_ [0..n] $ \l -> do
    forM_ [1..n] $ \r -> do
      (+) <$> readArray arr (l,r-1) <*> readArray arr (l,r) >>= \x -> writeArray arr (l,r) x

  forM_ [1..n] $ \l -> do
    forM_ [0..n] $ \r -> do
      (+) <$> readArray arr (l-1,r) <*> readArray arr (l,r) >>= \x -> writeArray arr (l,r) x

  
  replicateM query $ do
    (p,q) <- listToTuple2 . map readIntBS . BS.words <$> BS.getLine :: IO (Int,Int)
    a <- readArray arr (q,q)
    b <- readArray arr (p-1,q)
    c <- readArray arr (q,p-1)
    d <- readArray arr (p-1,p-1)

    print $ a - b - c + d
    
  return ()
