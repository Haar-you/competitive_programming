import Control.Applicative
import Data.List

main :: IO ()
main = do
  n <- readLn :: IO Int
  ws <- lines <$> getContents

  putStrLn $ if func ws && (length . nub) ws == length ws then "Yes" else "No"

  where
    func xs = and $ zipWith (\x y -> last x == head y) xs (tail xs) 
