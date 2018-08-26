import Control.Applicative
import Data.List
import Data.Array
import Data.Maybe
import qualified Data.ByteString.Char8 as BS

listToTuple2 [a,b] = (a,b)
readIntBS = fst . fromJust . BS.readInt

main :: IO ()
main = do
  (n,k) <- listToTuple2 . map read . words <$> getLine :: IO (Int,Int)
  xs <- map readIntBS . BS.words <$> BS.getLine :: IO [Int]

  let
    (a,b) = span (<0) xs
    a_ = listArray (0,length a) $ 0 : (reverse $ map negate a)
    b_ = listArray (0,length b) $ 0 : b

  print $ minimum [min (a_!l*2+b_!r) (a_!l+b_!r*2) | l<-[0..length a], let r=if k-l<0 then 0 else k-l, r<=length b]
