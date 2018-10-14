import Control.Applicative
import Data.List

main = do
  n <- readLn :: IO Int
  s <- sort <$> getLine

  putStrLn $ s
