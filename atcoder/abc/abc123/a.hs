import Control.Monad
import Data.Bool

main :: IO ()
main = do
  xs <- replicateM 5 $ readLn :: IO [Int]
  k <- readLn :: IO Int
  
  putStrLn $ bool ":(" "Yay!" $ and [abs (a-b) <= k | a<-xs, b<-xs]
