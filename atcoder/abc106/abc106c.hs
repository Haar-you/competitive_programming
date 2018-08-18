import Control.Monad
import Control.Applicative
import Data.Char
import qualified Data.ByteString.Char8 as BS
import Debug.Trace

main :: IO ()
main = do
  s <- getLine
  k <- readLn :: IO Integer
  
  let c = fromIntegral $ length $ takeWhile (=='1') s

  print $ if k <= c then 1 else (ord $ s !! (fromIntegral c)) - ord '0'
