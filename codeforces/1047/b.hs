import Control.Monad
import Control.Applicative
import Data.List
import Data.Maybe
import qualified Data.ByteString.Char8 as BS

readIntBS = fst . fromJust . BS.readInt

main = do
  n <- readLn :: IO Int
  ps <- map (map readIntBS . BS.words) . BS.lines <$> BS.getContents :: IO [[Int]]

  let m = maximum [x+y | [x,y] <- ps]
  
  print $ m
