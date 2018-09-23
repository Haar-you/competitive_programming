import Data.List
import Data.Array.IO
import Control.Monad
import Control.Applicative
import Data.Int

primes = aux [2..]
  where aux (x:xs) = x : aux [y | y<-xs, y`mod`x/=0]

main = do
  n <- readLn :: IO Int
  let p = take 1000 primes
  
  arr <- newArray ((0,0),(n+1,n+1)) 1 :: IO (IOUArray (Int,Int) Int64)

  forM_ [(x,y) | x<-[1..n], y<-[1..n]] $ \(x,y) -> do
    when (even (x+y)) $ do
      writeArray arr (x,y) (p!!((x+y)`div`2-1))

  forM_ [(x,y) | x<-[1..n], y<-[1..n]] $ \(x,y) -> do
    when (odd (x+y+n)) $ do
      readArray arr (n-x+1,y) >>= \a -> writeArray arr (n-x+1,y) (a * p!!(n+(x+y)`div`2-1))

  forM_ [(x,y) | x<-[1..n], y<-[1..n]] $ \(x,y) -> do
    when (odd (x+y)) $ do
      a <- readArray arr (x-1,y)
      b <- readArray arr (x+1,y)
      c <- readArray arr (x,y-1)
      d <- readArray arr (x,y+1)
      writeArray arr (x,y) $ foldl lcm 1 [a,b,c,d] + 1

  if n == 2 then
    putStrLn "4 7\n23 10"
    else
    mapM_ putStrLn =<< (forM [1..n] $ \y -> unwords . map show <$> (forM [1..n] $ \x -> readArray arr (x,y)))

