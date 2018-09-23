import Control.Applicative
import Data.List

main :: IO ()
main = do
  [a,b,c] <- sort . map read . words <$> getLine
  print $ c*10+b+a
