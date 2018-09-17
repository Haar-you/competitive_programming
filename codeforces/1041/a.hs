import Control.Applicative
import Data.List
import Data.Maybe
import qualified Data.ByteString.Char8 as BS

readIntBS = fst . fromJust . BS.readInt

main = do
  n <- readLn :: IO Int
  xs <- map read . words <$> getLine :: IO [Int]

  print $ maximum xs - minimum xs + 1 - n
