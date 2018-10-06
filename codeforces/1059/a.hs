import Control.Applicative
import qualified Data.ByteString.Char8 as BS
import Data.Maybe

readIntBS = fst . fromJust . BS.readInt

main = do
  [n,l,a] <- map read . words <$> getLine :: IO [Int]
  dat <- map (map readIntBS . BS.words) . BS.lines <$> BS.getContents :: IO [[Int]]

  let dat' = ([0,0] : dat) ++ [[l,0]]

  print $ sum [(j-(i+k))`div`a | ([i,k], [j,_]) <- zip dat' (tail dat')]
