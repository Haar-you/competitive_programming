import Data.Int
import Data.List
import qualified Data.ByteString.Char8 as BS
import Data.Maybe

readIntBS = fst . fromJust . BS.readInteger

main :: IO ()
main = do
  [n,a,b] <- map read . words <$> getLine :: IO [Integer]
  ds <- sort . map readIntBS . BS.words <$> BS.getLine :: IO [Integer]


  let
    ans =
      if ds == [] then
        n - (n+a-1) `div` a
      else
        n - (
        (head ds + a-1) `div` a - 1 +
        ((n - last ds + 1) + a-1) `div` a - 1 +
        (sum $ zipWith (\i j -> (j-i+a-1)`div`a) (init ds) (tail ds)) - (b-1) + b
        )

  print ans
