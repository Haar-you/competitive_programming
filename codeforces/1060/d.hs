import Control.Applicative
import Data.List
import Data.Maybe
import qualified Data.ByteString.Char8 as BS

readIntBS = fst . fromJust . BS.readInt

main = do
  n <- readLn :: IO Integer
  [l,r] <- transpose . map (map (fromIntegral . readIntBS) . BS.words) . BS.lines <$> BS.getContents :: IO [[Integer]]

  print $ n + sum (zipWith max (sort l) (sort r))
