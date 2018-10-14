import Data.Bits
import Control.Applicative
import Control.Monad

main = do
  t <- readLn :: IO Int

  replicateM_ t $ do
    a <- readLn :: IO Int
    print $ 2 ^ (popCount a)
    
