import Control.Applicative
import Data.List
import Data.Maybe
import qualified Data.ByteString.Char8 as BS

readIntBS = fst . fromJust . BS.readInt

main :: IO ()
main = do
  
  [n,x] <- map read . words <$> getLine :: IO [Int]
  xs <- map (abs . (+ (-x)) . readIntBS) . BS.words <$> BS.getLine :: IO [Int]

  print $ foldl1 gcd xs
